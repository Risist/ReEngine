#include <Re\Game\GameActor.h>
#include <Re\Game\GameWorld.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>

namespace Game
{

	// define function which will be used for serialisation of all standard actors
	MULTI_SERIALISATION_INTERFACE_IMPL(Actor)
	{
		MULTI_SERIALISATION_INTERFACE_CHECK(Actor);
		
		return nullptr;
	}

	Actor::Actor()
		: bAlive(true)
	{
		setActor(this);
	}

	bool Actor::onFrame(sf::Time dt)
	{
		/// dummy code, there is no pause code yet
		bool isGamePaused = false;

		if (isGamePaused)
			onPause(dt);
		else if (isAlive())
			onUpdate(dt);
		else
			return onAgony(dt);

		return false;
	}

	/*void Actor::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save<string>	("name", name, "");
		saver.save<bool>	("alive", bAlive, true);

		saver.nextLine(file);
		Super::serialiseF(file, saver);
	}

	void Actor::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		name	= loader.load<string>	("name", "");
		bAlive	= loader.load<bool>		("alive", true);

		Super::deserialiseF(file, loader);
	}*/

}