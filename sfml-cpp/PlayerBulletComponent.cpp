#include "PlayerBulletComponent.h"
#include <memory>
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Level.h"
#include "BlockingComponent.h"
#include "EnemyComponent.h"

void PlayerBulletComponent::Start()
{
	EnableTick(true);
}


void PlayerBulletComponent::Tick(float deltaTime)
{
	elapsed += deltaTime;

	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();
	auto level = go->GetLevel().lock();

	// Move bullet
	transform->Position = transform->Position + (direction * deltaTime * speed);

	// Handle collisions
	auto collisions = collider->GetOverlappingObjects();
	for (auto pObj : collisions)
	{
		auto obj = pObj.lock();

		auto pHitEnemy = obj->GetComponent<EnemyComponent>();
		if (!pHitEnemy.expired())
		{
			// Kill things
			auto hitEnemy = pHitEnemy.lock();
			hitEnemy->Hit();
			level->DestroyObject(go);
		}
		else if (!obj->GetComponent<BlockingComponent>().expired() && obj->GetComponent<BlockingComponent>().lock()->blockBullet)
		{
			// Hit wall
			level->DestroyObject(go);
		}
	}

	// Expire
	if (elapsed > 0.3f)
	{
		level->DestroyObject(go);
	}

}

