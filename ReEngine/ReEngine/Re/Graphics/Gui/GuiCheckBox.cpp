#include <Re\Graphics\Gui\GuiCheckBox.h>

namespace Gui
{

	CheckBox::CheckBox()
		: value(false)
	{
	}


	void Gui::CheckBox::onUpdate(RenderTarget & target, RenderStates states)
	{
		sh.setPosition(getActualPosition());

		bool mouseOn = isMouseOnWindow();

		if ((mouseKey.isReady() && mouseOn) || shortKey.isReady())
		{
			assert(eventOnPress);
			eventOnPress();

			value = !value;

			sh.setFillColor(statePressed.cl);
			statePressed.ts.setRectShape(sh);
		}

		if (value)
		{
			sh.setFillColor(statePressed.cl);
			statePressed.ts.setRectShape(sh);
		}
		else
		{
			sh.setFillColor(stateMouseOut.cl);
			stateMouseOut.ts.setRectShape(sh);
		}

		target.draw(sh, states);
	}


	void Gui::CheckBox::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Base::serialiseF(file, saver);
		saver.save("value", value, false);

		stateMouseOn.serialise_Index("on", file, saver);
		stateMouseOut.serialise_Index("off", file, saver);
	}
	void Gui::CheckBox::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Base::deserialiseF(file, loader);
		value = loader.load("value", false);

		stateMouseOn.deserialise_Index("on", file, loader);
		stateMouseOut.deserialise_Index("off", file, loader);
	}



}