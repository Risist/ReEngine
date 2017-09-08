#include <Re\Game\Effect\Movement\EffectMotor.h>
#include <Re\Game\GameActor.h>

namespace Effect
{
	Motor::Motor(float32 _movementSpeed, Angle _angleOffset)
		: movementSpeed(_movementSpeed), angleOffset(_angleOffset)
	{
	}

	bool Motor::canBeParent(Base * potential) const
	{
		return dynamic_cast<Game::Actor*>(potential);
	}

	void Motor::onUpdate(sf::Time dt)
	{
		if (getActor()->getRigidbody())
		{
			getActor()->getRigidbody()->ApplyForceToCenter(
				Vector2D(0, -movementSpeed*dt.asSeconds() * 1000).getRotated(
					getActor()->getRotation() + angleOffset
				), true
			);
		}
		else
		{
			getActor()->setPosition( getActor()->getPosition() + 
				Vector2D(0, -movementSpeed*dt.asSeconds() * 1000).getRotated(
					getActor()->getRotation() + angleOffset )
			);
		}
	}
	/*void Motor::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
		saver.save<float32>("angleOffset", angleOffset.asDegree() ,0.f);
		saver.save<float32>("speed", movementSpeed, 0.f);
	}
	void Motor::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		angleOffset = Degree(loader.load<float32>("angleOffset", 0.f));
		movementSpeed = loader.load<float32>("speed", 0.f);
	}*/
}