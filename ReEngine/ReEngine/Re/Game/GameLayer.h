#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Game
{

	class World;

	/*
	@brief: stores ptr's to Effects to determine which effects to update
	*/
	class Layer
	{
	public:
		void addEffect(Effect::Base* ptr)
		{
			stored.push_back(ptr);
		}
		bool removeEffect(Effect::Base* ptr)
		{
			for (auto it = stored.begin(); it != stored.end(); ++it)
				if (*it == ptr)
				{
					stored.erase(it);
					return true;
				}

			return false;
		}

	private:
		std::vector<Effect::Base*> stored;
		friend class World;
	};

}