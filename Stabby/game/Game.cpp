#include <fstream>
#include <filesystem>

#include "EntityBaseComponent.h"
#include "ControllerComponent.h"
#include "RectDrawable.h"
#include "TextDrawable.h"
#include "PositionComponent.h"
#include "GLRenderer.h"
#include "DebugIO.h"
#include "MenuButtonComponent.h"
#include "MenuTextBoxComponent.h"
#include "MenuGridComponent.h"

#include "nlohmann/json.hpp"
#include "../graphics/PlayerGC.h"
#include "../graphics/CapturePointGC.h"
#include "../player/ClientPlayerComponent.h"
#include "../player/OnlinePlayerLC.h"
#include "../graphics/camera/PlayerCam.h"

#include "Game.h"

using json = nlohmann::json;

Game::Game() :
	tick{0},
	gameState{GameState::main_menu},
	physics{},
	combat{},
	clientPlayers{&physics, &combat},
	weaponMenuOpen{false},
	client{ tick },
	sessionGuided{false}
{}

void Game::startMainMenu() {
	if (EntitySystem::Contains<EntityBaseComponent>()) {
		for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
			entity.isDead = true;
		}
		renderGroups.clear();
	}

	mainMenu = menus.makeMenu();
	auto& menu = menus.getMenu(mainMenu);
	menu.addMenuEntry(MenuEntryType::button, "start", AABB{ {278, 305}, {100, 25} });
	menu.addMenuEntry(MenuEntryType::text_box, "name", AABB{ {295, 241}, {100, 20} });
	menu.addMenuEntry(MenuEntryType::text_box, "ip_address", AABB{ {295, 262}, {100, 20} });
	menu.addMenuEntry(MenuEntryType::text_box, "port", AABB{ {295, 283}, {100, 20} });

	for (auto& button : menu.getButtons()) {
		EntityId id = button;
		EntitySystem::MakeComps<RenderComponent>(1, &id);
		RenderComponent* render = EntitySystem::GetComp<RenderComponent>(id);
		MenuButtonComponent* menuButton = EntitySystem::GetComp<MenuButtonComponent>(id);

		render->loadDrawable<RectDrawable>();
		auto* drawable = render->getDrawable<RectDrawable>();
		drawable->shape = menuButton->getBoundingBox();
		drawable->c = { 1.0, 1.0, 1.0, 1.0 };
		drawable->depth = 0.0;

		renderGroups[menuCamId].push_back(button);
	}
	
	
	for (auto& textBox : menu.getTextBoxes()) {

		EntityId id = textBox;
		EntitySystem::MakeComps<RenderComponent>(1, &id);
		RenderComponent* render = EntitySystem::GetComp<RenderComponent>(id);

		render->loadDrawable<TextDrawable>();
		auto* drawable = render->getDrawable<TextDrawable>();
		drawable->color = { 1, 1, 1, 1 };
		drawable->anti_alias = true;
		drawable->font.loadDataFile("suqua/fonts/consolas.fnt");
		drawable->scale = {.5, .5};

		renderGroups[menuCamId].push_back(textBox);
	}
	

	EntityId mainMenuBG;
	EntitySystem::GenEntities(1, &mainMenuBG);
	EntitySystem::MakeComps<RenderComponent>(1, &mainMenuBG);
	RenderComponent* mainMenuRender = EntitySystem::GetComp<RenderComponent>(mainMenuBG);
	mainMenuRender->loadDrawable<Sprite>("main_menu");
	EntitySystem::GetComp<PositionComponent>(mainMenuBG)->pos = { 0 , 0 };
	renderGroups[menuCamId].push_back(mainMenuBG);
}

void Game::startOfflineGame(bool sessionGuided_) {
	for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
		entity.isDead = true;
	}
	renderGroups.clear();
	menus.getMenu(mainMenu).clear();
	loadWeaponMenu();
	editables.isEnabled = false;
	
	std::ifstream settingsFile{ "settings.json" };
	json settings{};
	settingsFile >> settings;
	std::string stageName = settings["stage"];

	loadStage(stageName);

	playerId = players.makePlayer(weapons);
	makePlayerGFX(playerId);

	EntitySystem::GetComp<PlayerLC>(playerId)->chooseSpawn();

	mode.load(&spawns, 2, 1, 200000);

	auto spawnables = stage.getSpawnables();
	EntitySystem::MakeComps<CapturePointGC>(spawnables.size(), spawnables.data());

	gameState = GameState::offline;

	for (auto& stageAsset : stage.getRenderables()) {
		renderGroups[playerCamId].push_back(stageAsset);
	}
	for (auto& capturePoint : stage.getSpawnables()) {
		renderGroups[playerCamId].push_back(capturePoint);
	}

	sessionGuided = sessionGuided_;

	if (sessionGuided) {
		session.unserialize("session");
		EntitySystem::MakeComps<ClientPlayerComponent>(1, &playerId);

		client.setPlayer(playerId);
		client.setWeaponManager(weapons);
		client.setClientPlayerSystem(&clientPlayers);
		client.setOnlineSystem(&online);
		client.setMode(&mode);
		client.setSpawns(&spawns);
		client.setSessionSystem(&session);

		SessionSystem::NetworkEvent netEvent = session.getNetworkEvents().front();

		WelcomePacket packet{};
		std::memcpy(&packet, netEvent.enetEvent.packet->data, netEvent.enetEvent.packet->dataLength);
		packet.unserialize();

		online.registerOnlineComponent(playerId, packet.netId);
		

		tick = session.getCurrTick();
	}
}

void Game::startOnlineGame() {
	for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
		entity.isDead = true;
	}
	renderGroups.clear();
	menus.getMenu(mainMenu).clear();
	loadWeaponMenu();
	editables.isEnabled = false;

	std::ifstream settingsFile{ "settings.json" };
	json settings{};
	settingsFile >> settings;
	std::string stageName = settings["stage"];
	std::string address = settings["ip"];
	std::string name = settings["name"];
	int port = settings["port"];

	loadStage(stageName);

	playerId = players.makePlayer(weapons);
	EntitySystem::MakeComps<ClientPlayerComponent>(1, &playerId);
	EntitySystem::GetComp<NameTagComponent>(playerId)->nameTag = name;
	makePlayerGFX(playerId);

	client.setPlayer(playerId);
	client.setWeaponManager(weapons);
	client.setClientPlayerSystem(&clientPlayers);
	client.setOnlineSystem(&online);
	client.setMode(&mode);
	client.setSpawns(&spawns);
	client.setSessionSystem(&session);

	client.connect(address, port);

	gameState = GameState::online;

	for (auto& stageAsset : stage.getRenderables()) {
		renderGroups[playerCamId].push_back(stageAsset);
	}
}

void Game::startStageEditor(const std::string & filePath) {
	for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
		entity.isDead = true;
	}
	renderGroups.clear();
	menus.getMenu(mainMenu).clear();

	editables.isEnabled = true;
	editables.load(filePath);

	gameState = GameState::stage_editor;

	renderGroups[editorCamId].push_back(editables.getStageImage());
	if (EntitySystem::Contains<EditableStageComponent>()) {
		for (auto& editableStageComponent : EntitySystem::GetPool<EditableStageComponent>()) {
			renderGroups[editorCamId].push_back(editableStageComponent.getId());
		}
	}
}

void Game::loadStage(const std::string& stageName) {
	stage = Stage(stageName, spawns);
	stage.loadGraphics();
}

void Game::loadCameras(int viewWidth, int viewHeight) {
	PlayerCam playerCam{ viewWidth, viewHeight };
	Camera editorCamera{ Vec2f{0.0f, 0.0f}, Vec2f{static_cast<float>(viewWidth), static_cast<float>(viewHeight)}, 1.0 };
	Camera menuCamera{ Vec2f{0.0f, 0.0f}, Vec2f{static_cast<float>(viewWidth), static_cast<float>(viewHeight)}, 1.0 };
	playerCamId = GLRenderer::addCamera(playerCam);
	editorCamId = GLRenderer::addCamera(editorCamera);
	menuCamId = GLRenderer::addCamera(menuCamera);

	editorCam = EditorCam{ editorCamId };
}

void Game::loadTextures() {
	//misc
	GLRenderer::LoadTexture("images/none.png", "none");

	//font
	GLRenderer::LoadTexture("suqua/fonts/consolas_0.png", "test_font");

	//menus
	GLRenderer::LoadTexture("images/temp_main_menu.png", "main_menu");
	GLRenderer::LoadTexture("images/weapon_gui.png", "weapon_menu");
	
	//player
	GLRenderer::LoadTexture("images/stabbyman.png", "character");

	//stage
	namespace fs = std::filesystem;

	fs::path path{ "stage/" };
	for (auto& file : fs::directory_iterator(path)) {
		if (file.path().extension() == ".png") {
			std::string id = file.path().stem().string();
			GLRenderer::LoadTexture(file.path().string(), "stage::" + id);
		}
	}

	//weapons
	path = fs::path{ "attacks/asset/" };
	for (auto& file : fs::directory_iterator(path)) {
		if (file.path().extension() == ".png") {
			std::string id = file.path().stem().string();
			GLRenderer::LoadTexture(file.path().string(), "weapon::" + id);
		}
	}
}

void Game::updatePlayerCamera() {
	static_cast<PlayerCam&>(GLRenderer::getCamera(playerCamId)).update(playerId);
}

void Game::loadNewPlayers() {
	if (!client.getNewPlayers().empty()) {
		auto size = client.getNewPlayers().size();

		std::vector<EntityId> entities;
		entities.resize(size);
		EntitySystem::GenEntities(entities.size(), entities.data());
		EntitySystem::MakeComps<OnlinePlayerLC>(entities.size(), entities.data());
		EntitySystem::MakeComps<OnlineComponent>(entities.size(), entities.data());
		EntitySystem::MakeComps<NameTagComponent>(entities.size(), entities.data());

		unsigned int i = 0;
		for(auto& netId : client.getNewPlayers()) {
			EntityId entity = entities[i];
			online.registerOnlineComponent(entity, netId);
			EntitySystem::GetComp<CombatComponent>(entity)->hurtboxes.emplace_back(Hurtbox{ Vec2f{ -2, -20 }, AABB{ {0, 0}, {4, 20} } });
			EntitySystem::GetComp<CombatComponent>(entity)->health = 100;
			EntitySystem::GetComp<CombatComponent>(entity)->setAttack("sword");
			EntitySystem::GetComp<CombatComponent>(entity)->stats = CombatStats{ 100, 2, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };
			PositionComponent* pos = EntitySystem::GetComp<PositionComponent>(entity);
			pos->pos = { 0, 0 };

			makePlayerGFX(entity);

			++i;
		}
	}
	client.clearNewPlayers();
}

void Game::loadNewCapturePoints() {
	for (const auto& packet : client.getMissingCapturePoints()) {
		bool spawnWasFound = false;
		for (auto& spawn : EntitySystem::GetPool<SpawnComponent>()) {
			if (spawn.getSpawnZone() == packet.zone) {
				EntityId id = spawn.getId();
				spawnWasFound = true;
				mode.createZone(id, packet.zone, packet.state.currTeamId, packet.state.totalCaptureTime, packet.state.remainingCaptureTime);

				CapturePointComponent* capturePoint = EntitySystem::GetComp<CapturePointComponent>(id);
				capturePoint->setState(packet.state);

				EntitySystem::MakeComps<CapturePointGC>(1, &id);

				renderGroups[playerCamId].push_back(id);

				online.registerOnlineComponent(id, packet.netId);
			}
		}
		if (!spawnWasFound) {
			//unable to sync with server, throw an error
			throw std::exception{};
		}
	}
	client.clearMissingCapturePoints();
}

void Game::updateEditorCamera() {
	editorCam.update();
}

void Game::updateEditor() {
	editables.updateLogic(editorCamId);
}

void Game::updateMainMenu() {
	auto& menu = menus.getMenu(mainMenu);
	menu.updateMenuEntries(menuCamId);

	std::ifstream settingsFile{ "settings.json" };
	json settings{};
	settingsFile >> settings;
	std::string address = settings["ip"];
	int port = settings["port"];
	std::string name = settings["name"];
	settingsFile.close();

	MenuResult r{};
	while (menu.pollResult(r)) {
		switch (r.type) {
		case MenuEntryType::button:
		{
			std::string response{ r.button.response };
			if (response == "start") {
				startOnlineGame();
			}
		}
		case MenuEntryType::text_box:
		{
			std::string response{ r.text_box.resposne };
			if (r.entryTag == "ip_address") {
				settings["ip"] = response;
				address = response;
			}
			else if (r.entryTag == "port") {
				try {
					int newPort = std::stoi(response);
					settings["port"] = newPort;
					port = newPort;
				}
				catch (std::invalid_argument e) {}
			}
			else if (r.entryTag == "name") {
				settings["name"] = response;
				name = response;
			}
		}
		}
	}

	std::ofstream out{ "settings.json" };
	out << settings;
	out.close();

	for (auto& textBoxId : menu.getTextBoxes()) {
		MenuTextBoxComponent* textBox = EntitySystem::GetComp<MenuTextBoxComponent>(textBoxId);
		RenderComponent* render = EntitySystem::GetComp<RenderComponent>(textBoxId);

		if (textBox->getTag() == "ip_address") {
			if (textBox->isActive())
				render->getDrawable<TextDrawable>()->text = textBox->getActiveText();
			else
				render->getDrawable<TextDrawable>()->text = address;
		}
		else if (textBox->getTag() == "port") {
			if (textBox->isActive())
				render->getDrawable<TextDrawable>()->text = textBox->getActiveText();
			else
				render->getDrawable<TextDrawable>()->text = std::to_string(port);
		}
		else if (textBox->getTag() == "name") {
			if (textBox->isActive())
				render->getDrawable<TextDrawable>()->text = textBox->getActiveText();
			else
				render->getDrawable<TextDrawable>()->text = name;
		}
	}
}

void Game::updateWeaponMenu() {
	CombatComponent* playerCombat = EntitySystem::GetComp<CombatComponent>(playerId);
	//if he's dead, open the menu and toggle it to not open again.
	//if he's alive, allow to open menu, and clear the menu
	if (!playerCombat->isAlive()) {
		if (shouldOpenWeaponMenu) {
			shouldOpenWeaponMenu = false;
			weaponMenuOpen = true;
			openWeaponMenu();
		}
	}
	else {
		shouldOpenWeaponMenu = true;
		weaponMenuOpen = false;
		renderGroups[menuCamId].clear();
	}

	//when the menu is open, update
	if(weaponMenuOpen) {
		//position gfx
		auto& weaponMenu_ = menus.getMenu(weaponMenu);
		weaponMenu_.updateMenuEntries(menuCamId);
		MenuTextBoxComponent* text = EntitySystem::GetComp<MenuTextBoxComponent>(weaponMenu_.getMenuEntry("search_bar"));
		MenuGridComponent* grid = EntitySystem::GetComp<MenuGridComponent>(weaponMenu_.getMenuEntry("weapon_grid"));

		auto buttonBoxes = grid->generateButtonBoxes();
		auto buttonTags = grid->getCurrButtons();
		int i = 0;
		
		for (auto& pair : weaponIcons) {
			RenderComponent* render = EntitySystem::GetComp<RenderComponent>(pair.second);
			render->getDrawable<Sprite>()->setScale({ 0, 0 });
		}
		if (buttonTags.empty()) {
			if (!grid->prefix.empty()) {
				auto iter = weaponIcons.find(grid->prefix);
				if (iter != weaponIcons.end()) {
					auto& currButton = buttonBoxes[i];

					EntityId buttonImgId = weaponIcons[grid->prefix];
					RenderComponent* render = EntitySystem::GetComp<RenderComponent>(buttonImgId);
					PositionComponent* pos = EntitySystem::GetComp<PositionComponent>(buttonImgId);
					pos->pos = currButton.pos;
					render->getDrawable<Sprite>()->setScale({ 1, 1 });
				}
			}
		}
		else {
			for (auto buttonTag : buttonTags) {
				buttonTag = grid->prefix + buttonTag;
				auto& currButton = buttonBoxes[i];

				EntityId buttonImgId = weaponIcons[buttonTag];
				RenderComponent* render = EntitySystem::GetComp<RenderComponent>(buttonImgId);
				PositionComponent* pos = EntitySystem::GetComp<PositionComponent>(buttonImgId);
				pos->pos = currButton.pos;
				render->getDrawable<Sprite>()->setScale({ 1, 1 });
				++i;
			}
		}

		MenuResult r;
		std::string currQuery;
		while (weaponMenu_.pollResult(r)) {
			switch (r.type) {
			case MenuEntryType::text_box:
			{
				std::string response{ r.text_box.resposne };
				if (r.entryTag == "search_bar") {
					currQuery = response;
				}
			}
			case MenuEntryType::grid:
			{
				std::string response{ r.grid.response };
				if (r.entryTag == "weapon_grid") {
					if (weapons.hasWeapon(response)) {
						//close the menu
						weaponMenuOpen = false;
						renderGroups[menuCamId].clear();


						if (EntitySystem::Contains<PlayerLC>() && EntitySystem::Contains<PlayerGC>()) {
							if (!client.getConnected()) {
								PlayerLC* player = EntitySystem::GetComp<PlayerLC>(playerId);
								PlayerGC* graphics = EntitySystem::GetComp<PlayerGC>(playerId);

								player->setWeapon(response);
							}
							else {
								OnlineComponent* online = EntitySystem::GetComp<OnlineComponent>(playerId);
								size_t size = response.size();

								WeaponChangePacket p;
								p.size = size;
								p.id = online->getNetId();
								p.serialize();
								char* data = static_cast<char*>(malloc(sizeof(WeaponChangePacket) + size));
								memcpy(data, &p, sizeof(WeaponChangePacket));
								memcpy(data + sizeof(WeaponChangePacket), response.data(), size);
								client.send(sizeof(WeaponChangePacket) + size, data);
								free(data);
							}
						}
					}
				}
			}
			}
		}

		for (auto& textBoxId : weaponMenu_.getTextBoxes()) {
			MenuTextBoxComponent* textBox = EntitySystem::GetComp<MenuTextBoxComponent>(textBoxId);
			RenderComponent* render = EntitySystem::GetComp<RenderComponent>(textBoxId);

			if (textBox->getTag() == "search_bar") { 
				if (textBox->isActive()) {
					render->getDrawable<TextDrawable>()->text = textBox->getActiveText();
					grid->prefix = textBox->getActiveText();
				}
				else {
					render->getDrawable<TextDrawable>()->text = currQuery;
					grid->prefix = currQuery;
				}
			}
		}
	}
}

void Game::loadWeaponMenu() {
	//weapon menu
	weaponMenu = menus.makeMenu();
	auto& weaponMenu_ = menus.getMenu(weaponMenu);
	weaponMenu_.addMenuEntry(MenuEntryType::text_box, "search_bar", AABB{ {222, 71}, {182, 18} });
	weaponMenu_.addMenuEntry(MenuEntryType::grid, "weapon_grid", AABB{ {218, 87}, {190, 190} });
	MenuTextBoxComponent* weaponMenuTextBox = EntitySystem::GetComp<MenuTextBoxComponent>(weaponMenu_.getMenuEntry("search_bar"));
	weaponMenuTextBox->setCharLimit(21);

	MenuGridComponent* weaponMenuGrid = EntitySystem::GetComp<MenuGridComponent>(weaponMenu_.getMenuEntry("weapon_grid"));
	weaponMenuGrid->buttonRes = { 32, 32 };
	weaponMenuGrid->margins = { 5, 5 };
	auto& tags = weapons.getAttackTags();
	weaponMenuGrid->setButtons(tags);

	EntitySystem::GenEntities(1, &weaponMenuBG);
	EntitySystem::MakeComps<RenderComponent>(1, &weaponMenuBG);
	RenderComponent* weaponMenuRender = EntitySystem::GetComp<RenderComponent>(weaponMenuBG);
	weaponMenuRender->loadDrawable<Sprite>("weapon_menu");
	weaponMenuRender->getDrawable<Sprite>()->setDepth(-0.5);
	EntitySystem::GetComp<PositionComponent>(weaponMenuBG)->pos = { 0, 0 };

	for (auto& weapon : tags) {
		EntityId iconId;
		EntitySystem::GenEntities(1, &iconId);
		EntitySystem::MakeComps<RenderComponent>(1, &iconId);
		RenderComponent* render = EntitySystem::GetComp<RenderComponent>(iconId);
		render->loadDrawable<Sprite>("weapon::" + weapon + "_icon");
		render->getDrawable<Sprite>()->setScale({ 0, 0 });
		render->getDrawable<Sprite>()->setDepth(-1.0);
		weaponIcons.emplace(weapon, iconId);
	}

	for (auto& textBox : weaponMenu_.getTextBoxes()) {
		EntityId id = textBox;
		EntitySystem::MakeComps<RenderComponent>(1, &id);
		RenderComponent* render = EntitySystem::GetComp<RenderComponent>(id);

		render->loadDrawable<TextDrawable>();
		auto* drawable = render->getDrawable<TextDrawable>();
		drawable->color = { 1.0, 1.0, 1.0, 1.0 };
		drawable->anti_alias = true;
		drawable->font.loadDataFile("suqua/fonts/consolas.fnt");
		drawable->scale = { .5, .5 };
	}
}

void Game::openWeaponMenu() {
	renderGroups[menuCamId].clear();
	renderGroups[menuCamId].push_back(weaponMenuBG);

	Menu& menu = menus.getMenu(weaponMenu);
	for (auto& text : menu.getTextBoxes()) {
		renderGroups[menuCamId].push_back(text);
	}

	for (auto& pair : weaponIcons) {
		renderGroups[menuCamId].push_back(pair.second);
	}
}

void Game::makePlayerGFX(EntityId playerId_) {
	EntitySystem::MakeComps<PlayerGC>(1, &playerId_);
	EntitySystem::GetComp<RenderComponent>(playerId_)->loadDrawable<AnimatedSprite>("character", Vec2i{ 64, 64 });
	EntitySystem::GetComp<RenderComponent>(playerId_)->getDrawable<AnimatedSprite>()->setDepth(0.0);
	EntitySystem::GetComp<PlayerGC>(playerId_)->loadAnimations(weapons);
	EntitySystem::GetComp<PlayerGC>(playerId_)->loadNameTag();

	renderGroups[playerCamId].push_back(playerId_);
	renderGroups[playerCamId].push_back(EntitySystem::GetComp<PlayerGC>(playerId_)->getNameTageRenderId());
}

void Game::renderAll(double gfxDelay) {
	for (auto& pair : renderGroups) {
		GLRenderer::setCamera(pair.first);
		for (auto& entity : pair.second) {
			RenderComponent* comp = EntitySystem::GetComp<RenderComponent>(entity);
			if (comp) {
				render.draw(*comp);
			}
			else {
				//remove it
			}
		}
	}
}

const PlayerCam& Game::getPlayerCam() const {
	return static_cast<PlayerCam&>(GLRenderer::getCamera(playerCamId));
}

EntityId Game::getPlayerId() {
	return playerId;
}

const Stage& Game::getStage() const {
	return stage;
}

Game::GameState Game::getState() {
	return gameState;
}

bool Game::isSessionGuided() const {
	return sessionGuided;
}
