#pragma once
#include <Re\ReEngine.h>

class ActorPlayer : public Game::Actor
{
public:

	////// events
	virtual void onInit() override;
	virtual void onUpdate( sf::Time dt) override;

	////// effects
	Effect::Model *efModel{nullptr};
	Effect::MovementAim *efMovement{ nullptr };


	Graphics::AnimationController *animSpellCast;
	bool onCastingSpeel{false};

	Control::MultiKey *keySpellCast;
};

