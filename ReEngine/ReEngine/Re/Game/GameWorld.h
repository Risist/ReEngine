#pragma once
//#include <Re\Common\utility.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\GameLayer.h>

namespace Game
{

	struct RaycastResult
	{
		Actor* actor;			/// actor responsible for hitted fixture
		b2Fixture* fixture;		/// fixture on the path of the ray
		Vector2D point;			/// point on which collision with ray occured
		Vector2D normal;		/// normal vector to the surface of hitted fixture
		float32 fraction;		/// fraction part - how far from the beggining of the ray, in range [0,1]
	};

	class World : 
		//public Res::ISerialisable,
		private b2ContactFilter, 
		private b2ContactListener,
		private b2DestructionListener
	{
	public:
		World();
		~World();
		
		/// @summary updates physics and all actors
		/// should be called every frame
		/// @param:dt		time elapsed between frames
		void onFrame(sf::Time dt);


	public:
		/// creates new actor and then adds to world actor list
		template<class Act = Game::Actor>
		Act* createActor();

		/// creates new actor and spawns it on the position taken as an argument
		template<class Act = Game::Actor>
		Act* createActor(const Math::Transform& relativeTo, float32 offset, Angle angle = Angle::zero);

		/// creates new actor and spawns it on the transform location taken as arguments
		template<class Act = Game::Actor>
		Act* createActor(const Vector2D& position, Angle rotation = Angle::zero );

		/// creates new actor and spawns it on the transform location taken as argument
		template<class Act = Game::Actor>
		Act* createActor(Math::Transform& newTransform)
		{
			return createActor<Act>(newTransform.getPosition(), newTransform.rotation);
		}

		/// insertts an actor created somewhere else
		/// @Warring soon creation of actors will be able only from World class
		///		purpose of the function will be only for respawning released world members
		template<class Act = Game::Actor>
		Act* insertActor( Act* _new);

		/// TODO releaseActor - function/mechanism which returns ptr to actor and removes it from world actor list
		/// to be able to insert the actor again - performance

	public:
		void debugDisplayPhysics(Color clNotColliding, Color clColliding);
		
		/// removes all actors from the world
		void clear();

		/// callback function to detect all physical bodies within passed as an argument AABB
		/// @param lowerBounds, upperBounds : vectors whic describes an area to check
		/// @param callback : function which will take acton on every fixture found
		///			returns false to stop futher checking for other fixtures
		void queryAABB(const Vector2D& lowerBound, const Vector2D& upperBound, function<bool(b2Fixture*)> callback);
		/// sends ray from p1 to p2 and calls function on every fixture on the way
		/// @param p1, p2 : describes ray, from p1 to p2
		/// @param callback: calls the function on every actor found on the way of ray.
		///			@return -1 to filter, 0 to terminate, fraction to clip the ray for
		///			closest hit, 1 to continue
		void raycast(const Vector2D& p1, const Vector2D& p2, function<float32(const RaycastResult&)> callback);
		
		/// creates new display layer
		/// returns ptr to newly created layer
		Layer* addNewDisplayLayer()
		{
			displayLayers.push_back(make_unique<Layer>());
			return displayLayers.back().get();
		}
		/// returns layer described by an id
		Layer* getDisplayLayerById(size_t id) const
		{
			assert(displayLayers.size() > id);
			return displayLayers[id].get();
		}
		
		vector<unique_ptr<Actor>> actors;
		b2World physicsWorld;
	private:
		vector<unique_ptr<Actor>> actorsToAdd;

		/// in order to call "onDipsplay"/ "onUpdate"/ "onAgony" events effect have to be assigned to a layer
		/// layer with id 0 is created by default
		std::vector<unique_ptr<Game::Layer>> displayLayers;
		
	private: // box2d callbacks
		/// @Note serialisation works only with actors 
		///			physics is not saved (even only by settings of efects)
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
	
		virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB) override;

		virtual void SayGoodbye(b2Joint* joint);
		virtual void SayGoodbye(b2Fixture* fixture);
		
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver)const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};
	extern World world;


	template<class Act >
	Act* World::createActor()
	{
		Act* _new = new Act();
		return insertActor<Act>(_new);
	}
	template<class Act>
	inline Act * World::createActor(const Math::Transform & relativeTo, float32 offset, Angle angle)
	{
		Angle a = angle + relativeTo.getRotation();
		return createActor<Act>( relativeTo.getPosition() + offset.getRotated(a), a);
	}
	template<class Act>
	inline Act * World::createActor(const Vector2D& position, Angle rotation)
	{
		auto ac = createActor<Act>();
		if (ac->getRigidbody())
			ac->getRigidbody()->SetTransform(position*toB2Position, rotation.asRadian());
		
		ac->setPosition(position);
		ac->setRotation(rotation);
		return ac;
	}


	template<class Act>
	inline Act * World::insertActor(Act * _new)
	{
		assert(_new);

		actorsToAdd.push_back(unique_ptr<Actor>(_new));
		_new->world = this;
		_new->onInit();

		return _new;
	}
}