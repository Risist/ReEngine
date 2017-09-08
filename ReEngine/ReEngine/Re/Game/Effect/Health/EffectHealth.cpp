#include <Re\Game\Effect\Health\EffectHealth.h>
#include <Re\Game\GameActor.h>

namespace Effect
{

	Health::Health(float32 maxHealth, float32 percentInitialHealth)
		: max(maxHealth), actual(maxHealth*percentInitialHealth),inverseDefence(1)
	{
	}

	bool Health::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}

	void Health::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);

		actual += regeneration;
		regeneration *= regenerationDamping;
	

		if (actual > max)
			maxReaction(*this);
		else if (actual <= 0)
			getActor()->markAsDead();

	}

	void Health::maxReaction_allign(Effect::Health& health)
	{
		health.actual = health.max;
	}

	void Health::damage(float32 amount, Effect::Base* causer, float32 bleed)
	{
		amount *= -inverseDefence;
		damageReaction(amount, causer);

		actual += amount*(1-bleed);
		regeneration += amount* (bleed);
	}

	void Health::heal(float32 amount, Effect::Base* causer, float32 bleed)
	{
		amount *= inverseDefence;	
		damageReaction(amount, causer);

		actual += amount*(1-bleed);
		regeneration += amount* (bleed);
	}

	

	/*void Health::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);

		saver.save<float32>("inverseDefence", inverseDefence, 1.f);
		saver.save<float32>("max", max , 100.f);
		saver.save<float32>("actual", actual, max);
		saver.save<float32>("regeneration", regeneration, 0.f);
		saver.save<float32>("regenerationDamping", regenerationDamping , 0.5f);
	
		//TODO serialisation of maxMode
	}

	void Health::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file,loader);

		inverseDefence = loader.load<float32>("inverseDefence", 1.f);
		max = loader.load<float32>("max", 100.f);
		actual = loader.load<float32>("actual", max);
		regeneration = loader.load<float32>("regeneration", 0.f);
		regenerationDamping = loader.load<float32>("regenerationDamping", 0.5f);

		//TODO serialisation of maxMode
	}*/

	

}