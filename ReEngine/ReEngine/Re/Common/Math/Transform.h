#pragma once
#include <Re\Common\Math\Vector2D.h>
#include <Re\Common\Math\Angle.h>

namespace Math
{

	/// class for representing location and orientation of entites within game world
	/// simplified version of sfml class Transformable
	
	/// WIP
	class Transform
	{
	public:
		Transform();

		Vector2D getPosition() const { return position; }
		void getPosition(Vector2D& ret) const { ret = position; }
		void setPosition(const Vector2D& s) { position = s; needToUpdateTransform = true; }

		Vector2D getScale() const { return scale; }
		void getScale(Vector2D& ret) const { ret = scale; }
		void setScale(const Vector2D& s) { scale = s; needToUpdateTransform = true; }

		Angle getRotation() const { return rotation; }
		void getRotation(Angle& ret) const { ret = rotation; }
		void setRotation(const Angle& s) { rotation = s; needToUpdateTransform = true; }

		Vector2D transformPoint(const Vector2D& in) const
		{
			updateTransform();
			return transform.transformPoint(in.x, in.y);
		}
		sf::Transform getTransform() const
		{
			updateTransform();
			return transform;
		}

	private:
		mutable sf::Transform transform;
		Vector2D position;
		Vector2D scale;
		Angle rotation;
		mutable bool needToUpdateTransform : 1;

		void updateTransform() const;
	};
}