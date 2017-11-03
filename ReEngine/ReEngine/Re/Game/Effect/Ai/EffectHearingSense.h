#pragma once
#include <Re\Game\Effect\EffectBase.h>

/// WIP

namespace Effect
{
	namespace Data
	{
		/// describes fircular area where sound is heared
		struct NoiseData
		{
			Vector2D noisePosition; ///< where the sound happened
			float32 hearingRadius;	///< base radi actors can hear the cound, moddified by hearing strenght of the actor
		};

		//extern vector<NoiseData> noise;
	}

	/**
	Effect which generates a noise under certain conditions
	Then other components can
	/**/
	class NoiseGenerator : public Base
	{
		SERIALISATION_NAME(NoiseGenerator)
	public:

		virtual bool canBeChildOf(Base* potentialParent) const override;

		virtual void onUpdate(sf::Time dt) override;



	protected:
		std::function<bool()> noiseCondition;
	};

	/**
	Effect which detects noise generated bu other actors and allow to take an action on the information
	/**/
	class HearingSense : public Base
	{
		SERIALISATION_NAME(HearingSense)
	public:

		virtual bool canBeChildOf(Base* potentialParent) const override;

		virtual void onUpdate(sf::Time dt) override;



		typedef std::function<bool(Game::Actor* actor)> Query;

		vector<Query> queries;
	};

}