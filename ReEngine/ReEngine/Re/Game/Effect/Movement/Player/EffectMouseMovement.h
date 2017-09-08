#pragma once
#include <Re\Game\Effect\Movement\EffectMovementAim.h>

namespace Effect
{
	/// specialized version of MovementAim for player
	/// uppon activating presscode action from actionMap 
	/// destination is updated to mouse pos within game world
	class MouseMovement: public MovementAim
	{
		SERIALISATION_NAME(MouseMovement)
	public:
		MouseMovement(float32 movementSpeed = 1.f);

		////// events

		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		/////// setters

		MouseMovement* setInfluenceFall(float32 s)
		{
			MovementAim::setInfluenceFall(s);
			return this;
		}
		MouseMovement* setMinimalDistance(float32 s)
		{
			MovementAim::setMinimalDistance(s);
			return this;
		}
		MouseMovement* setMovementSpeed(float32 s)
		{
			MovementAim::setMovementSpeed(s);
			return this;
		}
		MouseMovement* setRotationSpeedMax(Angle s)
		{
			MovementAim::setRotationSpeedMax(s);
			return this;
		}
		MouseMovement* setRotationSmoothness(float32 s)
		{
			MovementAim::setRotationSmoothness(s);
			return this;
		}
		MouseMovement* setKey(const std::string& keyCode);
		MouseMovement* setCanMove(function<bool()>& condition)
		{
			canMove = condition;
			return this;
		}
		
	public:////// Data


		/// key saying when to start move to aim
		Control::MultiKey *pressKey{ nullptr};
		/// used to specify when to change destination of MovementAim 
		/// you can by this for example block movement for certain conditions
		function<bool()> canMove{ []() {return true; } };
	private:
		Vector2D destination;

	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};

}