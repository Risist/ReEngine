#include <Re\Graphics\Gui\Gui.h>

namespace Gui
{
	Menu gui;

	MULTI_SERIALISATION_INTERFACE_IMPL(Base)
	{
		MULTI_SERIALISATION_INTERFACE_CHECK(Button);
		MULTI_SERIALISATION_INTERFACE_CHECK(NamedButton);
		MULTI_SERIALISATION_INTERFACE_CHECK(Text);
		MULTI_SERIALISATION_INTERFACE_CHECK(CheckBox);
		MULTI_SERIALISATION_INTERFACE_CHECK(ProgressBar);
		//MULTI_SERIALISATION_INTERFACE_CHECK(ScrollBar);
		//MULTI_SERIALISATION_INTERFACE_CHECK(SetBar);
		MULTI_SERIALISATION_INTERFACE_CHECK(Menu);

		return nullptr;
	}
}
