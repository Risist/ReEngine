#pragma once
#include <Re\Graphics\GraphicsLightController.h>

namespace Efect
{
	// the farer light source is from observer the darker is scene
	// if the distance is less than fullLightDistance then is used maximal available intensitivity
	// otherwise intensitivity becomes less the distance is bigger dependinglu on intensitivityFall parametr
	// at 0 intensitivityFall always max available is used
	// at 1 intensitivityFall light is seen only in fullLightDistance
	// last parametr : maxIntensitivityRatio changes power of light source
	// sould be in range of 0 to 1 includive
	class LightSource : public Base
	{
	public:
		LightSource(float fullLightDistance, float intensitivityFall, float maxIntensitivityRatio);

		void onInit() override;
		void onUpdate(sf::Time dt) override;

		LightSource* setFullLightDistatince(float s) { fullLightDistance = s; return this; }
		LightSource* setIntensitivityFall(float s) { intensitivityFall = s; return this; }
		LightSource* setMaxIntensitivityRatio(float s) { maxIntensitivityRatio = s; return this; }

		float fullLightDistance;
		float intensitivityFall;
		float maxIntensitivityRatio;

	};
}