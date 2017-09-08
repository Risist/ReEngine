#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{
	/*
	Deals damage to aims hitted by colliders
		if DamageOnCollision is a child of Rigidbody then any colision event from that body 
			will deal damage to others
		if DamageOnCollision is a child of Fixture then any colision event 
			ONLY FROM THAT FIXTURE will deal damage to others
	@parent Effect::Rigidbody or Effect::Fixture
	*/
	class DamageOnCollision final: public Base
	{
		SERIALISATION_NAME(DamageOnCollision)
	public:
		enum EMode
		{
			enter,
			//stay, /// TODO
			exit,
		}mode{ enter };

		DamageOnCollision(float32 damage = 1.f, float32 bleed = 1.f, EMode mode = enter);

	public: /// events
		virtual bool canBeParent(Base* potentialParent) const;

		virtual void onCollisionEnter(Game::Actor& other, b2Contact& contact) override;
		virtual void onCollisionExit(Game::Actor& other, b2Contact& contact) override;

	public: /// setters
		DamageOnCollision* setMode(EMode newMode)
		{
			mode = newMode;
			return this;
		}
		DamageOnCollision* setAllowedToDeal(const function<bool(Game::Actor& other, b2Contact& contact)>& s)
		{
			allowedToDeal = s;
			return this;
		}
		DamageOnCollision* setBleed(float32 s)
		{
			bleed = s;
			return this;
		}
		DamageOnCollision* setDamage(float32 s)
		{
			damage = s;
			return this;
		}


		function<bool(Game::Actor& other, b2Contact& contact)> allowedToDeal{ [](Game::Actor&, b2Contact&) {return true;} };
		float32 damage;
		float32 bleed{1.f};
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)override;*/
	};

}