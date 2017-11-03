#pragma once
#include <Re\Game\Effect\Movement\Player\EffectStaticMovement.h>
#include <Re\Common\Control\ControlMouseDrag.h>

namespace Effect
{

	/// TODO

	/// efect that allows to move player forward, backward, strife, and rotate by moving mouse in x axes
	class RotatedMovement : public StaticMovement
	{
		SERIALISATION_NAME(RotatedMovement)
	public:
		RotatedMovement(float32 movementSpeedMax = 1.f);

		/// events

		virtual void onUpdate(sf::Time dt) override;	

		/// setters
		RotatedMovement* setLockRadius(Vector2D& v)
		{
			lockRadius = v;
			return this;
		}
		REDEFINE_SETTER_2(RotatedMovement, setAxis, const string&, const string&);

		/// getters
		Vector2D getLockRadius() const
		{
			return lockRadius;
		}

	protected:
		/// radius in which mouse will be locked onto screan
		/// if is in [0,lockRadius] or [wnd - lockRadius, wnd]
		/// then mouse is swaped in other side
		/// this ensures ability to continued movement of mouse while rotating
		Vector2D lockRadius{ 5,5 };
	private:
		Control::MouseDrag drag;
	};

}