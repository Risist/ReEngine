#include "EditorModel.h"
#include <Re\Graphics\Gui\GuiSpecial.h>
#include <Re\Graphics\Graphics.h>

namespace Gui
{

	EditorModel::EditorModel()
	{
		model.deserialise("model.txt");
		model.rewriteToVectorRendering(models);

		float32 offset = 35, longOffset = 45;
		float32 offsetX = 105, longOffsetX = 115;

		float32 minX = 115;
		float32 acY = 25;
		float32 acX = minX;

		gui.add(new Button("Background.txt"))->setPos(Vector2D(0, 0))->setHalfWh(Vector2D(225, 700));
		gui.add(new Button("Background.txt"))->setPos(Vector2D(0, 0))->setHalfWh(Vector2D(500, 50));
		//////////////////////
		acX = 65;
		auto addModelUp = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("addUp"); acX += offsetX;
		auto addModelDown = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("addDown"); acX += offsetX;
		auto delModel = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("del Model"); acX += longOffsetX;
		
		auto saveModel = gui.add(new NamedButton("ButtonHalf.txt"))->setPos(Vector2D(acX, acY))->setName("save"); acX += longOffsetX ;

		acY += longOffset;
		acX = minX;

		///////////////////////////////
		partId = gui.add(new SetBar("SetBar.txt"))->setName("part: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		auto textureId = gui.add(new SetBar("SetBar.txt"))->setName("ts: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		auto posX = gui.add(new SetBar("SetBar.txt"))->setName("posX: ")->setPos(Vector2D(acX, acY)); acY += offset;
		auto posY = gui.add(new SetBar("SetBar.txt"))->setName("posY: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		auto rot = gui.add(new SetBar("SetBar.txt"))->setName("rot: ")->setPos(Vector2D(acX, acY)); acY += offset;
		auto rotAround = gui.add(new SetBar("SetBar.txt"))->setName("rotAround: ")->setPos(Vector2D(minX, acY)); acY += longOffset;

		auto scaleX = gui.add(new SetBar("SetBar.txt"))->setName("scaleX: ")->setPos(Vector2D(acX, acY)); acY += offset;
		auto scaleY = gui.add(new SetBar("SetBar.txt"))->setName("scaleY: ")->setPos(Vector2D(acX, acY)); acY += longOffset;

		gui.add(new Text("Text.txt"))->setStr("Color")->setPos(Vector2D(acX, acY)); acY += 50;
		auto colorBar = gui.add(new ColorBar("ColorBar.txt"))->setPos(Vector2D(acX, acY)); acY += 80;

		///////////////////////////////////
		partId->setMinMax(0, models.size(), 0);

		/*textureId->setMinMax(0, 99999999999, 0)->setProgress(getActual()->tsId)
			->setEvent([=](float32& v) {getActual(); });
		*/
		////////////// scale
		auto inncreaseValueScale = []() { 
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				return 0.001f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				return 0.1f;
			else
				return 0.01f;
		};
		scaleX->setInitial(1.f)->setIncrease(inncreaseValueScale)->setProgress(getActual()->scale.x)
			->setEvent([=](float32& v) {getActual()->scale.x = v; });
		scaleY->setInitial(1.f)->setIncrease(inncreaseValueScale)->setProgress(getActual()->scale.y)
			->setEvent([=](float32& v) {getActual()->scale.y = v; });


		/// position
		auto inncreaseValuePosition = []() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				return 0.1f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				return 10.f;
			else
				return 1.f;
		};
		posX->setInitial(0.f)->setIncrease(inncreaseValuePosition)->setProgress(getActual()->pos.x)
			->setEvent([=](float32& v) {getActual()->pos.x = v; });
		posY->setInitial(0.f)->setIncrease(inncreaseValuePosition)->setProgress(getActual()->pos.y)
			->setEvent([=](float32& v) {getActual()->pos.y = v; });


		/// rotation
		auto inncreaseValueRotation = []() {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
				return 0.1f;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				return 10.f;
			else
				return 1.f;
		};
		rot->setInitial(0.f)->setIncrease(inncreaseValueRotation)->setProgress(getActual()->rot.asDegree()) 
			->setEvent([=](float32& v) {getActual()->rot = Degree(v); });
		rotAround->setInitial(0.f)->setIncrease(inncreaseValueRotation)->setProgress(getActual()->rotAround.asDegree())
			->setEvent([=](float32& v) {getActual()->rotAround = Degree(v); });


		//// color
		colorBar->setColor(Color(getActual()->color.r, 
			getActual()->color.g,
			getActual()->color.b,
			getActual()->color.a))
			->setEvent([=](Color cl) 
			{
				getActual()->color.r = cl.r;  
				getActual()->color.g = cl.g;
				getActual()->color.b = cl.b;
				getActual()->color.a = cl.a;
			});

		/// part
		partId->setMinMax(0,models.size()-1,0);
	}

	void EditorModel::update(RenderTarget & wnd, RenderStates states)
	{
		Menu::update(wnd, states);
		model.drawRecursive(cam);
	}
}
