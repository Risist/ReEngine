#include <Re\Game\Effect\Graphical\EffectDisplayable.h>
#include <Re\Game\GameWorld.h>

namespace Effect
{




	bool Displayable::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}

	void Displayable::onInit()
	{
		//Super::onInit();
		myDisplayLayer = getActor()->getWorld()->getDisplayLayerById(0);
	}

	void Displayable::onRespawn()
	{
		//Super::onRespawn();
		addToDisplayLayer();
	}

	void Displayable::onDeath()
	{
		//Super::onDeath();
		removeFromDisplayLayer();
	}

	void Displayable::addToDisplayLayer()
	{
		assert(myDisplayLayer);
		myDisplayLayer->addEffect(this);
	}

	void Displayable::removeFromDisplayLayer()
	{
		assert(myDisplayLayer);
		myDisplayLayer->removeEffect(this);
	}

	/*void Displayable::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
		/// Todo
	}

	void Displayable::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		myDisplayLayer = getActor()->getWorld()->getDisplayLayerById(loader.load<size_t>("displayLayerId", 0));
	}*/

}