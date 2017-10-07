#pragma once
#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{

	/// non-relative transformation component
	/// allows to hold data about position and rotation and gives some utility functions to manipulate them
	/// 
	class Transformable : public Composite, public Math::Transform
	{
		SERIALISATION_NAME(Transformable)
	public:

		Transformable(const Vector2D& _position = Vector2D(), Angle _rotation = Angle::zero)
		{
			setPosition(_position);
			setRotation(_rotation);
		}

		/// override
		virtual bool canBeParent(Base* potentialParent) const override;


	protected:
		/// serialisation functions - to allow effects to be sierialised from/into .res files
		//virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver)  const override;
		//virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}
