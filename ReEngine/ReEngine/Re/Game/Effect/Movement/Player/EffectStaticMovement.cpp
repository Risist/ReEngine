#include <Re\Game\Effect\Movement\Player\EffectStaticMovement.h>
#include <Re\Game\Game.h>

namespace Effect
{
	StaticMovement::StaticMovement(float32 _linearSpeed)
		: MovementAim(_linearSpeed)
	{
		setMinimalDistance(0.f);
	}

	void StaticMovement::onInit()
	{
		setAxis("xMove", "yMove");
	}

	void StaticMovement::onUpdate(sf::Time dt)
	{
		assert(xAxis && yAxis);

		Vector2D offset = { xAxis->getValue(), yAxis->getValue()};
		
		if (!offset.isZero())
		{
			applyInfluence(offset);
		}
		Super::onUpdate(dt);
	}
	StaticMovement * StaticMovement::setAxis(const string & x, const string & y)
	{
		xAxis = getActor()->getInputAxis(x);
		yAxis = getActor()->getInputAxis(y);
		return this;
	}
	/*void StaticMovement::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
		/// TODO
	}
	void StaticMovement::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		setKeys(loader.load<string>("keyUp", "up"),
			loader.load<string>("keyDown", "down"),
			loader.load<string>("keyLeft", "left"),
			loader.load<string>("keyRight", "right"));
	}*/
}