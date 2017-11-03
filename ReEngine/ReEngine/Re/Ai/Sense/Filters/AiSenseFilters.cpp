#include <Re\Ai\Sense\Filters\AiSenseFilters.h>
#include <Re\Game\GameActor.h>

namespace Ai
{

	SenseFilterCircle::SenseFilterCircle(float32 _radius, const Vector2D & _offset)
		: radius(_radius), offset(_offset)
	{
	}

	bool SenseFilterCircle::isSensed(const Game::Actor * potential) const
	{
		return  (getOwner()->transformPoint(offset) 
					-potential->getPosition() )
			.getLenghtSq()  < radius*radius;
	}

	b2AABB SenseFilterCircle::getSenseArea() const
	{
		Vector2D center = getOwner()->transformPoint(offset);
		b2AABB aabb;
		aabb.lowerBound.x = center.x - radius;
		aabb.lowerBound.x = center.y - radius;
		aabb.upperBound.x = center.x - radius;
		aabb.upperBound.y = center.y - radius;
		return aabb;
	}


	////////////////////////////

	bool SenseFilterCone::isSensed(const Game::Actor * potential) const
	{
		return SenseFilterCircle::isSensed(potential) && true; /// TODO
	}

}