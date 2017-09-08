#include "StateWhiteVoid.h"
#include "Layers.h"

#include "Warrior\WarriorPlayer.h"
#include "ActorHumanoidNpc.h"
//#include "Characters\Zenon.h"

void StateWhiteVoid::onStart()
{
	initKeys();
	/// initial map spawn
	Game::Layers::init();

	cam.setScale(1.85f);
	cam.setAlpha(1.f);

	
	
	addBackground(Vector2D());
	Game::world.addActor(new WarriorPlayer(), Game::Layers::character);
	Game::world.addActor(new ActorHumanoidNpc(), Game::Layers::character)->setPosition( 100, 500);

	//for (int i = 0; i < 5; ++i)
		//addZenon(Vector2D(0, randRange(100.f, 1500.f)).getRotated());
	
	//for (int i = 0; i < 250; ++i)
		//addObstacle(Vector2D(0, randRange(100.f, 5500.f)).getRotated(), randRange(Angle::zero, Angle::full) );


	for (int i = 0; i < 20; ++i)
		addBarrel(Vector2D(0, randRange(100.f, 5500.f)).getRotated(), randRange(Angle::zero, Angle::full) );
}

Game::State * StateWhiteVoid::onUpdate(sf::Time dt)
{
	Game::world.onUpdate(dt);
	cam.display(wnd);


	controlBackgroundColor();
	if (actionMap.isActive("restart"))
		return new StateWhiteVoid;
	return nullptr;
}

void StateWhiteVoid::onExit()
{
	Gui::gui.clear();
	Game::world.clear();
}

void StateWhiteVoid::initKeys()
{
	/// movement
	actionMap["up"] = thor::Action(sf::Keyboard::W);
	actionMap["down"] = thor::Action(sf::Keyboard::S);
	actionMap["left"] = thor::Action(sf::Keyboard::A);
	actionMap["right"] = thor::Action(sf::Keyboard::D);

	/// actions and skills
	actionMap["fire1"] =
		thor::Action(sf::Mouse::Left) || thor::Action(sf::Mouse::Right) 
		|| thor::Action(thor::JoystickButton(0, 5), thor::Action::PressOnce);
	
	actionMap["fire2"] = thor::Action(sf::Keyboard::Q, thor::Action::PressOnce);
	actionMap["fire3"] = thor::Action(sf::Keyboard::E, thor::Action::PressOnce);

	/// helper
	actionMap["debugPhysics"] = thor::Action(sf::Keyboard::Z, thor::Action::Hold);
	actionMap["restart"] = thor::Action(sf::Keyboard::P, thor::Action::PressOnce);
}

///////////////////////////////////////////////////////////

Game::Actor * StateWhiteVoid::addZenon(const Vector2D & position, Angle rotation)
{
	/*auto zenon = Game::world.addActor(new Zenon, Game::Layers::character);
	zenon->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian() );
	
	return zenon;*/
	return nullptr;
}

Game::Actor * StateWhiteVoid::addPlayer(const Vector2D & position, Angle rotation)
{
	auto player = Game::world.addActor(new WarriorPlayer(), Game::Layers::character);
	player->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());

	return player;
}

Game::Actor * StateWhiteVoid::addBackground(const Vector2D & position)
{
	auto background = Game::world.addActor(new Game::Actor, Game::Layers::background);

	background->setPosition(position);

	auto efModel = background->addEfect(new Efect::Model())->deserialiseFromString("<ts=100><\\>")
		->setScale(Vector2D(5.f, 5.f));
	return background;
}

Game::Actor * StateWhiteVoid::addObstacle(const Vector2D & position, Angle rotation)
{
	Game::Actor *actor = Game::world.addActor(new Game::Actor,Game::Layers::obstacle);
	actor->addEfect(new Efect::Rigidbody());
	actor->addEfect(new Efect::ColliderBox(Vector2D(75, 75), 10));
	actor->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());


	actor->addEfect(new Efect::UpdateTransform());
	actor->addEfect(new Efect::GraphicsRect(Vector2D(150, 150), Color(100, 100, 100, 150)));

	return actor;
}

Game::Actor * StateWhiteVoid::addBarrel(const Vector2D & position, Angle rotation)
{
	Game::Actor *actor = Game::world.addActor(new Game::Actor, Game::Layers::obstacle);
	actor->addEfect(new Efect::Rigidbody(10,10));
	//actor->addEfect(new Efect::ColliderBox(Vector2D(75, 75), 10));
	actor->addEfect(new Efect::ColliderCircle(70,50.f));
	actor->getRigidbody().SetTransform(position*toB2Position, rotation.asRadian());


	actor->addEfect(new Efect::UpdateTransform());
	//actor->addEfect(new Efect::GraphicsRect(Vector2D(150, 150), Color(100, 100, 100, 150)));
	//actor->addEfect(new Efect::GraphicsCircle(Color(150, 120, 120, 200), 75))->shape.setTexture(&atlasInst[501]);
	actor->addEfect(new Efect::Model(1));

	return actor;
}

void StateWhiteVoid::controlBackgroundColor()
{
	static const Color baseColor(200,185,185);
	static float intense = 1.f;

	intense *= randRange(0.985f, 1.15f);
	intense = clamp(intense, 0.f, 1.f);

	cam.setBackgroundColor(
		Color(
			baseColor.r*intense,
			baseColor.g*intense,
			baseColor.b*intense,
			baseColor.a*intense
		)
	);
}
