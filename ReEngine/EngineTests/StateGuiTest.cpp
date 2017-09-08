#include "StateGuiTest.h"

void StateGuiTest::onStart()
{
	Super::onStart();
	res.deserialise("Resources.txt");

	restartKey.setKeyCode(sf::Keyboard::P);
	restartKey.desiredState = Control::Key::EPressState::pressedOnce;


	Gui::gui.add<Gui::NamedButton>()
		->setPosition({ 450.f, 150.f })
		->setStateMouseOut(Color(155, 155, 155))
		->setStateMouseOn(Color(170, 170, 170))
		->setStatePressed(Color(190, 155, 155))
		->setWh({ 150,40 })
		->setShortKey(sf::Keyboard::Q)
		->setName("hello")
		;

	Gui::gui.add<Gui::ProgressBar>()
		->setPosition({ 450.f, 375.f })
		->setWh({ 30,300 })
		->setStateBackground(Color(55, 55, 55))
		->setStateForeground(Color(200, 55, 55, 100))
		->setProgress(0.3f)
		->setDirectionMode(Gui::ProgressBar::directionYMiddle)
		;



	Gui::gui.add<Gui::CheckBox>()
		->setPosition({ 250.f, 150.f })
		->setStateOn(Color(155, 200, 155))
		->setStateOff(Color(200, 155, 155))
		->setWh({ 150,40 })
		;

	Gui::gui.add<Gui::ScrollBar>()
		->setPosition({ 250.f, 375.f })
		->setWh({ 30,300 }, 40)
		->setStateBackground(Color(55, 55, 55))
		->setAxis(Gui::ScrollBar::vertical)
		->setStateButtonMouseOut(Color(155, 155, 155))
		->setStateButtonMouseOn(Color(170, 170, 170))
		->setStateButtonPressed(Color(190, 155, 155))
		;

		Gui::gui.add<Gui::SetBar>()
		->setStateBarMouseOut(Color(100, 100, 100))
		->setStateBarMouseOn(Color(150, 150, 150))
		->setStateBarPressed(Color(150, 100, 100))

		->setStateButtonMouseOut(Color(150, 125, 125))
		->setStateButtonMouseOn(Color(175, 150, 150))
		->setStateButtonPressed(Color(175, 125, 125))

		->setAxis(Gui::SetBar::vertical)
		->setWh({ 30,300 }, 70)
		->setBarName("bar: ")

		->setPosition({ 300,300 })
		->setRepetitionRate(sf::seconds(0.15f))
		;

}

Game::State * StateGuiTest::onUpdate(sf::Time dt)
{
	cam.display(wnd);
	if (restartKey.isReady())
		return new StateGuiTest;

	return nullptr;
}

void StateGuiTest::onExit()
{
	Gui::gui.clear();
}
