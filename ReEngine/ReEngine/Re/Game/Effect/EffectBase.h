#pragma once
#include <Re\Common\utility.h>

namespace Game
{
	class Actor;
}

namespace Effect
{
	/// component-like class for Actors
	class Base ///: public Res::ISerialisable
	{
	public:
		Base();
		Base(const Base&) = delete;
		virtual ~Base() = default;

	public: /// events

		//////// creation

		/// @summary	checks requirements on potential parent. Used to ensure right creation
		/// @note		should be called only in debug mode
		/// @return		whether the potential parent meets requirements
		virtual bool canBeParent(Base* potentialParent) const { return false; }

		/// @summary: called after owner ptr is set up
		virtual void onInit() {}

		/// called once when owner is added to world list
		virtual void onSpawn() {}

		/// called when setActivated changes activation state of the effect
		virtual void onSetActivated() {}
		
		/// called once when the actor returns to live
		/// here should go all code backing settings to initial state
		virtual void onRespawn() {}


		///////// deconstruction

		/// events allowing to do a clean up code on joints and fixtures
		virtual void onDeconstructionJoint(b2Joint* joint) {}
		virtual void onDeconstructionFixture(b2Fixture* fixture) {}

		/// called once when the actor was killed
		virtual void onDeath() {}

		//////////////////// Frame

		/// called every frame while actor is alive
		/// @param:dt			- delta of time elapsed between frames
		virtual void onUpdate(sf::Time dt) {}

		/// To render component first add object to rendering module
		/// then the function is called every screan display
		virtual void onDisplay() {};

		/// called every frame while game is paused
		/// @param:dt			- delta of time elapsed between frames
		virtual void onPause(sf::Time dt) {}

		/// @summary: event called every frame while actor is assigned as dead
		/// @param:dt			- delta of time elapsed between frames
		/// @return:			- whether owner can be safetly removed from memory
		virtual bool onAgony(sf::Time dt) { return true; }
		

		/////////////////////// Physicss

		/// @summary: event called when collision just started
		/// @param:otherActor	- actor owner is colliding with
		/// @param:contact		- box2d provided data about collision
		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) {}
		
		/// @summary: event called every frame 
		/// @param:dt			- delta of time elapsed between frames of collision update
		/// @param:otherActor	- actor owner is colliding with
		/// @param:contact		- box2d provided data about collision
		/// TODO virtual void onCollisionUpdate(sf::Time dt, Game::Actor& otherActor, b2Contact& contact)
		
		/// @summary: event called when collision just ended
		/// @param:otherActor	- actor owner is colliding with
		/// @param:contact		- box2d provided data about collision
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact) {}
		
		/// allows to filter collision detection
		/// @param:myFixture/otherFixture 
		///						- fixtures(box2d colliders) to check
		/// @return is collision allowed to happen? 
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) { return true; }

		/// @summary: event called after collision were resolved
		///		for more informations go to b2WorldCallbacks.h file
		/// @param:contact		- box2d provided data about collision
		/// @param:impulse		- data about applied impulse
		virtual void onPostSolve(Game::Actor& otherActor, b2Contact& contact, const b2ContactImpulse& impulse) {}

	public:/// childs
		/// function creating effect depended on its name 
		/// for purpose of creating in scripts
		/// if you create your own gameplay-depended effects provide new creation function
		/// in which if creation by default version will fail (return nullptr)
		/// you will check whether you chave class appropriate for the name
		MULTI_SERIALISATION_INTERFACE(Base);

	
	public:
		Game::Actor*		getActor()		{ assert(actor); return actor; }
		const Game::Actor*	getActor() const{ assert(actor); return actor; }
		virtual void setActor(Game::Actor* s)
		{ 
			actor = s;  
		}
	
		Base*		getParent()			{ return parent; }
		const Base*	getParent() const	{ return parent; }
		void setParent(Base* s)			{ parent = s; }


		/// changes effects activate state
		void setActivated(bool b);
		bool isActivated() const			{ return bActivated; }

		void markAsReadyToRemove() { bIsReadyToRemove = true; }

		/// @return is the effect valid to be updated?
		bool canBeUpdated() { return !bIsReadyToRemove && bActivated; }

	private:
		/// owner is the actor which holds effect and is affected by it
		Game::Actor* actor;
		/// effect this one is connected to
		/// nullptr means this is root component (if owner is set up)
		Base* parent;

		/// whether or not the efect is activated
		/// if not effect does not get updated nor take collision events
		bool bActivated :1;
		/// tells whether actor should be removed in the next frame
		bool bIsReadyToRemove :1;

	protected:
		/// /// /// Serialisation is currently disabled
		/// serialisation functions - to allow effects to be sierialised from/into .res files
		//virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver)  const override;
		//virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;

		friend class Composite;
	};
	
	

	//////////////////////////////
	/// Composite


	class Composite : public Base
	{
	public:
		SERIALISATION_NAME(Composite)
		

	public: /// events

		//////////// creation


		/// called once when owner is added to world list
		virtual void onSpawn();

		/// called when setActivated changes activation state of the effect
		virtual void onSetActivated();


		/// called once when the actor returns to live
		/// here should go all code backing settings to initial state
		virtual void onRespawn();

		/// deconstruction


		/// called once when the actor was killed
		virtual void onDeath();

		/// events allowing to do a clean up code on joints and fixtures
		virtual void onDeconstructionJoint(b2Joint* joint);
		virtual void onDeconstructionFixture(b2Fixture* fixture);

		//////////////////// Frame

		/// called every frame while actor is alive
		/// @param:dt			- delta of time elapsed between frames
		virtual void onUpdate(sf::Time dt);

		/// To render component first add object to rendering module
		/// then the function is called every screan display
		virtual void onDisplay();

		/// called every frame while game is paused
		/// @param:dt			- delta of time elapsed between frames
		virtual void onPause(sf::Time dt);

		/// @summary: event called every frame while actor is assigned as dead
		/// @param:dt			- delta of time elapsed between frames
		/// @return:			- whether owner can be safetly removed from memory
		virtual bool onAgony(sf::Time dt);


		/////////////////////// Physicss

		/// @summary: event called when collision just started
		/// @param:otherActor	- actor owner is colliding with
		/// @param:contact		- box2d provided data about collision
		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact);

		/// @summary: event called every frame 
		/// @param:dt			- delta of time elapsed between frames of collision update
		/// @param:otherActor	- actor owner is colliding with
		/// @param:contact		- box2d provided data about collision
		/// TODO virtual void onCollisionUpdate(sf::Time dt, Game::Actor& otherActor, b2Contact& contact)

		/// @summary: event called when collision just ended
		/// @param:otherActor	- actor owner is colliding with
		/// @param:contact		- box2d provided data about collision
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact);

		/// allows to filter collision detection
		/// @param:myFixture/otherFixture 
		///						- fixtures(box2d colliders) to check
		/// @return is collision allowed to happen? 
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture);

		/// @summary: event called after collision were resolved
		///		for more informations go to b2WorldCallbacks.h file
		/// @param:contact		- box2d provided data about collision
		/// @param:impulse		- data about applied impulse
		virtual void onPostSolve(Game::Actor& otherActor, b2Contact& contact, const b2ContactImpulse& impulse);


	public:
		/// adds child effect and performs all initialisation
		template<typename Ty>
		Ty* addEffect(Ty* _new, bool activated = true);

		/// adds child from definition placed in file
		/*template<typename Ty>
		Ty* addEffect(const char* path);
		template<typename Ty>
		Ty* addEffect(std::istream& file, Res::DataScriptLoader& loader);*/



		/// returns first found efect of type T
		/// if there is no such the one returns nullptr
		/// @Warring make sure T derrives from Base otherwise something might go wrong
		template<typename T> T* getEffect();

	protected:
		vector<unique_ptr<Base>> childs;

	public:
		virtual void setActor(Game::Actor* s)
		{
			Base::setActor(s);
			for (auto it = childs.begin(); it != childs.end(); ++it)
				it->get()->setActor(s);
		}
		
	protected:
		/// serialisation functions - to allow effects to be sierialised from/into .res files
		/// virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver)  const override;
		/// virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};



	template<typename Ty>
	Ty* Composite::addEffect(Ty * _new, bool activated)
	{
		assert(_new);
		assert(_new->canBeParent(this));
		childs.push_back(unique_ptr<Base>(_new));

		_new->setActor(getActor());
		_new->setParent(this);

		_new->onInit();
		_new->setActivated(activated);

		return _new;
	}

	/*template<typename Ty>
	Ty * Composite::addEffect(const char * path)
	{
		std::ifstream file;
		file.open(path);

		if (file)
		{
			DataScriptLoader loader;
			loader.nextLine(file);
			Ty* _new = addEffect<Ty>(file, loader);
			file.close();
			return _new;
		}

		// log error
		std::cout << "Falied to open the file: \"" << path << "\" to load\n";
		std::cout << "badbit " << file.badbit << ", failbit" << file.failbit << ", eof" << file.eofbit;
		return nullptr;
	}
	template<typename Ty>
	Ty * Composite::addEffect(std::istream& file, Res::DataScriptLoader& loader)
	{
		Base* _new = new Ty();
		addEffect(_new)->deserialise(file, loader);
		return _new;
	}*/

	template<typename T>
	T* Composite::getEffect()
	{
		T* ptr;
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if ((ptr = dynamic_cast<T*>(it->get())))
				return ptr;
		return nullptr;
	}
}