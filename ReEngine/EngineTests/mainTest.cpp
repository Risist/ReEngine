#include <Re\ReEngine.h>
#include"StateGuiTest.h"
#include "StateGameplay.h"

Clock performanceClock;


void init()
{
	srand((unsigned int)time(nullptr));
	wnd.create(VideoMode(800, 600), "ReEngine");
	wnd.setVerticalSyncEnabled(true);

	cam.create(Vector2D((float32)wnd.getSize().x, (float32)wnd.getSize().y));
	cam.setBackgroundColor(Color(0, 0, 0));
	cam.setDarkness(1);
	cam.setBackgroundColor(Color(200, 200, 200));

	//Game::stateManager.setState(new State);
	//Game::stateManager.setState(new StateGuiTest);
	Game::stateManager.setState(new StateGameplay);

	performanceClock.restart();
}


void update()
{	
	
	performanceClock.restart();
	Game::stateManager.onUpdate();
	


	Gui::gui.onUpdate(wnd, RenderStates::Default);
	
	sf::Text txt;

	if (performanceClock.getElapsedTime().asMilliseconds() < 100)
	{
		static float32 average = performanceClock.getElapsedTime().asMilliseconds();
		int32 actualTime = performanceClock.getElapsedTime().asMilliseconds();
		average = (average * 99.f + (float)actualTime ) /100.f;

		txt.setPosition(0, 0);
		txt.setFont(res.fonts[1]);
		txt.setCharacterSize(35);
		txt.setFillColor(Color::White);
		txt.setStyle(sf::Text::Bold);
		std::stringstream ss;
		ss << "ms: " << average;
		txt.setString(ss.str());
	}

	wnd.draw(txt);
}
void out()
{

}


int main()
{
	init();

	while (wnd.isOpen())
	{
		actionMap.clearEvents();
		Event ev;
		while (wnd.pollEvent(ev))
		{
			if (ev.type == Event::Closed
				|| (ev.type == Event::KeyPressed && ev.key.code == sf::Keyboard::Escape))
				wnd.close();
			actionMap.pushEvent(ev);
		}
		update();

		wnd.display();
	}
	out();
}