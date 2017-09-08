#pragma once
#include <Re\Graphics\Gui\Gui.h>
#include <Re\Graphics\ResourceManager.h>

namespace Gui
{
	class EditorModel : public Menu
	{
	public:
		EditorModel();

		void update(RenderTarget& wnd, RenderStates states) override;

		//shared_ptr<Gui::Button> 

		Graphics::Model* getActual()
		{
			return models[(size_t)partId->getProgres()];
		}

		Graphics::Model model;

		vector<Graphics::Model*> models;
		SetBar* partId;
		vector<ResId> tsIds;
	};

}

