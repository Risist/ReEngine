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

		/// creates new actor and then adds to world actor list
		template<class Act = Game::Actor>
		Act* createActor();

		template<class Act = Game::Actor>
		Act* insertActor( Act* _new);

	public:
		void debugDisplayPhysics(Color clNotColliding, Color clColliding);
		
		/// removes all actors from the world
		void clear();

		///
		void queryAABB(const Vector2D& loverBound, const Vector2D& upperBound, function<bool(b2Fixture*)> callback);
		void raycast(const Vector2D& p1, const Vector2D& p2, function<float32(const RaycastResult&)> callback);
		
		/// creates new display layer
		/// returns ptr to newly created layer
		Layer* addNewDisplayLayer()
		{
			displayLayers.push_back(make_unique<Layer>());
			return displayLayers.back().get();
		}
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
	inline Act * World::insertActor(Act * _new)
	{
		assert(_new);

		actorsToAdd.push_back(unique_ptr<Actor>(_new));
		_new->world = this;
		_new->onInit();

		return _new;
	}
}