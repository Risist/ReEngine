#pragma once
#include <Re\ReEngine.h>

class StateGameplay : public Game::State
{
public:
	
	Graphics::Background background;
	Control::Key restartKey;

	virtual void onStart() override;
	virtual State* onUpdate(sf::Time dt = sf::seconds(1)) override;
	virtual void onExit() override;

};

