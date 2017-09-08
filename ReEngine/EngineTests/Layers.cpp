#include "Layers.h"
#include <Re\Game\GameWorld.h>

namespace Game
{
	namespace Layers
	{
		void init()
		{
			background = world.addNewDisplayLayer();
			blood = world.addNewDisplayLayer();
			bullet = world.addNewDisplayLayer();
			obstacle = world.addNewDisplayLayer();
			character = world.addNewDisplayLayer();
		}

		Layer* background = nullptr;
		Layer* blood = nullptr;
		Layer* bullet = nullptr;
		Layer* obstacle = nullptr;
		Layer* character = nullptr;
	}
}