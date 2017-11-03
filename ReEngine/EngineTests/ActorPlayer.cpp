#include "ActorPlayer.h"

void ActorPlayer::onInit()
{
	Super::onInit();
	keySpellCast = Control::input.getKey("atack");
	
	efModel = new Effect::Model("model_fury.txt");
	auto animationManager = addEffect(new Effect::AnimationManager(&efModel->modelsUpdate));
	addEffect(efModel);

	animSpellCast = animationManager->insertAnimation("anim_spellCast.txt");



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


	efMovement = efRigidbody->addEffect(new Effect::MouseMovement(5.f))
	//efMovement = efRigidbody->addEffect(new Effect::StaticMovement(4.f))->setMinimalDistance(0.f)
		->setRotationSmoothness(3.f);

	//efMovement = efRigidbody->addEffect(new Effect::RadiusMovement(5))
	//	->setRotationSmoothness(3.f);
		
	//efMovement = efRigidbody->addEffect(new Effect::RotatedMovement(7.5))
	//	->setRotationSmoothness(0.025f)->setRotationSpeedMax(Degree(10));



	addEffect(new Effect::FollowCamera())->setSmooth(0.05f, 0.f);
}

void ActorPlayer::onUpdate(sf::Time dt)
{
	Super::onUpdate(dt);

	if (keySpellCast->isReady())
		onCastingSpeel = true;

	if (onCastingSpeel && animSpellCast->updateReturn())
	{
		/// spell cast here : 
		///
		/// /// 

		if(animSpellCast->speed > 0)
			onCastingSpeel = false;
	}
}
