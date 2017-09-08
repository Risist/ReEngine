#include <Re\Game\Effect\Movement\EffectMovementAim.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\Effect\Physics\EffectRigidbody.h>

namespace Effect
{
	MovementAim::MovementAim(float32 _movementSpeed)
		: movementSpeed(_movementSpeed), bAtMove(false)
	{
	}

	bool MovementAim::canBeParent(Effect::Base * potentialParent) const
	{
		return dynamic_cast<Rigidbody*>(potentialParent);
	}

	void MovementAim::onInit()
	{
	}

	void MovementAim::onUpdate(sf::Time dt)
	{
		/// check if influence is strong enough
		if (influence.getLenghtSq() <= minimalDistance*minimalDistance)
		{
			/// stored influence is too low
			stop();
		}

		/// execute movement
		if (bAtMove)
		{

			updatePosition(dt, influence.getNormalised() );
			updateRotation(dt, influence);

			influence *= influenceFall;
		}

	}

	void MovementAim::setDestination(const Vector2D& newDest, float32 influenceScale)
	{
		Vector2D v = (newDest - getActor()->getPosition());
		influence += v*influenceScale;
		bAtMove = true;
	}


	Vector2D MovementAim::getDestination() const
	{
		return influence + (Vector2D)getActor()->getPosition();
	}
	void MovementAim::updateRotation(sf::Time dt, const Vector2D& influence)
	{
		auto rb = ((Rigidbody*)getParent())->getRigidbody();

		Angle dir = influence.angle();
		Angle actual = getActor()->getRotation();

		rb->ApplyAngularImpulse(
			clamp(
				dir.minimalDiffirence(actual) * rotationSmoothness*dt.asSeconds(),
				-rotationSpeedMax,
				rotationSpeedMax
			).asRadian(),
			true
		);
	}
	void MovementAim::updatePosition(sf::Time dt, Vector2D destSpeed)
	{
		auto rb = ((Rigidbody*)getParent())->getRigidbody();
		rb->ApplyForceToCenter(
			destSpeed * movementSpeed*toB2Position*dt.asSeconds() * 1000, true);
	}
	/*void MovementAim::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);

		saver.save<float32>("influenceFall", influenceFall, 0.f);
		saver.save<float32>("minimalDistance", minimalDistance, 50.f);
		saver.save<float32>("movementSpeed", movementSpeed , 1.f);
		saver.save<float32>("rotationSpeedMax", rotationSpeedMax.asDegree(), numeric_limits<float32>::max());
		saver.save<float32>("rotationSmoothness", rotationSmoothness, 1.f);

	}
	void MovementAim::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		
		influenceFall = loader.load<float32>("influenceFall", 0.f);
		minimalDistance = loader.load<float32>("minimalDistance", 50.f);
		movementSpeed = loader.load<float32>("movementSpeed", 1.f);
		rotationSpeedMax = Degree(loader.load<float32>("rotationSpeedMax", numeric_limits<float32>::max()));
		rotationSmoothness = loader.load<float32>("rotationSmoothness", 1.f);
	}*/
}