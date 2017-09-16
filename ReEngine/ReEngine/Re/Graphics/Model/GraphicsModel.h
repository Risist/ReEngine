#pragma once
#include <Re\Graphics\ResourceManager.h>
#include <Re\Graphics\Model\GraphicsModelDef.h>

// #define RE_EDITOR

namespace Graphics
{
	
	class ModelPart : 
		public BinaryTree<ModelPart, sf::Transformable>,
		public Transformable,
		public Res::ISerialisable
	{
	public:
		ModelPart();

		void onUpdate();
		void onDraw(sf::RenderTarget& target, sf::RenderStates states);

		void applayAnimation( const ModelDef& def)
		{
			animationDef += def;
			++appliedAnimationsCount;
		}

		/// permanently edits model statistics
		void applayPose(const ModelDef& def)
		{
			baseDef += def;
		}




		////// setters
		void setOrigin(const Vector2D& s) { sp.setOrigin(s); }
		void setTexture(ResId tsId) { tsInst[tsId].setSprite(sp); }

		////// getters
		Vector2D getOrigin() const { return sp.getOrigin(); }

		Vector2D getPosition() const { return Transformable::getPosition(); }
		Vector2D getScale() const { return Transformable::getScale(); }
		Color getColor() const { return sp.getColor(); }
		Angle getRotation() const { return Degree(Transformable::getRotation()); }
		

	private:
		using Transformable::setPosition;
		using Transformable::setRotation;
		using Transformable::setScale;
		using Transformable::move;
		using Transformable::rotate;
		using Transformable::scale;

		sf::Sprite sp;
	private:
		ModelDef baseDef;
		/// animation influences
		mutable ModelDef animationDef;
		/// how many animationa has been applied
		size_t appliedAnimationsCount;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
}