#include <Re\Game\Effect\Health\EffectDeathControll.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\Effect\Physics\EffectFixture.h>


namespace Effect
{
	////////////////////////// Respawn after a while

	RespawnAfterAWhile::RespawnAfterAWhile(sf::Time timeToRespawn, function<bool()> _canLive)
		: timer(timeToRespawn), canLive(_canLive)
	{

	}

	bool RespawnAfterAWhile::canBeParent(Base * potential) const
	{
		return dynamic_cast<Game::Actor*>(potential);
	}

	void RespawnAfterAWhile::onDeath()
	{
		Super::onDeath();
		timer.restart();
	}

	bool RespawnAfterAWhile::onAgony(sf::Time dt)
	{
		Super::onAgony(dt);
		if (timer.isReady() && canLive())
			getActor()->respawn();

		/// block deletion
		return false;
	}

	/*void RespawnAfterAWhile::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		timer.serialise(file, saver);
		Super::serialiseF(file, saver);
	}

	void RespawnAfterAWhile::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		timer.deserialise(file, loader);
		Super::deserialiseF(file, loader);
	}*/


	////////////////////////// die after a while
	DieAfterAWhile::DieAfterAWhile(sf::Time lifeTime, function<bool()> _canDie)
		: timer(lifeTime), canDie(_canDie)
	{

	}

	bool DieAfterAWhile::canBeParent(Base * potential) const
	{
		return dynamic_cast<Game::Actor*>(potential);
	}

	void DieAfterAWhile::onRespawn()
	{
		Super::onRespawn();
		timer.restart();
	}

	void DieAfterAWhile::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);
		if (timer.isReady() && canDie() )
			getActor()->markAsDead();
	}

	/*void DieAfterAWhile::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		timer.serialise(file, saver);
		Super::serialiseF(file, saver);
	}

	void DieAfterAWhile::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		timer.deserialise(file, loader);
		Super::deserialiseF(file, loader);
	}*/

	////////////////////////// die on collision

	DieOnCollision::DieOnCollision(EPhase _phase, function<bool(Game::Actor&, b2Contact&)> _canDie)
		: phase(_phase), canDie(_canDie)
	{

	}


	bool DieOnCollision::canBeParent(Base * potential) const
	{
		return dynamic_cast<Effect::Fixture*>(potential) || dynamic_cast<Effect::Rigidbody*>(potential);
	}

	void DieOnCollision::onCollisionEnter(Game::Actor & other, b2Contact & collision)
	{
		Super::onCollisionEnter(other, collision);
		if (phase == EPhase::enter && collision.GetFixtureB()->IsSensor() == false)
			if(canDie(other, collision))
				getActor()->markAsDead();
	}

	void DieOnCollision::onCollisionExit(Game::Actor & other, b2Contact & collision)
	{
		Super::onCollisionExit(other, collision);
		if (phase == EPhase::exit && collision.GetFixtureB()->IsSensor() == false)
			if (canDie(other, collision))
				getActor()->markAsDead();
	}

	/*void DieOnCollision::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
		//if (phase == EPhase::enter)
			//saver.save<string>("phase", "enter");
		//else 
		if (phase == EPhase::exit)
			saver.save<string>("phase", "exit");
	}

	void DieOnCollision::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		std::string sPhase = loader.load<string>("phase", "enter");
		if (sPhase == "exit")
			phase = EPhase::exit;
		else if (sPhase == "enter")
			phase = EPhase::enter;
		else 
			cerr << "Effect::DieOnCollision: phase = \"" << sPhase << "\" is invalid" << endl;
	}*/

	/////////////////////////////// 
}