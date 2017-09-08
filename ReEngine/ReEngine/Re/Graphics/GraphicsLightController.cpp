#include <Re\Graphics\GraphicsLightController.h>

namespace Graphics
{
	LightController lightController(nullptr, 0.075f, 1.f);

	LightController::LightController(Game::Actor *_observer, float _minimalLight, float _maximalLight)
		: observer(_observer), minimalLight(_minimalLight), maximalLight(_maximalLight)
	{
	}

	void LightController::update(Camera& cam)
	{
		lastLightIntensitivitySq = bestLightIntensitivitySq;
		// set new darkness level
		cam.setDarkness(
			clamp(
				(float) pow(bestLightIntensitivitySq, powFadeLight)
				, minimalLight, maximalLight)
		);

		// reset Light intensitivity
		bestLightIntensitivitySq = minimalLight * minimalLight;
	}


	void LightController::checkLightSource(Game::Actor *source, float fullLightDistance, float intensitivityFall, float maxIntensitivityRatio)
	{
		// vialidance check
		if (observer == nullptr || source == nullptr)
			return;

		float distanceSq = (observer->getPosition() - source->getPosition()).getLenghtSq();

		if (fullLightDistance * fullLightDistance > distanceSq)
			// in full light range
			checkLightSource(maximalLight*maximalLight*maxIntensitivityRatio *maxIntensitivityRatio);
		else
			// with changing light power
			checkLightSource(

			(maximalLight*maximalLight - (distanceSq - fullLightDistance*fullLightDistance) * intensitivityFall * intensitivityFall)
				*maxIntensitivityRatio *maxIntensitivityRatio
			);
	}
}