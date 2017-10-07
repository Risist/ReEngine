#include <Re\Graphics\Model\GraphicsAnimationPart.h>
#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Common\Math\Math.h>

namespace Graphics
{

	void AnimationPart::onUpdate() const
	{
		assert(maintainedModel);
		maintainedModel->applayAnimation(getDefAtStep(getActualStep()));
	}
	void AnimationPart::applyPose() const
	{
		assert(maintainedModel);
		maintainedModel->applayPose(getDefAtStep(getActualStep()));
	}
	ModelDef AnimationPart::getDefAtStep(Step_t step) const
	{
		/// Animation Part has to have at least one keystone
		assert(!keystones.empty());

		/// bounding range checks
		if (step >= keystones.back().step)
			return keystones.back().desiredDef;
		else if (step <= keystones.front().step)
			return keystones.front().desiredDef;
		/// case of one keystone is handled by checks above

		/// find the most fitting partition
		
		/// front keystone of partition step is within
		auto actualKeystone = keystones.begin();
		for (; actualKeystone != keystones.end()-1; ++actualKeystone)
			if (step >= actualKeystone->step && step <= (actualKeystone+1)->step)
				goto ret;
		
		/// this should be never hit
		/// if does probably keystones are not sorted
		assert(false); 

	ret:
		ModelDef retDef = actualKeystone->desiredDef +
			((actualKeystone + 1)->desiredDef - actualKeystone->desiredDef)
			*(step - actualKeystone->step)
			/ ((actualKeystone + 1)->step - actualKeystone->step);

		return retDef;
	}

	void AnimationPart::finaliseKeystones()
	{
		std::sort(keystones.begin(), keystones.end() );
	}

	void AnimationPart::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		/// TODO
	}
	void AnimationPart::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		modelId = loader.load("model", 0u); 
		AnimationStepHolder::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			KeyStone keystone;
			//keystone.desiredDef.deserialise(file, loader);
			{
				keystone.desiredDef.position.x = loader.load("posX", ModelDef::zero.position.x);
				keystone.desiredDef.position.y = loader.load("posY", ModelDef::zero.position.y);

				keystone.desiredDef.scale.x = loader.load("scaleX", ModelDef::zero.scale.x);
				keystone.desiredDef.scale.y = loader.load("scaleY", ModelDef::zero.scale.y);

				keystone.desiredDef.rotation = Degree(loader.load("rot", ModelDef::zero.rotation.asDegree()));
				keystone.desiredDef.mineRotation = Degree(loader.load("mineRot", ModelDef::zero.mineRotation.asDegree()));

				keystone.desiredDef.color.r = loader.load("clR", ModelDef::zero.color.r);
				keystone.desiredDef.color.g = loader.load("clG", ModelDef::zero.color.g);
				keystone.desiredDef.color.b = loader.load("clB", ModelDef::zero.color.b);
				keystone.desiredDef.color.a = loader.load("clA", ModelDef::zero.color.a);
			}

			keystone.step = loader.load<Step_t>("step", 0.f);
			keystones.push_back(keystone);
		}

		finaliseKeystones();
	}
}