#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{
	ModelPart::ModelPart()
		: baseDef(ModelDef::default), animationDef(ModelDef::zero)
	{
		setThis((Math::Transform*)this);
	}

	void ModelPart::applayAnimation(const ModelDef& def)
	{
		animationDef += def;
		++appliedAnimationsCount;
	}

	void ModelPart::onUpdate()
	{
		assert(getParent());
		
		ModelDef actualDef = baseDef;
		
		if(appliedAnimationsCount != 0)
		{
			float32 divisor = 1.f / (float32)appliedAnimationsCount;
			animationDef *= divisor;
			actualDef+=animationDef;
		}	

		setScale(actualDef.scale * getParent()->getScale());
		
		setPosition(
			actualDef.position
				.getRotated(getParent()->getRotation() + actualDef.rotation)
					
			+ getParent()->getPosition()
		);
		
		setRotation(getParent()->getRotation() + actualDef.rotation);

		/// reset animation Count
		appliedAnimationsCount = 0;
		animationDef = actualDef;
	}
	
	void ModelPart::onDraw(RenderTarget & target, RenderStates states)
	{
		/// update from Transformable state
		sp.setPosition(getPosition());
		sp.setRotation(getRotation().asDegree() + animationDef.mineRotation.asDegree());
		sp.setScale(getScale());
		sp.setColor(
			Color(
				(sf::Uint8)clamp(animationDef.color.r , 0.f, 255.f),
				(sf::Uint8)clamp(animationDef.color.g , 0.f, 255.f),
				(sf::Uint8)clamp(animationDef.color.b , 0.f, 255.f),
				(sf::Uint8)clamp(animationDef.color.a , 0.f, 255.f)
			)
		);

		/// draw
		target.draw(sp, states);

		/// reset state
		animationDef = ModelDef::zero;
	}

	void ModelPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_EDITOR
		/// Only in editor
		/// TODO
#endif // RE_EDITOR
	}

	void ModelPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		baseDef.deserialise(file, loader);

		/// set texture
		ResId tsId = loader.load("ts", 0);
		if (tsId != 0)
			setTexture(tsId);
		else
			sp.setTextureRect(sf::IntRect() );

		setOrigin({
			loader.load<float32>("originX", 0.f),
			loader.load<float32>("originY", 0.f)
		});

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			string b = loader.load<string>("ud", "down");
			ModelPart *m = new ModelPart();

			if (b == "up")
				addUp(m);
			else // if( b == "down")
				addDown(m);

			m->deserialise(file, loader);
		}

		animationDef = baseDef;
	}
}