#include "PlayerBulletComponent.h"
#include <memory>
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Level.h"
#include "WallComponent.h"

void PlayerBulletComponent::Tick(float deltaTime)
{
	elapsed += deltaTime;

	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();
	auto level = go->GetLevel().lock();

	// Move bullet
	transform->Position = transform->Position + (direction * deltaTime * speed);

	// Destroy
	if (elapsed > 5.0f || collider->IsOverlappingComponent<WallComponent>())
	{
		level->DestroyObject(go);
	}

}