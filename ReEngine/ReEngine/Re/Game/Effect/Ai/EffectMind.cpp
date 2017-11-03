#include <Re\Game\Effect\Ai\EffectMind.h>

namespace Effect
{

	void Mind::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);
		mind.onUpdate(dt);
	}

}