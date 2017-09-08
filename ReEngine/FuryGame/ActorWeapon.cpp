#include "ActorWeapon.h"


ActorWeapon::ActorWeapon(Game::Actor * _owner, Transformable * _transformable)
	: owner(_owner), updateTransformable(_transformable)
{

}

void ActorWeapon::onInit()
{
	addEfect((new Efect::Rigidbody)->setType(b2_kinematicBody)->setIsBullet(true));
	addEfect(new Efect::UpdateTransform(Efect::UpdateTransform::RigidbodyToTransform))
		->setUpdateRate(100)
		->setTransformOwner(updateTransformable);
}

void ActorWeapon::onCollisionEnter(Game::Actor & otherActor, b2Contact & contact)
{
	Actor::onCollisionEnter(otherActor, contact);

	//contact.GetManifold()->localNormal * contact.GetTangentSpeed();
	//contact.GetFixtureB()->GetShape()->RayCast
}

bool ActorWeapon::shouldCollide(b2Fixture * myFixture, b2Fixture * otherFixture)
{
	/// do not collide with owner
	return otherFixture->GetBody()->GetUserData() != owner;
}
