#include <Re\Game\Effect\Movement\Player\EffectRadiusMovement.h>
#include <Re\Game\GameActor.h>
#include <Re\Graphics\Camera.h>
#include <Re\Game\Effect\Physics\EffectRigidbody.h>
extern RenderWindow wnd;

namespace Effect
{
	
	/*
	RadiusMovement::RadiusMovement(float32 _movementSpeed)
		: MovementAim(_movementSpeed)
	{
		setMinimalDistance(0.f);
	}

	void RadiusMovement::onInit()
	{
		/// set mouse position to middle screan -> dead zone
		/// in this place character will not move at the begining of the game
		sf::Mouse::setPosition((Vector2D)wnd.getSize()*0.5f, wnd);
	}
	void RadiusMovement::onUpdate(sf::Time dt)
	{
		/// do not move character if wnd has no focus
		if (wnd.hasFocus() == false)
		{
			lastMovementSpeedModificator = 0;
			return;
		}


		setDestination(cam.mapPixelToCoords(sf::Mouse::getPosition(wnd)));


		/// check if influence is strong enough
		if (influence.getLenghtSq() <= minimalDistance*minimalDistance)
		{
			/// stored influence is too low
			stop();
		}

		/// execute movement
		if (bAtMove)
		{

			Vector2D infNorm = getInfluence();

			float32 toMouseRadius = sqrt(influence.getLenghtSq());
			/// normalize
			infNorm /= toMouseRadius;

			toMouseRadius = clamp(toMouseRadius, getMovementRadius(), getMovmentRadiusMax());
			lastMovementSpeedModificator = (toMouseRadius - getMovementRadius()) / (movementRadiusMax - getMovementRadius());


			updatePosition(dt, infNorm*toMouseRadius);
			updateRotation(dt, influence);

			influence *= influenceFall;
		}

	}*/
}