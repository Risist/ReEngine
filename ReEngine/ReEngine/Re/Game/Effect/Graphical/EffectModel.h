#pragma once
#include <Re\Game\Effect\Graphical\EffectDisplayable.h>
#include <Re\Graphics\Graphics.h>


namespace Effect
{
	/// Efect which will simplyfy maintaining
	/// Models within game objects
	class Model final: public Displayable
	{
		SERIALISATION_NAME(Model)
	public:
		Model() {};
		Model(const char* path);
		Model(ResId scriptId);

		/// events

		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;
		virtual void onDisplay() override;

		Model* setModelParent(sf::Transformable* parent)
		{
			model.parent = parent;
			return this;
		}
		REDEFINE_SETTER_1(Model, setDisplayLayer, Game::Layer*)

		/// graphics data 
		Graphics::Model model;
		vector<Graphics::Model*> modelsUpdate, modelsRendering;
	private:
		//ResId resId;
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};
}