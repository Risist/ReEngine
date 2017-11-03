#pragma once
#include <Re\Ai\Sense\AiSenseBasic.h>
#include <Re\Common\Math\Math.h>

namespace Ai
{
	/// Sense emtites in circle 
	class SenseFilterCircle : public Ai::SenseFilter
	{
	public:
		SenseFilterCircle(float32 radius, const Vector2D& offset = Vector2D());
		
		/// override

		virtual bool isSensed(const Game::Actor* potential) const override;
		virtual b2AABB getSenseArea() const override;


	private:
		/// how big is the filter circle?
		float32 radius;
		/// offset in center of filter from a owner position relative to owner's rotation
		Vector2D offset;
	};


	/// WIP
	class SenseFilterCone : public Ai::SenseFilterCircle
	{
	public:
		virtual bool isSensed(const Game::Actor* potential) const override;
		
	private:
		Angle angleMin;
		Angle angleMax;
	};


}