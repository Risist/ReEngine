#include "EfectLightSource.h"

namespace Efect
{
	LightSource::LightSource(float _fullLightDistance, float _intensitivityFall, float _maxIntensitivityRatio)
		: fullLightDistance(_fullLightDistance), intensitivityFall(_intensitivityFall), maxIntensitivityRatio(_maxIntensitivityRatio)
	{
	}


	void LightSource::onInit()
	{
		Base::onInit();
	}

	void LightSource::onUpdate(sf::Time dt)
	{
		Base::onUpdate(dt);

		Graphics::lightController.checkLightSource(getOwner(), fullLightDistance, intensitivityFall, maxIntensitivityRatio);
	}
}