#include "StateGameplay.h"
#include "ActorPlayer.h"
#include "Obstacle.h"

void StateGameplay::onStart()
{
	Super::onStart();
	cam.setScale(1.95f);
	res.deserialise("Resources.txt");

	Control::input.setKey("up", new Control::MultiKey(sf::Keyboard::W));
	Control::input.setKey("down", new Control::MultiKey(sf::Keyboard::S));
	Control::input.setKey("left", new Control::MultiKey(sf::Keyboard::A));
	Control::input.setKey("right", new Control::MultiKey(sf::Keyboard::D));

	Control::input.setKey("press", new Control::MultiKey(sf::Mouse::Left));
	Control::input.setKey("atack", new Control::MultiKey(sf::Mouse::Right)) ->addKey(sf::Keyboard::Q);

	restartKey = Control::input.setKey("restart", new Control::MultiKey(sf::Keyboard::P, Control::Key::EPressState::pressedOnce));

	Control::input.setAxis("xMove", "right", "left");
	Control::input.setAxis("yMove", "down", "up");

	{
		sf::Sprite sp;
		tsInst[100].set(sp);
		sp.setScale(5, 5);
		sp.setOrigin(sp.getTextureRect().height*0.5f, sp.getTextureRect().width * 0.5f);
		background.addSprite(sp);
	}

	Game::world.createActor<ActorPlayer>()
		->setPosition({ 0,0 });

	for(int i = 0; i < 10; ++i)
		Game::world.createActor<Obstacle>( Vector2D(randRange(200,1000),0).getRotated(), randRange(Degree(0), Degree(360)) );
	
	/*for (int i = 0; i < 10000; ++i)
		Game::world.createActor<Game::Actor>();*/

}

Game::State* StateGameplay::onUpdate(sf::Time dt)
{
	cam.draw(background);
	Game::world.onFrame(dt);
	cam.display(wnd);

	if (restartKey->isReady())
		return new StateGameplay;
	return nullptr;
}
void StateGameplay::onExit()
{
	Game::world.clear();
	Gui::gui.clear();
}