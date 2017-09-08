#include <Re\Game\Effect\Physics\EffectRigidbody.h>
#include <Re\Game\GameActor.h>
#include <Re\Game\GameWorld.h>
#include <Re\Game\Effect\Physics\EffectFixture.h>

namespace Effect
{
	Rigidbody::Rigidbody()
		: bSyncTransformAtPause(false), bSyncTransformAtDeath(false)
	{
	}

	Effect::Rigidbody::~Rigidbody()
	{
		destroyBody();
	}

	Rigidbody * Effect::Rigidbody::createRigidbody(const b2BodyDef * _def)
	{
		b2BodyDef def = *_def;
		def.position = (getActor()->getPosition() + getPosition().getRotated(getActor()->getRotation())) * toB2Position;
		def.angle = (getActor()->getRotation() + getRotation()).asRadian();

		rigidbody = Game::world.physicsWorld.CreateBody(&def);
		rigidbody->SetUserData(this);
		return this;
	}

	void Rigidbody::destroyBody()
	{
		if (rigidbody == nullptr)
			return;

		if (getActor()->rigidbody == rigidbody)
			getActor()->rigidbody = nullptr;

		b2Body * body = rigidbody;
		rigidbody = nullptr;

		body->SetUserData(nullptr);
		Game::world.physicsWorld.DestroyBody(body);
	}


	/// only actor can be parent for rigidbody
	bool Rigidbody::canBeParent(Effect::Base* potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}
	
	/// sync rigidbody and transform at update function
	void Rigidbody::onUpdate(sf::Time dt)
	{
		syncTransform();
		Super::onUpdate(dt);
	}
	void Rigidbody::onPause(sf::Time dt)
	{
		if (bSyncTransformAtPause)
			syncTransform();
		Super::onPause(dt);
	}

	void Rigidbody::onInit()
	{
		syncTarget = getActor();
		Super::onInit();
	}

	void Rigidbody::onRespawn()
	{
		if (rigidbody)
			rigidbody->SetActive(true);
		Super::onRespawn();
	}
	void Rigidbody::onDeath()
	{
		if (rigidbody)
			rigidbody->SetActive(false);
		Super::onDeath();
	}
	bool Rigidbody::onAgony(sf::Time dt)
	{
		if (bSyncTransformAtDeath)
			syncTransform();
		return Super::onAgony(dt);		
	}

	/// activate/deactivate rigidbody if actor/ the effect was turn on/off
	void Rigidbody::onSetActivated()
	{
		Super::onSetActivated();
		if (rigidbody)
			rigidbody->SetActive( isActivated() );
	}


	/// Collision events are called on every child, besides fixtures
	/// fixtures receive only events that comes from their shape

	void Rigidbody::onCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated() && dynamic_cast<Fixture*>(it->get()) == nullptr )
				it->get()->onCollisionEnter(otherActor, contact);
	}

	void Rigidbody::onCollisionExit(Game::Actor & otherActor, b2Contact & contact)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated() && dynamic_cast<Fixture*>(it->get()) == nullptr)
				it->get()->onCollisionExit(otherActor, contact);
	}

	bool Rigidbody::shouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
	{
		bool b = true;
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated() && dynamic_cast<Fixture*>(it->get()) == nullptr)
				b = b && it->get()->shouldCollide(myFixture, otherFixture);
		return b;
	}

	void Rigidbody::onPostSolve(Game::Actor & otherActor, b2Contact & contact, const b2ContactImpulse & impulse)
	{
		for (auto it = childs.begin(); it != childs.end(); ++it)
			if (it->get()->canBeUpdated() && dynamic_cast<Fixture*>(it->get()) == nullptr)
				it->get()->onPostSolve(otherActor, contact, impulse);
	}

	Rigidbody * Rigidbody::setSyncMode(ETransformSyncMode newMode, float32 _syncRate)
	{
		transformSyncMode = newMode;
		if (newMode == ETransformSyncMode::transformToRigidbody)
		{
			assert(!getActor()->rigidbody || getActor()->rigidbody == rigidbody);
			getActor()->rigidbody = rigidbody;
		}
		syncRate = _syncRate;
		return this;
	}


	void Rigidbody::syncTransform()
	{
		if(rigidbody)
		switch (transformSyncMode)
		{
		case Effect::Rigidbody::transformToRigidbody:
			{
				syncTarget->setRotation(Radian(rigidbody->GetAngle()) + getRotation());
				syncTarget->setPosition((Vector2D)rigidbody->GetPosition() * toSfPosition 
					+ getPosition().getRotated(syncTarget->getRotation()));
			}
			break;
		case Effect::Rigidbody::rigidbodyToTransform:
			{
				Vector2D desiredPosition = syncTarget->getPosition()* toB2Position  
					+ getPosition().getRotated(syncTarget->getRotation());
				Vector2D toDesiredPosition = desiredPosition - (Vector2D)rigidbody->GetPosition();
				rigidbody->SetLinearVelocity(toDesiredPosition *syncRate);

				Angle desiredRotation = syncTarget->getRotation() + getRotation();
				Angle toDesiredRotation = desiredRotation.minimalDiffirence(Radian(rigidbody->GetAngle()));
				rigidbody->SetAngularVelocity(toDesiredRotation.asRadian() * syncRate);
			}
			break;
		}

	}

	/*void Rigidbody::serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const
	{
		saver.save<bool>("syncAtDeath", bSyncTransformAtDeath, false);
		saver.save<bool>("syncAtPause", bSyncTransformAtPause, false);
		saver.save<float32>("syncRate", syncRate, 80.f);
		
		/// default state, not need to check
		//if (transformSyncMode == transformToRigidbody)
			// saver.save<string>("syncMode","transformToRigidbody");
		//else 
		if (transformSyncMode == rigidbodyToTransform)
			saver.save<string>("syncMode", "rigidbodyToTransform");
		else if(transformSyncMode == none)
			saver.save<string>("syncMode", "none");

		saver.save<ResId>("bodyDefId", bodyDefId, 0);

		Super::serialise(file, saver);
	}
	void Rigidbody::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		bSyncTransformAtDeath = loader.load<bool>("syncAtDeath", false);
		bSyncTransformAtPause = loader.load<bool>("syncAtPause", false);
		syncRate = loader.load<float32>("syncRate", 80.f);

		ResId bodyDefId = loader.load<ResId>("bodyDefId", 0u);
		if (bodyDefId)
			createBody(bodyDefId);


		std::string sSyncMode = loader.load<string>("syncMode", "transformToRigidbody");
		if (sSyncMode == "transformToRigidbody")
			setSyncMode(transformToRigidbody);
		else if (sSyncMode == "rigidbodyToTransform")
			setSyncMode(rigidbodyToTransform);
		else if (sSyncMode == "none")
			setSyncMode(none);
		else
			cerr << "wrong rigidbody sync mode = " << sSyncMode << endl;
		
		
		/// load fixtures/ joints
		Super::deserialiseF(file, loader);
	}*/

}