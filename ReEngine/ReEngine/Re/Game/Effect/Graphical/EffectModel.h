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
			rootModel.setParent( parent );
			return this;
		}
		REDEFINE_SETTER_1(Model, setDisplayLayer, Game::Layer*)

		/// graphics data 
		Graphics::ModelPart rootModel;
		vector<Graphics::ModelPart*> modelsUpdate, modelsRendering;
	};
}