#include <Re\Game\Effect\Health\EffectDamageOnCollision.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\Effect\Health\EffectHealth.h>
#include <Re\Game\Effect\Physics\EffectFixture.h>
#include <Re\Game\Effect\Physics\EffectRigidbody.h>

namespace Effect
{
	DamageOnCollision::DamageOnCollision(float32 _damage, float32 _bleed, EMode _mode)
		: damage(_damage), bleed(_bleed), mode(_mode)
	{
	}

	bool DamageOnCollision::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Rigidbody*>(potentialParent) && dynamic_cast<Fixture*>(potentialParent);
	}

	void DamageOnCollision::onCollisionEnter(Game::Actor & other, b2Contact & contact)
	{
		if (mode == enter)
		{
			if (allowedToDeal(other, contact))
			{
				auto dmgEffect = other.getEffect<Health>();
				if (dmgEffect)
				{
					dmgEffect->damage(damage, this, bleed);
				}
			}
		}
	}

	void DamageOnCollision::onCollisionExit(Game::Actor & other, b2Contact & contact)
	{
		if (mode == exit)
		{
			if (allowedToDeal(other, contact))
			{
				auto dmgEffect = other.getEffect<Health>();
				if (dmgEffect)
				{
					dmgEffect->damage(damage, this, bleed);
				}
			}
		}
	}

	/*void DamageOnCollision::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save<float32>("damage", damage, 1.f);
		saver.save<float32>("bleed", bleed, 1.f);

		//if (mode == EMode::enter)
		//	saver.save<string>("mode", "enter");
		//else 
		if (mode == EMode::exit)
			saver.save<string>("mode", "enter");

		Super::serialiseF(file, saver);
	}

	void DamageOnCollision::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		damage = loader.load<float32>("damage", 1.f);
		bleed = loader.load<float32>("bleed", 1.f);
		std::string sMode = loader.load<string>("mode", "enter");
		
		if (sMode == "enter")
			mode = EMode::enter;
		else if (sMode == "exit")
			mode = EMode::exit;
		else
			cerr << "DamageOnCollision: damage mode = \"" << sMode << "\" is invaid" << std::endl;

		Super::deserialiseF(file, loader);
	}*/

}