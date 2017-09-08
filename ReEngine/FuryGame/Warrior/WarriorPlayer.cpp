#include "WarriorPlayer.h"
#include "../Layers.h"

#include "../ActorWeapon.h"

void WarriorPlayer::onInit()
{
	Game::Actor::onInit();
	
	/// graphics
	auto efModel = addEfect(new Efect::Model("model_reaper.txt"));
	     efAnimation = addEfect(new Efect::AnimationManager(efModel->modelsUpdate));
	
				  &efAnimation->addAnimation("anim_reaperPose.txt")->getAnimation();
	slash		= &efAnimation->addAnimation("anim_reaperSlash.txt")->getAnimation();
	pull		= &efAnimation->addAnimation("anim_reaperPull.txt")->getAnimation();
	push		= &efAnimation->addAnimation("anim_reaperPush.txt")->getAnimation();
	walk		= &efAnimation->addAnimation("anim_reaperWalk.txt")->getAnimation();
	greatSlash	= &efAnimation->addAnimation("anim_reaperGreatSlash.txt")->getAnimation();/**/
	helper		= &efAnimation->addAnimation("anim_reaperHelper.txt")->getAnimation();/**/

	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());

	{
		auto weaponActor = Game::world.addActor(new ActorWeapon(this, &efModel->modelsUpdate[2]->getTransformSprite()));
		weaponActor->addEfect(new Efect::ColliderBox)->setAsBox(Vector2D(150, 30), Vector2D(), Degree(45))->setRestitution(0.005);
		weaponActor->addEfect(new Efect::ColliderBox)->setAsBox(Vector2D(30, 150), Vector2D(-15,75), Degree(0))->setRestitution(0.0025);
	}
	
	efMovement = addEfect(new Efect::MouseMovement(75, 
		(new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005))->setMaxRotationSpeed(Degree(0.5f)) ));
	
	//efMovement = addEfect(new Efect::StaticMovement(50, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	addEfect(new Efect::FollowCamera(Efect::FollowCamera::positionOnlySmooth))->setLerpPosition(0.125);
}

void WarriorPlayer::onUpdate(sf::Time dt)
{
	/// set up scale for all animation
	/*{
		Graphics::Step_t scaleSum = (onPull + onPush + onSlash + onGreatSlash);
		if (scaleSum) scaleSum = 1 / scaleSum;

		size_t size = efAnimation->animationCount();
		for (size_t i = 1; i < size; ++i)
			efAnimation->activateAnimation(i,scaleSum);
	}*/
	Actor::onUpdate(dt);
	
	/**
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		push.updateInRange(push.speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		push.updateInRange(-push.speed);
	/**/

	/**/
	{
		
		if (onSlashBack )
		{
			if (slash->updateTowards(0, 0.75*(0.25 + slashLoadedStep*0.75) ) )
				onSlashBack = onSlash = false;
		}else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			onSlash = true;
			slash->updateInRange(-slash->getSpeedSign()*0.85);
			slashLoadedStep = slash->step/ slash->stepMin;
		}
		else if (!onSlashBack && onSlash && 
			slash->updateTowards((0.3 + slashLoadedStep*0.7)* slash->stepMax,
				slash->getSpeedSign()*2.25*
				(0.25 + slashLoadedStep*slashLoadedStep*0.75)
				) )
			onSlashBack = true;
		
	}
	

	/*if(efMovement->getArrived() == false && efMovement->activated)
		walk->updateReturn();*/

	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			onGreatSlash = true;
		if (onGreatSlash && greatSlash->updateRestart())
			onGreatSlash = false;
	}

	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			onPull = true;
		if (onPull && pull->updateRestart())
			onPull = false;
	}
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			onPush = true;
		if (onPush && push->updateRestart())
			onPush = false;
	} 

	if (onSlash || onPull || onPush || onGreatSlash)
	{
		//efMovement->reset();
		efMovement->efRotDir->direction = Vector2D((Vector2D)cam.mapPixelToCoords((Vector2D)Mouse::getPosition(wnd)) - getPosition()).angle();
	}
	//efMovement->activated = !(onSlash && !sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || onPull || onPush || onGreatSlash);
}
