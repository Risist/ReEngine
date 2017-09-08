#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{

	/*
	component which moves actor forward
	@parent: Game::Actor only
	*/
	class Motor final : public Base
	{
		SERIALISATION_NAME(Motor)
	public:
		Motor(float32 movementSpeed = 0.f, Angle angleOffset = Angle() );

		virtual bool canBeParent(Base* potential) const override;
		virtual void onUpdate(sf::Time dt) override;

		float32 movementSpeed;
		Angle angleOffset;
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};

}
