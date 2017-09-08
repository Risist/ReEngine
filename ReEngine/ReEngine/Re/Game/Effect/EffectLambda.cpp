#include <Re\Game\Effect\EffectLambda.h>


namespace Effect
{


	/**
	Lambda::Lambda(
		const onInit_t & __onInit,
		const onSpawn_t & __onSpawn,
		const onUpdate_t & __onUpdate,
		const onDeath_t & __onDeath,
		const onCollisionEnter_t & __onCollisionEnter,
		const onCollisionExit_t & __onCollisionExit,
		const shouldCollide_t & __shouldCollide) :
			_onInit(__onInit),
			_onSpawn(__onSpawn),
			_onUpdate(__onUpdate),
			_onDeath(__onDeath),
			_onCollisionEnter(__onCollisionEnter),
			_onCollisionExit(__onCollisionExit),
			_shouldCollide(__shouldCollide)
	{
	}

	void Lambda::onInit()
	{
		Base::onInit();
		_onInit();
	}

	void Lambda::onSpawn()
	{
		Base::onSpawn();
		_onSpawn();
	}

	void Lambda::onUpdate(sf::Time dt)
	{
		Base::onUpdate(dt);
		_onUpdate(dt);
	}

	bool Lambda::onAgony(sf::Time dt)
	{
		bool b = Base::onAgony(dt);
		return _onDeath(dt) && b;
	}

	void Lambda::onCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
		Base::onCollisionEnter(otherActor,contact);
		_onCollisionEnter(otherActor, contact);
	}

	void Lambda::onCollisionExit(Game::Actor & otherActor, b2Contact & contact)
	{
		Base::onCollisionExit(otherActor, contact);
		_onCollisionExit(otherActor, contact);
	}

	bool Lambda::shouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		return _shouldCollide(myFixture, otherFixture) &&
			Base::shouldCollide(myFixture, otherFixture);
	}


	/// defaults 

	void Lambda::defaultOnInit()
	{
	}

	void Lambda::defaultOnSpawn()
	{
	}

	void Lambda::defaultOnUpdate(sf::Time dt)
	{
	}

	bool Lambda::defaultOnDeath(sf::Time dt)
	{
		return true;
	}

	void Lambda::defaultOnCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
	}

	void Lambda::defaultOnCollisionExit(Game::Actor & otherActor, b2Contact & contact)
	{
	}

	bool Lambda::defaultShouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		return true;
	}*/
}