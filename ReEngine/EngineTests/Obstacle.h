#pragma once
#include <Re\ReEngine.h>

class Obstacle : public Game::Actor
{
public:
	Obstacle();

	virtual void onInit() override;
	virtual void onUpdate(sf::Time dt) override;
	virtual void onRespawn() override;

	Effect::Health* efHealth;

};

