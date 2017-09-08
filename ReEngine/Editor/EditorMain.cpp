#include <Re\ReEngine.h>
#include <Re\Graphics\Gui\Gui.h>
#include <Re\Lambdas.h>
#include "EditorModel.h"
#include "EditorShape.h"


void init()
{
	wnd.create(VideoMode(800, 600), "ReEngine");
	wnd.setFramerateLimit(seconds(1.f / 30.f).asMicroseconds());

	cam.create(Vector2D(wnd.getSize().x, wnd.getSize().y));
	cam.setBackgroundColor(Color(0, 0, 0));
	cam.setDarkness(1);
	cam.setBackgroundColor(Color(150, 150, 150));

	res.deserialise("Resources.txt");

	//map<string, shared_ptr<Gui::Base> > guiMap;
	//Gui::Base::loaded = &guiMap;
	//Gui::gui.deserialise("Gui.txt");


	Game::stateManager.setState(
		new Game::StateLambda(
		[&]() 
		{
			//Gui::gui.add(new Gui::EditorModel);
			Gui::gui.add(new Gui::EditorShape);
		}
	));
}


void update()
{
	static Clock clock;
	Game::stateManager.onUpdate(clock.getElapsedTime());
	clock.restart();

	Gui::gui.update(wnd, RenderStates::Default);

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