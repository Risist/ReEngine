#pragma once
#include <Re\ReEngine.h>


class ActorWeapon : public Game::Actor
{
public:
	ActorWeapon(Game::Actor* owner, Transformable* transformable);

	virtual void onInit() override;
	virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) override;
	virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture*otherFixture) override;

	Game::Actor* owner;
	Transformable* updateTransformable;
};

