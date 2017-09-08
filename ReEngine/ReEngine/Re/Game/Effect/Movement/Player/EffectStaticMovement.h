#pragma once
#include <Re\Game\Effect\Movement\EffectMovementAim.h>
#include <Re\Common\Control\Control.h>

namespace Effect
{
	/// efect that allows to move player in x and y axes without any rotation
	/// @Warring:  Rigidbody must be created before a first update of the component!
	class StaticMovement : public MovementAim
	{
	public:
		StaticMovement(float32 movementSpeed);

		virtual void onInit() override;
		virtual void onUpdate(sf::Time st) override;

		////// setters

		StaticMovement* setAxis(const string& x, const string& y);

		////// Data - cashed axis
		Control::Axis *xAxis{ nullptr };
		Control::Axis *yAxis{ nullptr };
	/*protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;*/
	};
}