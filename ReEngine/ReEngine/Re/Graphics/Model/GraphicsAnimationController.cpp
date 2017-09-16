#include <Re\Graphics\Model\GraphicsAnimationController.h>
#include <Re\Graphics\Model\GraphicsModel.h>

namespace Graphics
{

	AnimationController::AnimationController()
	{
	}

	void AnimationController::onUpdate()
	{
		for (auto it : parts)
			it.onUpdate();
	}

	
	void AnimationController::addPart(const AnimationPart& newPart)
	{
		parts.push_back(newPart);
		parts.back().step = &step;
	}

	void AnimationController::attachToModel(vector<ModelPart*>& model)
	{
		for (auto&it : parts)
		{
			assert(it.modelId < model.size());
			it.attachToModel(model[it.modelId]);
		}
	}
	void AnimationController::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
#ifdef RE_ENGINE
		/// animation serialization available only in editor
		/// TODO
#endif // RE_ENGINE
	}

	void AnimationController::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		AnimationStep::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			addPart(AnimationPart());
			parts.back().deserialise(file, loader);
		}
	}

}