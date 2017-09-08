#include <Re\Game\Effect\Movement\Player\EffectMouseMovement.h>
#include <Re\Game\Game.h>
#include <Re\Graphics\Camera.h>

extern RenderWindow wnd;

namespace Effect
{
	MouseMovement::MouseMovement(float32 _movementSpeed)
		: MovementAim(_movementSpeed)
	{
	}
	void MouseMovement::onInit()
	{
		Super::onInit();
		setKey("press");
	}
	void MouseMovement::onUpdate(sf::Time dt)
	{
		assert(pressKey);

		if (pressKey->isReady())
		{
			destination = cam.mapPixelToCoords(sf::Mouse::getPosition(wnd));
		}

		if ((destination - getActor()->getPosition()).getLenghtSq() < getMinimalDistance()*getMinimalDistance())
			stop();
		else
			setDestination(destination);

		Super::onUpdate(dt);
	}
	MouseMovement * MouseMovement::setKey(const std::string & keyCode)
	{
		pressKey = getActor()->getInputKey(keyCode);
		return this;
	}
	/*void MouseMovement::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
	}
	void MouseMovement::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		/// TODO serialisation of key
	}*/
}