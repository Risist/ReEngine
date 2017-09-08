#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{
	/* 
	spawns something when actor dies
	
	@parent Game::Actor only
	*/
	class SpawnOnDeath final: public Base
	{
		SERIALISATION_NAME(SpawnOnDeath)
	public:
		SpawnOnDeath(function<Game::Actor*()> _createActor);

		virtual bool canBeParent(Base* potentialParent) const override;
		virtual void onDeath() override;

		
		SpawnOnDeath* setOffset(Vector2D _offset, Angle _angle)
		{
			position = _offset;
			rotation = _angle;
			return this;
		}



		function<Game::Actor*()> createActor;

		/// data which defines spawning pos
		/// relative to owner
		Vector2D position;
		Angle rotation;

		/*
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)override;*/
	};


}