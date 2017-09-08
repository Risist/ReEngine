#pragma once

#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{
	
	/*
	Makes camera follow a Transformable (by default parent of the effect)
	allows to smooth transition
	@parent: a Effect::Transformable* 
	*/
	class FollowCamera final: public Base
	{
		SERIALISATION_NAME(FollowCamera)
	public:
		FollowCamera();
		
		////// events

		virtual bool canBeParent(Base* potentialParent) const override;
		
		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		////// setters
		FollowCamera* setAddictionalRotation(Angle add)
		{
			addictionalRotation = add;
			return this;
		}
		FollowCamera* setSmooth(float32 sPosition, float32 sRotation)
		{
			smoothness.x = sPosition;
			smoothness.y = sRotation;
			return this;
		}
		FollowCamera* setOffset(Vector2D s)
		{
			offset = s;
			return this;
		}
		FollowCamera* setUpdateTarget(sf::Transformable* s)
		{
			updateTarget = s;
			return this;
		}

		/// camera's offset in position to transformable parent
		Vector2D offset;
		/// x - smoothness in position
		/// y - smoothness in rotation
		Vector2D smoothness;
		/// offset in rotation to target transformable
		Angle addictionalRotation;
		/// target to which update camera
		/// default one is Transformable parent
		sf::Transformable *updateTarget{nullptr};
	/*protected:
		virtual void serialiseF(std::ostream&file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream&file, Res::DataScriptLoader& loader)override;*/
	};

}