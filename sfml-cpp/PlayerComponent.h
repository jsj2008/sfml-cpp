#pragma once
#include "GameComponent.h"

class PlayerComponent : public GameComponent
{
	
public:
	void Update(float deltaTime) override {};
};

DECLARE_LOADABLE(PlayerComponent);
