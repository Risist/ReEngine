#include "ActorPlayer.h"

void ActorPlayer::onInit()
{
	Super::onInit();
	createInput();
	
	
	auto efModel = addEffect(new Effect::Model("model_reaper.txt"));
	auto animationManager = addEffect(new Effect::AnimationManager(*efModel));
		
	animPose = animationManager->insertAnimation("anim_reaperPose.txt");
	animWalk = animationManager->insertAnimation("anim_reaperWalk.txt");
	animSlash = animationManager->insertAnimation("anim_reaperSlash.txt");
	animPush = animationManager->insertAnimation("anim_reaperPush.txt");
	animPull = animationManager->insertAnimation("anim_reaperPull.txt");

	
	
	auto efRigidbody = addEffect(new Effect::Rigidbody())
		->createRigidbody(Effect::RigidbodyDef()
			.setType(b2_dynamicBody)
			.setLinearDamping(10)
			.setAngularDamping(15)
		)
		->setSyncMode(Effect::Rigidbody::ETransformSyncMode::transformToRigidbody);

	efRigidbody->addEffect(new Effect::Fixture())
		->createFixture(Effect::CircleColliderDef()
			.setDensity(2.f)
			.setRadius(100.f)
		);


	//efMovement = efRigidbody->addEffect(new Effect::MouseMovement(2.5f));
	efMovement = efRigidbody->addEffect(new Effect::StaticMovement(2.5f))->setMinimalDistance(0.f);

	addEffect(new Effect::FollowCamera())->setSmooth(0.1f, 0.0f);


	jumpCd.cd = sf::seconds(1.f);
	jumpTime.cd = sf::seconds(0.15f);
	defaultMovementSpeed = efMovement->getMovementSpeed();
	jumpKey.setKeyCode(sf::Keyboard::LShift);
	jumpKey.desiredState = Control::Key::EPressState::pressedOnce;
}

void ActorPlayer::onUpdate(sf::Time dt)
{
	Super::onUpdate(dt);

	if (efMovement->isMoving())
		animWalk->updateReturn();

	{
		if (onSlashBack)
		{
			if (animSlash->updateTowards(0, 0.75*(0.25 + slashLoaded*0.75)))
				onSlashBack = onSlash = false;
		}
		else
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				onSlash = true;
				animSlash->updateInRange(-animSlash->getSpeedSign()*0.85);
				slashLoaded = animSlash->step / animSlash->stepMin;
			}
			else if (!onSlashBack && onSlash &&
				animSlash->updateTowards((0.3 + slashLoaded*0.7)* animSlash->stepMax,
					animSlash->getSpeedSign()*2.25*
					(0.25 + slashLoaded*slashLoaded*0.75)
				))
				onSlashBack = true;
	}

	/*{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			onGreatSlash = true;
		if (onGreatSlash && animGreatSlash->updateRestart())
			onGreatSlash = false;
	}*/

	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			onPull = true;
		if (onPull && animPull->updateRestart())
			onPull = false;
	}
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			onPush = true;
		if (onPush && animPush->updateRestart())
			onPush = false;
	}

	if ( jumpKey.isReady() && jumpCd.isReadyRestart())
			jumpTime.restart();

	if (jumpTime.isReady())
		efMovement->setMovementSpeed(defaultMovementSpeed);
	else
		efMovement->setMovementSpeed(defaultMovementSpeed*5.f);

}

void ActorPlayer::createInput()
{
	createPlayerInput()
		->setInputKey("up", new Control::MultiKey(sf::Keyboard::W))
		->setInputKey("down", new Control::MultiKey(sf::Keyboard::S))
		->setInputKey("left", new Control::MultiKey(sf::Keyboard::A))
		->setInputKey("right", new Control::MultiKey(sf::Keyboard::D))

		->setInputKey("press", new Control::MultiKey(sf::Mouse::Left))

		->setInputAxis("xMove", "right", "left")
		->setInputAxis("yMove", "down", "up")
		;
}
