#include <Re\Game\Effect\Movement\Player\EffectRotatedMovement.h>
#include <Re\Graphics\Graphics.h>
#include <Re\Game\Effect\Physics\EffectRigidbody.h>

namespace Effect
{

	
	RotatedMovement::RotatedMovement(float32 _linearSpeed)
		: StaticMovement(_linearSpeed)
	{
		wnd.setMouseCursorGrabbed(true);
	}

	void RotatedMovement::onUpdate(sf::Time dt)
	{
		assert(xAxis && yAxis);

		Vector2D offset = { xAxis->getValue(), yAxis->getValue() };

		float dragValue = clamp(drag.measure().x * rotationSmoothness*dt.asSeconds(), -rotationSpeedMax.asDegree(), rotationSpeedMax.asDegree()) * 1000;

		((Rigidbody*)getParent())->getRigidbody()->ApplyTorque(Degree(dragValue).asRadian(), true);

		if (!offset.isZero())
		{
			applyInfluence(offset.getRotated(getActor()->getRotation() ) );
		}

		/////////////Super::onUpdate(dt);
		if (influence.getLenghtSq() <= minimalDistance*minimalDistance)
		{
			/// stored influence is too low
			stop();
		}

		/// execute movement
		if (bAtMove)
		{

			updatePosition(dt, influence.getNormalised());
			///updateRotation(dt, influence);

			influence *= influenceFall;
		}
		//////
		
		drag.loopMouse(lockRadius);
	}
}