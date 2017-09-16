#pragma once
#include <Re\Graphics\Model\GraphicsAnimationPart.h>

namespace Graphics
{
	class AnimationController : public Res::ISerialisable, public AnimationStep
	{
	public:
		AnimationController();
		
		/// call this on every frame before model update/ after drawing
		/// updates model's actulDef to fullfil model state after appling animation
		/// @arg:scale - allows you to scale influence of the animation
		///			usefull for example in merging animations
		void onUpdate();

		/// add new animation part 
		void addPart(const AnimationPart& newPart);

		/// attach the animation to model
		/// AnimationParts holds ptr to models they are animating 
		/// modelId determine which modelPart is choosen
		/// call after initialisation of modelId(deserialise function) and before first onUpdate
		/// @Warring! slow operation. Don't use that on every frame 
		void attachToModel(vector<ModelPart*>& model);

	private:
		/// animation parts holded
		vector<AnimationPart> parts;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}