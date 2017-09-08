#include "ActorHumanoidNpc.h"
#include <Re\Ai\ai.h>
#include "ActorWeapon.h"

class AnimationBehaviour : public Ai::BehaviourEvTime
{
public:
	AnimationBehaviour(Graphics::AnimationController *_controller, Ai::Utility_t base = 0.f, Ai::Utility_t scale = 1.f)
		: controller(_controller), Ai::BehaviourEvTime(base, scale)
	{

	}


	virtual void onStart() override 
	{ 
	}
	virtual bool onExecute(sf::Time dt) override 
	{
		assert(controller);
		return controller->updateRestart();
	}

	Graphics::AnimationController *controller;
};

ActorHumanoidNpc::ActorHumanoidNpc()
{
}

void ActorHumanoidNpc::onInit()
{
	Actor::onInit();

	efModel = addEfect(new Efect::Model("model_reaper.txt"));
	efAnim = addEfect(new Efect::AnimationManager(efModel->modelsUpdate));

		efAnim->addAnimation("anim_reaperPose.txt");

	auto pull = &efAnim->addAnimation("anim_reaperPull.txt")->getAnimation();
	auto push = &efAnim->addAnimation("anim_reaperPush.txt")->getAnimation();
	auto walk = &efAnim->addAnimation("anim_reaperWalk.txt")->getAnimation();
	auto greatSlash = &efAnim->addAnimation("anim_reaperGreatSlash.txt")->getAnimation();

	/// physics
	addEfect(new Efect::Rigidbody(25, 20));
	addEfect(new Efect::ColliderCircle(50.f));
	addEfect(new Efect::UpdateTransform());

	{
		auto weaponActor = Game::world.addActor(new ActorWeapon(this, &efModel->modelsUpdate[2]->getTransformSprite()));
		weaponActor->addEfect(new Efect::ColliderBox)->setAsBox(Vector2D(150, 30), Vector2D(), Degree(45))->setRestitution(0.005);
		weaponActor->addEfect(new Efect::ColliderBox)->setAsBox(Vector2D(30, 150), Vector2D(-15, 75), Degree(0))->setRestitution(0.0025);
	}


	efHealth = addEfect(new Efect::Health);

	efMovement = addEfect(new Efect::MovementAim(50, new Efect::RotateToDirection(Efect::RotateToDirection::smoothPhysics, 0.005)));
	auto efRandomMovement = addEfect(new Efect::RandomMovement(efMovement),false)
		->setOffset(Vector2D(0, -50))->setRadius(75.f, 50.f)->setTime(seconds(0.25), seconds(0.6));


	static Clock cl;
	
	efMind = addEfect(new Efect::Mind)->setTreshold(0.25f)
		->addBehaviour(new Ai::BehaviourWait(sf::seconds(1.f), 0.75))
		->addBehaviour((new Ai::BehaviourLambda())
			->setOnStart([=]() {efRandomMovement->activated = true; cl.restart(); })
			->setOnExit([=]() {efRandomMovement->activated = false; })
			->setOnExecute([=](sf::Time) { 
				walk->updateReturn();
				return  cl.getElapsedTime() > seconds(1.f);  
			})
		)
		->addBehaviour(new AnimationBehaviour(pull,0,0.05))
		->addBehaviour(new AnimationBehaviour(push,0,0.05))
		->addBehaviour(new AnimationBehaviour(greatSlash, 0, 0.05))
		;
}
