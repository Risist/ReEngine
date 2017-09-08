#include <Re\Game\Effect\EffectBase.h>
#include "EffectBase.h"
namespace Effect
{
	Base::Base()
		:
		bActivated(true),
		bIsReadyToRemove(false)
	{
	}

	/*void Base::serialiseF(std::ostream& file, Res::DataScriptSaver& saver)  const
	{
		saver.save("effectType", getName() );
		saver.save<bool>("activated", bActivated, true);
	}
	void Base::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		setActivated(loader.load<bool>("activated", true));
	}*/

	////////////


	void Base::setActivated(bool b) 
	{ 
		if (b == bActivated)
			return;
		
		bActivated = b; 
		onSetActivated();
	}


	///////////////////////////// Composite

	/// called once when actor is added to world list
	/// or when efect is inserted to already added actor
	void Composite::onSpawn()
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			it->get()->onSpawn();

		for (auto it = childs.begin(); it != childs.end(); ++it)
			it->get()->onRespawn();
	}

	void Composite::onSetActivated()
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			it->get()->onSetActivated();
	}


	/// called every frame while actor is alive
	/// @param:dt			- delta of time elapsed between frames
	void Composite::onUpdate(sf::Time dt)
	{
		/// remove childs 
		for (auto it = childs.begin(); it != childs.end();)
			if (it->get()->bIsReadyToRemove)
				childs.erase(it++);
			else
				++it;

		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->bActivated)
				it->get()->onUpdate(dt);
	}

	void Composite::onDisplay()
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			it->get()->onDisplay();
	}

	void Composite::onPause(sf::Time dt)
	{
		/// remove childs 
		for (auto it = childs.begin(); it != childs.end();)
			if (it->get()->bIsReadyToRemove)
				childs.erase(it++);
			else
				++it;

		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->bActivated)
				it->get()->onUpdate(dt);
	}

	void Composite::onDeath()
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated())
				it->get()->onDeath();
	}

	void Composite::onDeconstructionJoint(b2Joint * joint)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			it->get()->onDeconstructionJoint(joint);
	}

	void Composite::onDeconstructionFixture(b2Fixture * fixture)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			it->get()->onDeconstructionFixture(fixture);
	}

	void Composite::onRespawn()
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated())
				it->get()->onRespawn();
	}

	/// @summary: event called every frame while actor is assigned as dead
	/// @param:dt			- delta of time elapsed between frames
	/// @return:			- whether owner can be safetly removed from memory
	bool Composite::onAgony(sf::Time dt)
	{
		/// remove childs 
		for (auto it = childs.begin(); it != childs.end();)
			if (it->get()->bIsReadyToRemove)
				childs.erase(it++);
			else
				++it;


		bool b = true;
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->bActivated)
				b = b && it->get()->onAgony(dt);
		return b;
	}


	/// @summary: event called when collision just started
	/// @param:otherActor	- actor owner is colliding with
	/// @param:contact		- box2d provided data about collision
	void Composite::onCollisionEnter(Game::Actor& otherActor, b2Contact& contact)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated())
				it->get()->onCollisionEnter(otherActor, contact);
	}

	/// @summary: event called every frame 
	/// @param:dt			- delta of time elapsed between frames of collision update
	/// @param:otherActor	- actor owner is colliding with
	/// @param:contact		- box2d provided data about collision
	/// TODO virtual void onCollisionUpdate(sf::Time dt, Game::Actor& otherActor, b2Contact& contact)

	/// @summary: event called when collision just ended
	/// @param:otherActor	- actor owner is colliding with
	/// @param:contact		- box2d provided data about collision
	void Composite::onCollisionExit(Game::Actor& otherActor, b2Contact& contact)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated())
				it->get()->onCollisionExit(otherActor, contact);
	}

	/// allows to filter collision detection
	/// @param:myFixture/otherFixture 
	///						- fixtures(box2d colliders) to check
	/// @return is collision allowed to happen? 
	bool Composite::shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture)
	{
		bool b = true;
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated())
				b = b && it->get()->shouldCollide(myFixture, otherFixture);
		return b;
	} 

	void Composite::onPostSolve(Game::Actor& otherActor, b2Contact & contact, const b2ContactImpulse & impulse)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated())
				it->get()->onPostSolve(otherActor, contact, impulse);
	}

	/*void Composite::serialiseF(std::ostream& file, Res::DataScriptSaver& saver)  const
	{
		Super::serialiseF(file, saver);
		saver.nextLine(file);
		auto it = childs.begin();
		do
		{
			(*it)->serialise(file, saver);
			++it;
		}
		DATA_SCRIPT_MULTILINE_SAVE(file, saver, it != childs.end())
	}
	void Composite::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		Super::deserialiseF(file, loader);
		DATA_SCRIPT_MULTILINE(file, loader)
		{
			const string type = loader.load<string>("effectType", "Base");
			Base* _new = creationFunction(type);
			if (_new)
				addEffect(_new)->deserialise(file, loader);
			else
				cerr << "AddEffect failed due to invalid effect type: " << type << endl;
		}
	}*/
}