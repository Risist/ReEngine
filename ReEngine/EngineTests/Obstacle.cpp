#include "Obstacle.h"



Obstacle::Obstacle()
{
}

void Obstacle::onInit()
{
	Super::onInit();

	auto efModel = addEffect(new Effect::Model("model_obstacle.txt"));


	auto efRigidbody = addEffect(new Effect::Rigidbody())
		->createRigidbody(Effect::RigidbodyDef()
			.setType(b2_dynamicBody)
			.setLinearDamping(15)
			.setAngularDamping(20)
		)
		->setSyncMode(Effect::Rigidbody::ETransformSyncMode::transformToRigidbody);
	
	efRigidbody->addEffect(new Effect::Fixture())
		->createFixture(Effect::CircleColliderDef()
			.setDensity(2.f)
			.setRadius(100.f)
		);

	efHealth = addEffect(new Effect::Health)->setRegeneration(-0.5,1);
	//addEffect(new Effect::RespawnAfterAWhile(sf::seconds(5)));

}

void Obstacle::onUpdate(sf::Time dt)
{
	Super::onUpdate(dt);
}

void Obstacle::onRespawn()
{
	Super::onRespawn();
	efHealth->actual = efHealth->max;
	setPosition(Vector2D(randRange(200, 1000), 0).getRotated());
	getRigidbody()->SetTransform(getPosition()*toB2Position, randRange(Degree(0), Degree(360)).asRadian());
}
