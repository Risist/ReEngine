#include <Re\Game\Efect\Ai\EfectSensor.h>


namespace Efect
{
	Sensor::Sensor(sf::Time refreshRate)
		: refreshCd(refreshRate)
	{
	}
	void Sensor::onUpdate(sf::Time dt)
	{
		if (refreshClock.getElapsedTime() > refreshCd)
		{
			holder.update();
			refreshClock.restart();
		}
	}
}