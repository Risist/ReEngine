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

	////// animations
	Graphics::AnimationController* animPose{ nullptr };
	Graphics::AnimationController* animGreatSlash{ nullptr };
	Graphics::AnimationController* animPull{ nullptr };
	Graphics::AnimationController* animPush{ nullptr };
	Graphics::AnimationController* animWalk{ nullptr };
	Graphics::AnimationController* animSlash{ nullptr };
private:
	void createInput();

	/// slash
	float32 slashLoaded{0};
	bool onSlash{ false }, onSlashBack{ false };
	bool onPull{ false }, onPush{ false };


	Control::Timer jumpCd, jumpTime;
	Control::Key jumpKey;
	float32 defaultMovementSpeed;
};

