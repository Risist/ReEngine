#pragma once
#include <Re\Game\Effect\EffectBase.h>
#include <Re\Game\Effect\EffectTransformable.h>

namespace Effect
{
	class Rigidbody;
}


namespace Game
{

	class World;

	class Actor : public Effect::Transformable
	{
	public:
		MULTI_SERIALISATION_INTERFACE(Actor);

		Actor();
		virtual ~Actor() = default;

	public:
		/// name of the actor, a way to identify it in runtime
		std::string name;

		bool isAlive() const { return bAlive; }
		
		/// kills the actor
		void markAsDead()
		{
			if(bAlive)
			{
				bAlive = false;
				onDeath();
			}
		}
		/// brings the actor again to live (if dead)
		void respawn()
		{
			if (!bAlive)
			{
				bAlive = true;
				onRespawn();
			}
		}


		/// function should be called every frame
		/// chooses right form of updating object state
		///	@param:dt		delta of time elapsed between frames
		bool onFrame(sf::Time dt);

		
		/// an actor mentally responsible on this one, 
		Actor* instigator{ nullptr };

	public:
		b2Body* getRigidbody() const { assert(rigidbody); return rigidbody; };
		
		Game::World* getWorld() const { assert(world); return world; }

	private:

			/// main rigidbody, hich actor is sync to
			/// there is only possibility for one rigidbody at the time to sync transform to rigidbody
		b2Body* rigidbody{ nullptr };
		friend class Effect::Rigidbody;

		/// ptr to world actor is currently in
		/// seted after onInit event 
		Game::World* world;
		friend class Game::World;

		/// whether or not to update normally.
		/// if equal to true onUpdate event is called every frame
		/// otherwise onAgony, which gives possiblility of destroing actor
		bool bAlive : 1;
		
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};

}