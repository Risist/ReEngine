#include <Re\Game\Effect\EffectTransformable.h>
#include <Re\Game\GameActor.h>
#include "EffectTransformable.h"

namespace Effect
{
	/*void Transformable::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save<float>("posX", getPosition().x, 0.f);
		saver.save<float>("posY", getPosition().y, 0.f);
		saver.save<float>("rot", getRotation().asDegree(), 0.f);
		Super::serialiseF(file, saver);
	}

	void Transformable::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		setPosition( { 
			loader.load<float>("posX", 0.f),
			loader.load<float>("posY", 0.f) 
		});
		setRotation( Degree(loader.load<float>("rot", 0.f)) );
		Super::deserialiseF(file, loader);
	}*/
	bool Transformable::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}
}
