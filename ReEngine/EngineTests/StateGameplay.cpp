#include "StateGameplay.h"
#include "ActorPlayer.h"

void StateGameplay::onStart()
{
	Super::onStart();
	cam.setScale(2.25f);
	res.deserialise("Resources.txt");

	{
		sf::Sprite sp;
		tsInst[100].setSprite(sp);
		sp.setScale(5, 5);
		sp.setOrigin(sp.getTextureRect().height*0.5f, sp.getTextureRect().width * 0.5f);
		background.addSprite(sp);
	}

	Game::world.createActor<ActorPlayer>()
		->setPosition({ 0,0 });
	
	restartKey.setKeyCode(sf::Keyboard::P);
	restartKey.desiredState = Control::Key::EPressState::pressedOnce;
}

Game::State* StateGameplay::onUpdate(sf::Time dt)
{
	cam.draw(background);
	Game::world.onFrame(dt);
	cam.display(wnd);

	if (restartKey.isReady())
		return new StateGameplay;
	return nullptr;
}
void StateGameplay::onExit()
{
	Game::world.clear();
	Gui::gui.clear();
}