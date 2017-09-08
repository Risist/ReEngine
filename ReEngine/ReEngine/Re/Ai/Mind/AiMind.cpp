#include <Re\Ai\Mind\AiMind.h>

namespace Ai
{
	/////////////////////////////////
	Mind::Mind()
	{
		for (int i = 0; i < MEMORY_SIZE; ++i)
			behaviourMemory[i] = nullptr;
	}

	Mind::~Mind()
	{
		for (auto it : behaviours)
			delete it;
	}


	void Mind::onUpdate(sf::Time dt)
	{
		if (!actualBehaviour || 
			/// execute behaviour
			actualBehaviour->onExecute(dt) )
			/// set up new behaviour 
		{
			if (actualBehaviour)
				actualBehaviour->onExit();

			/// fill chances vector
			assert(behaviours.size() == chance.chances.size());
			size_t size = behaviours.size();
			Utility_t helperValue;
			for (int i = 0; i < size; ++i)
			{
				helperValue = behaviours[i]->getUtility();
				chance.chances[i] = helperValue > treshold ? helperValue : 0;
			}

			/// choose new behaviour
			size_t id = chance.randId();
			actualBehaviour = behaviours[id];
			actualBehaviour->onStart();

			/// update memory
			behaviourMemory[4] = behaviourMemory[3];
			behaviourMemory[3] = behaviourMemory[2];
			behaviourMemory[2] = behaviourMemory[1];
			behaviourMemory[1] = behaviourMemory[0];
			behaviourMemory[0] = actualBehaviour;
		}

	}

	void Mind::setBehaviour(BehaviourBase * s)
	{
		if (actualBehaviour)
			actualBehaviour->onExit();
		actualBehaviour = s;
		actualBehaviour->onStart();

		/// update memory
		behaviourMemory[4] = behaviourMemory[3];
		behaviourMemory[3] = behaviourMemory[2];
		behaviourMemory[2] = behaviourMemory[1];
		behaviourMemory[1] = behaviourMemory[0];
		behaviourMemory[0] = actualBehaviour;
	}

	void Mind::setBehaviour(size_t id)
	{
		if (actualBehaviour)
			actualBehaviour->onExit();
		actualBehaviour = behaviours[id];
		actualBehaviour->onStart();

		/// update memory
		behaviourMemory[4] = behaviourMemory[3];
		behaviourMemory[3] = behaviourMemory[2];
		behaviourMemory[2] = behaviourMemory[1];
		behaviourMemory[1] = behaviourMemory[0];
		behaviourMemory[0] = actualBehaviour;
	}

	void Mind::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/// TODO
	}

	void Mind::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		treshold = loader.load("treshold", 0.f);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			loader.load<string>("name", "");
		}
	}





////////////////////////////////////////////////////////////////////////

	void BehaviourBase::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
	}
	void BehaviourBase::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
	}



}