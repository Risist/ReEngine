#include <Re\Game\Effect\Health\EffectSpawnOnDeath.h>
#include <Re\Game\GameWorld.h>

namespace Effect
{
	SpawnOnDeath::SpawnOnDeath(function<Game::Actor*()> _createActor)
		:createActor(_createActor)
	{
	}
	bool SpawnOnDeath::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Transformable*>(potentialParent);
	}
	void SpawnOnDeath::onDeath()
	{
		auto actor = createActor();
		if (actor == nullptr)
			return;

		Game::world.insertActor(actor );

		Transformable* parent = (Transformable*)getParent();

		actor->setPosition( parent->getPosition() + 
			position.getRotated(parent->getRotation())
		);
		actor->setRotation(parent->getRotation() + rotation);

		actor->instigator = getActor();

		return;
	}
	/*void SpawnOnDeath::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save<float>("posX", position.x, 0.f);
		saver.save<float>("posY", position.y, 0.f);
		saver.save<float>("rot", rotation.asDegree(), 0.f);
		Super::serialiseF(file, saver);
	}
	void SpawnOnDeath::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		position = {
			loader.load<float>("posX", 0.f),
			loader.load<float>("posY", 0.f)
		};
		rotation = Degree(loader.load<float>("rot", 0.f));
		Super::deserialiseF(file, loader);
	}*/
}