#pragma once

#include <Re\Game\Effect\EffectTransformable.h>
#include <Re\Graphics\ResourceManager.h>
#include <Re\Game\Effect\Physics\PhysicsDefs.h>

namespace Game
{
	class Actor;
}
namespace Effect
{
	/// rigidbody effect creates and takes control on rigidbody propertites
	/// Only childs of rigidbody can take events about physics
	class Rigidbody final : public Transformable 
	{
		SERIALISATION_NAME(Rigidbody)
	public:
		/// removes rigidbody if created 
		virtual ~Rigidbody();
		
		/// does not create rigidbody (in box2d sense )
		/// should be used while the effect is loaded from file (after deserialisation body is created), 
		/// or call create body function manually
		/// you HAVE TO call createBody function in order to gain anything from that component
		Rigidbody();

	public:

		/// creates body from definition passed as an argument
		Rigidbody* createRigidbody(const RigidbodyDef& def) { return createRigidbody(&def.def); }
		/// creates body from manually provided b2 definition
		Rigidbody* createRigidbody(const b2BodyDef* def);

		/// removes rigidbody if created
		void destroyBody();

		b2Body* getRigidbody() const { return rigidbody; }

		/// decides how actor(or different updateTarget) and rigidbody are synchronised together
		enum ETransformSyncMode : int8
		{
			transformToRigidbody,	/// actor transform is altered relativelly to rigidbody
			rigidbodyToTransform,	/// body transform is altered relativelly to owning actor /// changes in small steps
			none					/// don't sync
		} transformSyncMode{ rigidbodyToTransform };

	public: ////// events

		/// only actor can be parent for rigidbody
		virtual bool canBeParent(Effect::Base* potentialParent) const override;

		virtual void onInit() override;

		virtual void onRespawn() override;
		virtual void onDeath() override;


		/// sync rigidbody and transform at update function
		virtual void onUpdate(sf::Time dt) override;
		virtual void onPause(sf::Time dt) override;
		virtual bool onAgony(sf::Time dt) override;

		/// activate/deactivate rigidbody if actor/ the effect was turn on/off
		virtual void onSetActivated() override;

		/// Collision events are called on every child, besides fixtures
		/// fixtures receive only events that comes from their shape

		virtual void onCollisionEnter(Game::Actor& otherActor, b2Contact& contact) override;
		/// TODO virtual void onCollisionUpdate(sf::Time dt, Game::Actor& otherActor, b2Contact& contact)
		virtual void onCollisionExit(Game::Actor& otherActor, b2Contact& contact) override;
		virtual bool shouldCollide(b2Fixture* myFixture, b2Fixture* otherFixture) override;
		virtual void onPostSolve(Game::Actor& otherActor, b2Contact& contact, const b2ContactImpulse& impulse) override;
		
	public:////// setters

		Rigidbody* setSyncMode(ETransformSyncMode newMode, float32 _syncRate = 80.f);
		Rigidbody* setSyncAtPause(bool s = true)
		{
			bSyncTransformAtPause = s;
			return this;
		}
		Rigidbody* setSyncAtDeath(bool s = true)
		{
			bSyncTransformAtDeath = s;
			return this;
		}
		Rigidbody* setSyncOffset(const Vector2D& position, Angle rotation)
		{
			setPosition(position);
			setRotation(rotation);
			return this;
		}
		Rigidbody* setSyncTarget(Transformable* target)
		{
			syncTarget = target;
			return this;
		}

	private:
		b2Body* rigidbody{nullptr};
		
		ResId bodyDefId{0};

		void syncTransform();

	public:
		/// by default sync target is Actor, but it is possible to sync to different transformable
		Transformable *syncTarget{nullptr};
		
		/// while synchronising rigidbody to transform rigidbody is mooved to actor through physics forces 
		///		to not break simulation ( like to not miss collisition detection )
		/// this value explains how fast the process will it appear
		/// @warring if to big value body will never arrive to the aim (very buggy effect)
		float32 syncRate{ 80.f };
		
		/// sync at pause and death would not be needed 
		/// -> therefore you can turn off the operation which cost a little bit
		uint8 bSyncTransformAtPause : 1;
		uint8 bSyncTransformAtDeath : 1;

		/*
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};


}