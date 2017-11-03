#pragma once
#include <Re\Ai\Mind\AiMind.h>
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{

	class Mind : public Base
	{
		SERIALISATION_NAME(Mind)
	public:

		virtual void onUpdate(sf::Time dt) override;

		/// adds new possible behaviour
		Mind* addBehaviour(Ai::BehaviourBase* behaviour, const string name = "")
		{
			mind.addBehaviour(behaviour, name);
			return this;
		}
		/// adds new behavoiour and sets it as actual one
		Mind* setNewBehaviour(Ai::BehaviourBase* behaviour, const string name = "")
		{
			mind.setNewBehaviour(behaviour, name);
			return this;
		}

		/// 
		Mind* setTreshold(Ai::Utility_t s)
		{
			mind.treshold = s;
			return this;
		}

		/// returns how much behaviours are remembered
		size_t getMemorySize() const
		{
			return mind.getMemorySize();
		}

		Ai::BehaviourBase* getFromMemory(size_t pastTime)
		{
			return mind.getFromMemory(pastTime);
		}
		const Ai::BehaviourBase* getFromMemory(size_t pastTime) const
		{
			return mind.getFromMemory(pastTime);
		}

	private:
		Ai::Mind mind;
	};
}