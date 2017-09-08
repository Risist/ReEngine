#pragma once
#include <Re\Game\Effect\Movement\EffectMovementAim.h>

namespace Effect
{
	/// WIP
	/*class RadiusMovement : public MovementAim
	{
		SERIALISATION_NAME(RadiusMovement)
	public:
		RadiusMovement(float32 movementSpeed = 1.f);


		////// events
		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		/////// setters

		RadiusMovement* setRadius(float32 rotation, float32 movement, float32 movementMax)
		{
			rotationRadius = rotation;
			setMinimalDistance(movement);
			movementRadiusMax = movementMax;
			return this;
		}
		REDEFINE_SETTER_1(RadiusMovement, setInfluenceFall, float32);
		REDEFINE_SETTER_1(RadiusMovement, setMovementSpeed, float32);
		REDEFINE_SETTER_1(RadiusMovement, setRotationSpeedMax, Angle);
		REDEFINE_SETTER_1(RadiusMovement, setRotationSmoothness, float32);

		////// Getters

		float32 getRotationRadius() const
		{
			return rotationRadius;
		}
		float32 getMovementRadius() const
		{
			return getMinimalDistance();
		}
		float32 getMovmentRadiusMax() const
		{
			return movementRadiusMax;
		}
		float32 getLastMovementSpeedModificator;

	private:
		/// the efect does sevral actions
		/// each one runs only when mouse is in sertain distance from character (center of screan)
		float32 rotationRadius{100.f};		/// in radius > rotationRadius character rotates towards mouse
		//float32 movementRadius{200.f};		/// in radius > movementRadius character starts to move towards mouse
		float32 movementRadiusMax{300.f};	/// describes in which radius character will accerelate with max speed

		float32 lastMovementSpeedModificator;


		REDEFINE_SETTER_1(RadiusMovement, setMinimalDistance, float32);

	protected:
		/// TODO
		// serialiseF
		// deserialiseF
	};*/
}