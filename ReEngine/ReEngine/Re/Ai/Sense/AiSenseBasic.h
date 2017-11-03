#pragma once
#include <Re\Common\Settings.h>

/// forwards
namespace Game
{
	class Actor;
}


/// Qeneral description of Sense system:
/// 
///		Sense allows actors to get information about their environment through SenseHolder::Query
///		SenseHolder::Query can be set up by functor or lambda expression
///
///		SenseFilter tells the system where to look at, describes an area of potential perception
///		then if actor is filtered class Sense finds out if the actor can be perceived
///				for sight: is anything on the way between sense owner and aim
///				for smell: everything is good
///				for hearing: saves last position of actor withing sense. The more you move the more noise you do
///				ect.
///		keep in mind you can design your own sense/filter types
///
///		at the end SenseHolder handles the whole process on its own. 
///		You should use SenseHolder and then look up what you need more
///
///	@note only actors with rigidbody can be perceived thous b2 collision system usage

namespace Ai
{

	/// defines an area at which actors can be perceived
	/// @note - can only perceive those actors which has rigidbody component
	class SenseFilter
	{
	protected:

		/// returns true if a @potential actor is sensed by the filter
		/// if any filter will detect an actor as within other filters function @isSensed is not called
		virtual bool isSensed(const Game::Actor* potential) const = 0;

		/// get aproximation of an area the filter can sense
		/// used to optimise b2 search of rigidbodies
		virtual b2AABB getSenseArea() const = 0;

		Game::Actor* getOwner() const { return owner; }
	private:
		Game::Actor* owner{nullptr};
		friend class Sense;
		friend class SenseHolder;
	};


	/// defines method of checking whether the actor is perceived
	class Sense
	{
	public:
		/// 
		bool isSensed(Game::Actor* potential);

		/// returns minimal area filters need
		b2AABB getSenseArea() const;
	

		Sense* addFilter(SenseFilter* s)
		{
			filters.push_back(unique_ptr<SenseFilter>(s));
			filters.back()->owner = owner;
			return this;
		}

	protected:
		/// called when the potential actor is within one of filters
		/// put here addictional checks & update of sense state
		virtual bool isSensedF(Game::Actor* potential) = 0;

		Game::Actor* getOwner() const { return owner; }
	
	private:
		/// actor owning the sense
		Game::Actor* owner;

		vector<unique_ptr<SenseFilter>> filters;
		friend class SenseHolder;
	};

	/// main class of the system
	/// manages the whole process
	/// mainly used in Effect::Sense
	class SenseHolder
	{
	public:

		/// Sense::Query is a callback type
		/// if the actor is perceived by a sense then the passed functor is called
		///
		/// Param description:
		///		@actor - perceived actor by the sense query is attached to
		///		@return - if true is returned then the callback will be removed
		typedef std::function<bool(Game::Actor* actor)> Query;


		/// do the whole calculation of sense
		/// expensive operation so try to not call it every frame
		void updateSense();

	public:
		/// setters

		SenseHolder* setOwner(Game::Actor* owner)
		{
			senseType->owner = owner;
			for (auto it = senseType->filters.begin(); it != senseType->filters.begin(); ++it)
				it->get()->owner = owner;
		}
		SenseHolder* addQuery(Query s)
		{
			queries.push_back(s);
			return this;
		}
		SenseHolder* addFilter(SenseFilter* s)
		{
			assert(senseType);
			senseType->addFilter(s);
			return this;
		}
		SenseHolder* setSenseType(Sense* s)
		{
			senseType = unique_ptr<Sense>(s);
			return this;
		}

	private:
		unique_ptr<Sense> senseType;
		vector<Query> queries;
	};
}