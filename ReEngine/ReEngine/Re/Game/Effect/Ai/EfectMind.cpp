#include <Re\Game\Efect\Ai\EfectMind.h>

namespace Efect
{

	void Mind::onUpdate(sf::Time dt)
	{
		Efect::Base::onUpdate(dt);
		mind.onUpdate(dt);
	}

}