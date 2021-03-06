#include "PlayerManager.h"
#include "PlayerLC.h"
#include "spawn/RespawnComponent.h"
#include "../combat/WeaponManager.h"
#include <DebugIO.h>

EntityId PlayerManager::makePlayer(const WeaponManager & weapons) {
	EntityId playerId;
	EntitySystem::GenEntities(1, &playerId);
	EntitySystem::MakeComps<PlayerLC>(1, &playerId);
	EntitySystem::MakeComps<NameTagComponent>(1, &playerId);
	EntitySystem::GetComp<CombatComponent>(playerId)->hurtboxes.emplace_back(Hurtbox{ Vec2f{ -2, -20 }, AABB{ {0, 0}, {4, 20} } });
	EntitySystem::GetComp<CombatComponent>(playerId)->health = 100;
	EntitySystem::GetComp<CombatComponent>(playerId)->stats = CombatStats{ 100, 2, 0, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	EntitySystem::GetComp<NameTagComponent>(playerId)->nameTag = "Player";

	return playerId;
}


void PlayerManager::updateAll(double timeDelta, const Stage & stage, SpawnSystem& spawns) {
	if (EntitySystem::Contains<PlayerLC>()) {
		for (auto& player : EntitySystem::GetPool<PlayerLC>()) {
			updatePlayer(timeDelta, player, stage, spawns);
		}
	}
}

void PlayerManager::update(EntityId playerId, double timeDelta, const Stage& stage, SpawnSystem& spawns) {
	if (EntitySystem::Contains<PlayerLC>()) {
		PlayerLC* player = EntitySystem::GetComp<PlayerLC>(playerId);
		updatePlayer(timeDelta, *player, stage, spawns);

	}
}

void PlayerManager::updatePlayer(double timeDelta, PlayerLC& player, const Stage& stage, SpawnSystem& spawns) {
	player.update(timeDelta);
}
