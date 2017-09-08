#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{
	/*
	Respawns actor after provided delay
	@parent: Game::Actor only
	*/
	class RespawnAfterAWhile final: public Base
	{
		SERIALISATION_NAME(RespawnAfterAWhile)
	public:
		RespawnAfterAWhile(sf::Time timeToRespawn = sf::seconds(1.f), function<bool()> canLive = []() {return true; } );

		////// events

		virtual bool canBeParent(Base* potential) const override;

		/// reset timer
		virtual void onDeath() override;
		/// block deletion and respawn when timer is ready
		virtual bool onAgony(sf::Time dt) override;

		////// data

		/// callback which allows you to specify addictional requirements to respawn
		function<bool()> canLive;
		/// time period to wait
		Control::Timer timer;
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override*/;
	};

	/*
	Marks Actor as dead after some time
	(main usage: bullets)
	@parrent Game::Actor only
	*/
	class DieAfterAWhile final: public Base
	{
		SERIALISATION_NAME(DieAfterAWhile)
	public:
		DieAfterAWhile(sf::Time lifeTime = sf::seconds(1.f), function<bool()> canDie = []() {return true;  });

		////// events

		virtual bool canBeParent(Base* potential) const override;

		/// reset timer
		virtual void onRespawn() override;
		/// block deletion and respawn when timer is ready
		virtual void onUpdate(sf::Time dt) override;

		////// data

		/// callback which allows you to specify addictional requirements to death
		function<bool()> canDie;
		/// time period to wait
		Control::Timer timer;
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};

	/*
	Marks Actor as dead when collides with something
	@parent Effect::Rigidbody or Effect::Fixture (only those calls collision events)
	*/
	class DieOnCollision final: public Base
	{
		SERIALISATION_NAME(DieOnCollision)
	public:
		enum EPhase
		{
			enter,
			exit
		}phase;

		DieOnCollision(EPhase phase = EPhase::enter, 
			function<bool(Game::Actor&,b2Contact&)> canDie = [](Game::Actor& other, b2Contact& collision) {return true; });

		////// events
		virtual bool canBeParent(Base* potential) const override;

		virtual void onCollisionEnter(Game::Actor& other, b2Contact& collision) override;
		virtual void onCollisionExit(Game::Actor& other, b2Contact& collision) override;

		////// data

		/// callback which allows you to specify addictional requirements to death
		function<bool(Game::Actor& other, b2Contact& collision)> canDie;
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};


}