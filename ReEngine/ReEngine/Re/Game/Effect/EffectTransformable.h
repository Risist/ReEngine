#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{

	/// non-relative transformation component
	/// allows to hold data about position and rotation and gives some utility functions to manipulate them
	/// 
	class Transformable : public Composite, public sf::Transformable
	{
		SERIALISATION_NAME(Transformable)
	public:

		Transformable(const Vector2D& _position = Vector2D(), Angle _rotation = Angle::zero)
		{
			setPosition(_position);
			setRotation(_rotation);
		}

		/// override
		virtual bool canBeParent(Base* potentialParent) const override;

		/// position
		Vector2D getPosition() const { return Vector2D(sf::Transformable::getPosition()); }
		Angle getRotation() const { return Degree(sf::Transformable::getRotation());  }

		void setPosition(const Vector2D& s) { sf::Transformable::setPosition(s.x, s.y); }
		void setRotation(Angle s) { sf::Transformable::setRotation(s.asDegree()); }

		/// utility functions: translate

		void translateTowards(const Vector2D& destination, float32 speed)
		{
			Vector2D toDestination = destination - getPosition();
			setPosition(getPosition()+ toDestination.getNormalised()*speed);
		}
		bool translateTowards(const Vector2D& destination, float32 speed, float32 arriveRadius)
		{
			Vector2D toDestination = destination - getPosition();
			if (toDestination.getLenghtSq() > arriveRadius*arriveRadius)
			{
				setPosition( getPosition() + toDestination.getNormalised()*speed);
				return false;
			}
			else
				return true;
		}
		bool translateTowardsIdeal(const Vector2D& destination, float32 speed, float32 arriveRadius)
		{
			Vector2D toDestination = destination - getPosition();
			if (toDestination.getLenghtSq() > arriveRadius*arriveRadius)
			{
				setPosition( getPosition() + toDestination.getNormalised()*speed);
				return false;
			}
			else
			{
				setPosition(destination);
				return true;
			}
		}

		void translateTowards(const Transformable& destination, float32 speed)
		{
			Vector2D toDestination = destination.getPosition() - getPosition();
			setPosition(getPosition() + toDestination.getNormalised()*speed);
		}
		bool translateTowards(const Transformable& destination, float32 speed, float32 arriveRadius)
		{
			Vector2D toDestination = destination.getPosition() - getPosition();
			if (toDestination.getLenghtSq() > arriveRadius*arriveRadius)
			{
				setPosition( getPosition() + toDestination.getNormalised()*speed);
				return false;
			}
			else
				return true;
		}
		bool translateTowardsIdeal(const Transformable& destination, float32 speed, float32 arriveRadius)
		{
			Vector2D toDestination = destination.getPosition() - getPosition();
			if (toDestination.getLenghtSq() > arriveRadius*arriveRadius)
			{
				setPosition( getPosition() + toDestination.getNormalised()*speed);
				return false;
			}
			else
			{
				setPosition(destination.getPosition());
				return true;
			}
		}

		/// utility functions: rotate

		bool rotateTowards(Angle desired, Angle speed, Angle minDifference)
		{
			Angle toDesired = desired - getRotation();
			if (toDesired > Angle::zero )
			{
				if (toDesired < minDifference)
				{
					setRotation(getRotation() - speed);
					return false;
				}
			}
			else
			{
				if (-toDesired < minDifference)
				{
					setRotation(getRotation() + speed);
					return false;
				}
			}
			return true;
		}
		bool rotateTowardsIdeal(Angle desired, Angle speed, Angle minDifference)
		{
			Angle toDesired = desired - getRotation();
			if (toDesired > Angle::zero)
			{
				if (toDesired < minDifference)
				{
					setRotation( getRotation() - speed);
					return false;
				}
			}
			else
			{
				if (-toDesired < minDifference)
				{
					setRotation(getRotation() + speed);
					return false;
				}
			}

			setRotation(desired);
			return true;
		}

		bool rotateTowards(const Vector2D& destination, Angle speed, Angle minDifference)
		{
			Vector2D toDestination = destination - getPosition();
			return rotateTowards(toDestination.angle(), speed, minDifference);
		}
		bool rotateTowardsIdeal(const Vector2D& destination, Angle speed, Angle minDifference)
		{
			Vector2D toDestination = destination - getPosition();
			return rotateTowardsIdeal(toDestination.angle(), speed, minDifference);
		}

		bool rotateTowards(const Transformable& destination, Angle speed, Angle minDifference)
		{
			Vector2D toDestination = destination.getPosition() - getPosition();
			return rotateTowards(toDestination.angle(), speed, minDifference);
		}
		bool rotateTowardsIdeal(const Transformable& destination, Angle speed, Angle minDifference)
		{
			Vector2D toDestination = destination.getPosition() - getPosition();
			return rotateTowardsIdeal(toDestination.angle(), speed, minDifference);
		}

	protected:
		/// serialisation functions - to allow effects to be sierialised from/into .res files
		//virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver)  const override;
		//virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}
