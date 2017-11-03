#include <Re\Game\Effect\Movement\Player\EffectRadiusMovement.h>
#include <Re\Game\GameActor.h>
#include <Re\Graphics\Camera.h>
#include <Re\Game\Effect\Physics\EffectRigidbody.h>
extern RenderWindow wnd;

namespace Effect
{
	
	
	RadiusMovement::RadiusMovement(float32 _movementSpeedMax)
		: MovementAim(_movementSpeedMax), movementSpeedMax(_movementSpeedMax)
	{
		setMinimalDistance(200.f);
	}

	void RadiusMovement::onInit()
	{
		/// set mouse position to middle screan -> dead zone
		/// in this place character will not move at the begining of the game
		sf::Mouse::setPosition((Vector2D)wnd.getSize()*0.5f, wnd);
	}
	void RadiusMovement::onUpdate(sf::Time dt)
	{
		if (wnd.hasFocus())
		{
			setDestination(cam.mapPixelToCoords(sf::Mouse::getPosition(wnd)));

			setMovementSpeed(clamp(
				( getInfluence().getLenght() - getMinimalDistance())
					/ movementRadiusMax
					, 0.f, movementSpeedMax)
				* movementSpeedMax );
		}
		else
		{
			setMovementSpeed(0);
		}

		Super::onUpdate(dt);
	}
}