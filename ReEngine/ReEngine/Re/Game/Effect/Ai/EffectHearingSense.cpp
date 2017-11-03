#include <Re\Game\Effect\Ai\EffectHearingSense.h>
#include <Re\Game\Effect\EffectTransformable.h>

namespace Effect
{

	bool NoiseGenerator::canBeChildOf(Base* potentialParent) const
	{
		return dynamic_cast<Effect::Transformable*>(potentialParent);
	}


	void NoiseGenerator::onUpdate(sf::Time dt)
	{
	}

	////////////////////


	bool HearingSense::canBeChildOf(Base* potentialParent) const
	{
		return dynamic_cast<Effect::Transformable*>(potentialParent);
	}


	void HearingSense::onUpdate(sf::Time dt)
	{
	}

}