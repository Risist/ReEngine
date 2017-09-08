#include "EditorShape.h"
#include <Re\Graphics\Gui\GuiSpecial.h>
#include <Re\Graphics\Graphics.h>
extern RenderWindow wnd;

namespace Gui
{

	EditorShape::EditorShape()
	{
		shape.deserialise("model.txt");

		float32 offset = 35, longOffset = 65;
		float32 offsetX = 105, longOffsetX = 115;

		float32 minX = 115;
		float32 acY = 25;
		float32 acX = minX;

		gui.add(new Button("Background.txt"))->setPos(Vector2D(0, 0))->setHalfWh(Vector2D(225, 700));
		gui.add(new Button("Background.txt"))->setPos(Vector2D(0, 0))->setHalfWh(Vector2D(450, 50));
		//////////////////////
		acX = 65;

		auto addPoint = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("add"); acX += offsetX;
		auto delPoint = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("delete"); acX += offsetX;

		auto saveShape = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("save"); acX += offsetX;
		auto loadShape = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("load"); acX += longOffsetX;


		acY += longOffset;
		acX = minX;

		///////////////////////////////
		pointId = gui.add(new SetBar("SetBar.txt"))->setName("point: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		posX = gui.add(new SetBar("SetBar.txt"))->setName("posX: ")->setPos(Vector2D(acX, acY)); acY += offset;
		posY = gui.add(new SetBar("SetBar.txt"))->setName("posY: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		auto layers = gui.add(new SetBar("SetBar.txt"))->setName("layers: ")->setPos(Vector2D(acX, acY)); acY += offset;
		auto radius = gui.add(new SetBar("SetBar.txt"))->setName("radius: ")->setPos(Vector2D(acX, acY)); acY += offset;
		auto cd = gui.add(new SetBar("SetBar.txt"))->setName("cd: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		gui.add(new Text("Text.txt"))->setStr("Color")->setPos(Vector2D(acX, acY)); acY += 50;
		auto colorBar = gui.add(new ColorBar("ColorBar.txt"))->setPos(Vector2D(acX, acY)); acY += 80;

		gui.add(new Text("Text.txt"))->setStr("DisplayPoints")->setPos(Vector2D(acX, acY)); acY += offset;
		cbDisplayPoints = gui.add(new CheckBox("CheckBox.txt"))->setPos(Vector2D(acX, acY)); acY += offset;

		/////////////////////////////////
		auto increaseValueOne = []() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				return 0.1f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				return 10.f;
			else
				return 1.f;
		};

		auto increaseValueOnePlus = []() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				return 10.f;
			else
				return 1.f;
		};

		auto increaseValueOneMin = []() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				return 0.01f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				return 1.f;
			else
				return 0.1f;
		};
		
		pointId->setMinMax(1,shape.getPointCount()-2, 1)->setProgress(1)
			->setEvent([=](float&) 
			{
				posX->setProgress(shape.getPoint(getPointId()).x);
				posY->setProgress(shape.getPoint(getPointId()).y);
			} )
			->setEventMinus([]() {return Keyboard::isKeyPressed(Keyboard::Q); })
			->setEventPlus([]()  {return Keyboard::isKeyPressed(Keyboard::E); });

		posX->setInitial(0)->setProgress(shape.getPoint(getPointId()).x)->setIncrease(increaseValueOne)
			->setEvent([=](float& f) { 
				shape.setPoint(getPointId(), Vector2D(f, shape.getPoint(getPointId()).y));
			})
			->setEventMinus([]() {return Keyboard::isKeyPressed(Keyboard::A); })
			->setEventPlus([]()  {return Keyboard::isKeyPressed(Keyboard::D); });
		
		
		posY->setInitial(0)->setProgress(shape.getPoint(getPointId()).y)->setIncrease(increaseValueOne)
			->setEvent([=](float& f) {
				shape.setPoint(getPointId(), Vector2D(shape.getPoint(getPointId()).x, f));
			})
			->setEventMinus([]() {return Keyboard::isKeyPressed(Keyboard::W); })
			->setEventPlus([]()  {return Keyboard::isKeyPressed(Keyboard::S); });

		layers->setMinMax(1, 1000000, 1)->setProgress(shape.getLayersCount())->setEvent([=](float&f) {shape.setLayersCount(f); })
			->setIncrease(increaseValueOnePlus)
			->setEventMinus([]() {return Keyboard::isKeyPressed(Keyboard::O); })
			->setEventPlus([]() {return Keyboard::isKeyPressed(Keyboard::P); });
		

		radius->setMinMax(0.f, 100000000.f, 0)->setProgress(shape.getChangeRadius())
			->setEvent([=](float32& f) { shape.setChangeRadius(f); })
			->setIncrease( increaseValueOne)
			->setEventMinus([](){return Keyboard::isKeyPressed(Keyboard::K); })
			->setEventPlus([]() {return Keyboard::isKeyPressed(Keyboard::L); });

		cd->setMinMax(0.f, 100000000.f, 0)->setProgress(shape.getCdChange().asSeconds())
			->setEvent([=](float32& f) { shape.setCdChange(sf::seconds(f)); })
			->setIncrease(increaseValueOneMin)
			->setEventMinus([]() {return Keyboard::isKeyPressed(Keyboard::Z); })
			->setEventPlus([]()  {return Keyboard::isKeyPressed(Keyboard::X); });

		colorBar->setColor(shape.getColor())->setEvent([=](Color& cl) {shape.setColor(cl); });


		addPoint->setEvent([=]() {
			shape.addPoint(getPointId()); ++pointId->maximalValue;
			pointId->setProgress(pointId->getProgres()+1);
			posX->setProgress(shape.getPoint(getPointId()).x );
			posY->setProgress(shape.getPoint(getPointId()).y );
		});

		delPoint->setEvent([=]() {
			shape.delPoint(getPointId()); --pointId->maximalValue;
			posX->setProgress(shape.getPoint(getPointId()).x);
			posY->setProgress(shape.getPoint(getPointId()).y);
		});

		saveShape->setEvent([=]() {shape.serialise("model.txt"); }); 

		loadShape->setEvent([=]() {
			shape.deserialise("model.txt"); 
			posX->setProgress(shape.getPoint(getPointId()).x);
			posY->setProgress(shape.getPoint(getPointId()).y);
			pointId->maximalValue = shape.getPointCount() - 2;
			pointId->setProgress(1);
			layers->setProgress(shape.getLayersCount());
			radius->setProgress(shape.getChangeRadius());
			cd->setProgress(shape.getCdChange().asSeconds() );
			colorBar->setColor(shape.getColor() );
		});
	}

	

	void EditorShape::update(RenderTarget & wnd, RenderStates states)
	{
		Menu::update(wnd, states);
		cam.draw(shape);

		if (cbDisplayPoints->b)
		{
			sf::CircleShape sh(7);
			sh.setOrigin(sh.getRadius(), sh.getRadius());

			for (int i = 1; i < shape.getPointCount() - 1; ++i)
			{
				sh.setPosition(shape.getPoint(i));
				sh.setFillColor(i == getPointId() ? Color(0, 200, 0) : Color(200, 0, 0));
				cam.draw(sh);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && ::wnd.hasFocus())
		{
			shape.setPoint(getPointId(), Vector2f(Mouse::getPosition(::wnd).x - ::wnd.getSize().x*0.5, Mouse::getPosition(::wnd).y - ::wnd.getSize().y * 0.5));
			posX->setProgress(shape.getPoint(getPointId()).x);
			posY->setProgress(shape.getPoint(getPointId()).y);
		}
	}

}