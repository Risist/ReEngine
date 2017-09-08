#pragma once
#include <Re\Game\Effect\EffectBase.h>
#include <Re\Game\GameLayer.h>

namespace Effect
{

	/*
	Decomposition of all displayable effects
	Manages all things about display layers for you
	*/
	class Displayable : public Base
	{
	public:
		Displayable() = default;

		/// only a transformable can be parent for Displayable
		virtual bool canBeParent(Base* potentialParent) const override;

		/// childrens have to define display behaviour
		virtual void onDisplay() override = 0;


		virtual void onInit() override;

		/// add to display layer when spawned
		virtual void onRespawn() override;
		/// remove from display layer when dead
		virtual void onDeath() override;

		

		Displayable* setDisplayLayer(Game::Layer* displayLayer)
		{
			myDisplayLayer = displayLayer;
			return this;
		}

	private:
		/// manually add to display layer
		void addToDisplayLayer();
		/// manually remove from display layer
		void removeFromDisplayLayer();

		Game::Layer* myDisplayLayer;

	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};


}