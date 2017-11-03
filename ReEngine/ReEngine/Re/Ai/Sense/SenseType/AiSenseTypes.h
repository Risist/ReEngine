#pragma once
#include <Re\Ai\Sense\AiSenseBasic.h>

namespace Ai
{

	/// checks whether is something on the road from owner to aim
	/// WIP
	class SightSense : public Sense
	{
	protected:
		/// called when the potential actor is within one of filters
		/// put here addictional checks & update of sense state
		virtual bool isSensedF(Game::Actor* potential);
	};


}