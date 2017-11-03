#include <Re\Ai\Sense\AiSenseBasic.h>
#include <Re\Game\GameWorld.h>

namespace Ai
{
	bool Sense::isSensed(Game::Actor * potential)
	{
		bool insideFilter = false;
		for (auto it = filters.begin(); it != filters.end(); ++it)
			if (it->get()->isSensed(potential))
			{
				insideFilter = true;
				break;
			}

		return insideFilter && isSensed(potential);
	}

	b2AABB Sense::getSenseArea() const
	{
		/// AABB which will be returned
		b2AABB r;
		for (auto it = filters.begin(); it != filters.end(); ++it)
		{
			b2AABB itAABB = it->get()->getSenseArea();

			r.upperBound.x = std::max(r.upperBound.x, itAABB.upperBound.x);
			r.upperBound.y = std::max(r.upperBound.y, itAABB.upperBound.y);

			r.lowerBound.x = std::min(r.lowerBound.x, itAABB.lowerBound.x);
			r.lowerBound.y = std::min(r.lowerBound.y, itAABB.lowerBound.y);
		}

		return r;
	}

	void SenseHolder::updateSense()
	{
		assert(senseType);
		b2AABB aabb = senseType->getSenseArea();

		Game::world.queryAABB(aabb.lowerBound, aabb.upperBound, 
			[this](b2Fixture* f)
			{
				Game::Actor* actor = (Game::Actor*)f->GetUserData();
				if (senseType->isSensed(actor))
				{
					/// call queries
					for (auto it = queries.begin(); it != queries.end();)
						if ((*it)(actor))
						/// remove on true
							queries.erase(it++);
						else
							++it;
				}
		
				return true;
			}
		);


	}
}