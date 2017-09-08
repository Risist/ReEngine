#pragma once
#include <Re\Game\Game.h>
#include <Re\Game\Efect\efects.h>

class ActorHumanoidNpc : public Game::Actor
{
public:
	ActorHumanoidNpc();

	virtual void onInit() override;
	
	

	//////efects

	/// graphics
	Efect::Model *efModel{ nullptr };
	Efect::AnimationManager *efAnim{ nullptr };

	Graphics::AnimationController *animWalk{ nullptr };
	Graphics::AnimationController *animTakeDmg{ nullptr };
	Graphics::AnimationController *animDie{ nullptr };

	/// health
	Efect::Health *efHealth{ nullptr };

	/// ai
	Efect::MovementAim *efMovement{ nullptr };
	Efect::Mind *efMind{ nullptr };
	Efect::Sensor *efSensor{nullptr};

protected:
	void displayHealthbar(const Vector2D& wh, const Vector2D& offset, Color clOn, Color clBackground);
};

