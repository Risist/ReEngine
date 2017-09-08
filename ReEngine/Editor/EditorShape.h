#pragma once
#include <Re\Graphics\Gui\Gui.h>
#include <Re\Graphics\GraphicsPolygonShape.h>

namespace Gui
{
	class EditorShape : public Menu
	{
	public:
		EditorShape();

		void update(RenderTarget& wnd, RenderStates states) override;

		size_t getPointId()
		{
			return pointId->getProgres();
		}

		Graphics::PolygonShape shape;
	private:
		Gui::SetBar *pointId;
		Gui::CheckBox *cbDisplayPoints;
		Gui::SetBar *posX, *posY;
	};
}

