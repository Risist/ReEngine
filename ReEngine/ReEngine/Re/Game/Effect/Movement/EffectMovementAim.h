#pragma once
#include <Re\Game\Effect\EffectBase.h>


namespace Effect
{
	/// Owner will move towards setted destination
	/// when within minimalDistance radius destination is marked as arrived
	/// and waits for new destination
	/// @requires rigidbody
	class MovementAim : public Base
	{
		SERIALISATION_NAME(MovementAim)
	public:
		MovementAim( float32 movementSpeed = 1.f );

		////// events

		virtual bool canBeParent(Effect::Base* potentialParent) const override;
		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;

		////// using
		void setDestination(const Vector2D& position, float32 influenceScale = 1.f );
		void applyInfluence(const Vector2D& destVersor, float32 influenceScale = 1.f )
		{
			influence += destVersor.getNormalised()*influenceScale;
			bAtMove = true;
		}
		/// applies influence without normalisation
		void applyInfluenceSimple(const Vector2D& add)
		{
			influence += add;
			bAtMove = true;
		}

		/// stops current movement
		void stop()
		{
			influence = Vector2D();
			bAtMove = false;
		}

		////// setters

		MovementAim* setInfluenceFall(float32 s)
		{
			influenceFall = s;
			return this;
		}
		MovementAim* setMinimalDistance(float32 s)
		{
			minimalDistance = s;
			return this;
		}
		MovementAim* setMovementSpeed(float32 s)
		{
			movementSpeed = s;
			return this;
		}
		MovementAim* setRotationSpeedMax(Angle s)
		{
			rotationSpeedMax = s;
			return this;
		}
		MovementAim* setRotationSmoothness(float32 s)
		{
			rotationSmoothness = s;
			return this;
		}

		/////// getters

		Vector2D getInfluence() const { return influence;}
		Vector2D getDestination() const;
		float32 getInfluenceFall() const { return influenceFall; }
		float32 getMinimalDistance() const { return minimalDistance; }
		float32 getMovementSpeed() const { return movementSpeed; }
		Angle getRotationSpeedMax() const { return rotationSpeedMax; }
		float32 getRotationSmoothness() const { return rotationSmoothness; }

		bool isMoving() const { return bAtMove; }

	protected:
		Vector2D influence;
		/// damping of influence
		float32 influenceFall{0.f};
		/// distance at which actor stops moving - to prevent wobby movement
		float32 minimalDistance{50.f};
		/// how fast the actor moves
		float32 movementSpeed{1.f};
		/// rotation speed is scaled - the far from desired angle the biger speed
		/// but rotation speed has maximal value
		Angle rotationSpeedMax{Degree(numeric_limits<float32>::max())};
		/// how much rotation speed will increase in dependency on diffirence from desired angle
		float32 rotationSmoothness{ 1.f };

		/// whether or not Actor is still moving
		int8 bAtMove : 1;
	protected:
		void updateRotation(sf::Time dt, const Vector2D& influence);
		void updatePosition(sf::Time dt, Vector2D destSpeed);

	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};
}