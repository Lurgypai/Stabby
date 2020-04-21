#include <fstream>

#include "EntityBaseComponent.h"
#include "ControllerComponent.h"
#include "RectDrawable.h"
#include "TextDrawable.h"
#include "PositionComponent.h"
#include "GLRenderer.h"

#include "nlohmann/json.hpp"
#include "../graphics/PlayerGC.h"
#include "../graphics/CapturePointGC.h"
#include "../player/ClientPlayerComponent.h"
#include "../player/OnlinePlayerLC.h"
#include "../graphics/camera/PlayerCam.h"

#include "Game.h"

using json = nlohmann::json;

Game::Game() :
	physics{},
	combat{},
	clientPlayers{&physics, &combat}
{}

void Game::startOfflineGame() {
	for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
		entity.isDead = true;
	}

	editables.isEnabled = false;
	
	std::ifstream settingsFile{ "settings.json" };
	json settings{};
	settingsFile >> settings;
	std::string stageName = settings["stage"];



	loadStage(stageName);

	playerId = players.makePlayer(weapons);
	makePlayerGFX(playerId);

	EntitySystem::GetComp<PlayerLC>(playerId)->chooseSpawn();

	mode.load(&spawns, 2, 1, 6000);

	auto spawnables = stage.getSpawnables();
	EntitySystem::MakeComps<CapturePointGC>(spawnables.size(), spawnables.data());

	gameState = GameState::offline;

	renderGroups[playerCamId].push_back(playerId);
	for (auto& stageAsset : stage.getRenderables()) {
		renderGroups[playerCamId].push_back(stageAsset);
	}
	for (auto& capturePoint : stage.getSpawnables()) {
		renderGroups[playerCamId].push_back(capturePoint);
	}
}

void Game::startOnlineGame() {
	for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
		entity.isDead = true;
	}
	editables.isEnabled = false;

	std::ifstream settingsFile{ "settings.json" };
	json settings{};
	settingsFile >> settings;
	std::string stageName = settings["stage"];
	std::string address = settings["ip"];
	int port = settings["port"];

	loadStage(stageName);

	playerId = players.makePlayer(weapons);
	EntitySystem::MakeComps<ClientPlayerComponent>(1, &playerId);
	makePlayerGFX(playerId);

	client.setPlayer(playerId);
	client.setWeaponManager(weapons);
	client.setClientPlayerSystem(&clientPlayers);
	client.setOnlineSystem(&online);
	client.setMode(&mode);
	client.setSpawns(&spawns);

	client.connect(address, port);

	gameState = GameState::online;
}

void Game::startStageEditor(const std::string & filePath) {
	for (auto& entity : EntitySystem::GetPool<EntityBaseComponent>()) {
		entity.isDead = true;
	}

	editables.isEnabled = true;
	editables.load(filePath);

	gameState = GameState::stage_editor;

	renderGroups[editorCamId].push_back(editables.getStageImage());
	for (auto& editableStageComponent : EntitySystem::GetPool<EditableStageComponent>()) {
		renderGroups[editorCamId].push_back(editableStageComponent.getId());
	}
}

void Game::loadStage(const std::string& stageName) {
	stage = Stage(stageName, spawns);
	stage.loadGraphics();
}

void Game::loadCameras(int viewWidth, int viewHeight) {
	PlayerCam playerCam{ viewWidth, viewHeight };
	Camera editorCamera{ Vec2f{0.0f, 0.0f}, Vec2f{static_cast<float>(viewWidth), static_cast<float>(viewHeight)}, 1.0 };
	playerCamId = GLRenderer::addCamera(playerCam);
	editorCamId = GLRenderer::addCamera(editorCamera);

	editorCam = EditorCam{ editorCamId };
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

		unsigned int i = 0;
		for(auto& netId : client.getNewPlayers()) {
			EntityId entity = entities[i];
			online.registerOnlineComponent(entity, netId);
			EntitySystem::GetComp<CombatComponent>(entity)->hurtboxes.emplace_back(Hurtbox{ Vec2f{ -2, -20 }, AABB{ {0, 0}, {4, 20} } });
			EntitySystem::GetComp<CombatComponent>(entity)->health = 100;
			EntitySystem::GetComp<CombatComponent>(entity)->attack = weapons.cloneAttack("player_sword");

			makePlayerGFX(entity);

			renderGroups[playerCamId].push_back(entity);

			++i;
		}
	}
	client.clearNewPlayers();
}

void Game::updateEditorCamera() {
	editorCam.update();
}

void Game::updateEditor() {
	editables.updateLogic(editorCamId);
}

void Game::makePlayerGFX(EntityId playerId_) {
	EntitySystem::MakeComps<PlayerGC>(1, &playerId_);
	EntitySystem::GetComp<RenderComponent>(playerId_)->loadDrawable<AnimatedSprite>("images/stabbyman.png", Vec2i{ 64, 64 });
	EntitySystem::GetComp<PlayerGC>(playerId_)->loadAnimations();
	EntitySystem::GetComp<PlayerGC>(playerId_)->attackSprite = weapons.cloneAnimation("player_sword");
}

void Game::renderAll(double gfxDelay) {
	for (auto& pair : renderGroups) {
		GLRenderer::setCamera(pair.first);
		for (auto& entity : pair.second) {
			render.draw(*EntitySystem::GetComp<RenderComponent>(entity));
		}
	}
}

EntityId Game::getPlayerId() {
	return playerId;
}

const Stage& Game::getStage() const {
	return stage;
}

GameState Game::getState() {
	return gameState;
}
