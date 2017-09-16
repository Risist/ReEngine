#include <Re\Graphics\Model\GraphicsAnimationPart.h>
#include <Re\Graphics\Model\GraphicsModel.h>
#include <Re\Common\Math\Math.h>

namespace Graphics
{
	AnimationPart::AnimationPart()
	{
	}
	void AnimationPart::onUpdate()
	{
		assert(maintainedModel);
		maintainedModel->applayAnimation(getDefAtStep(getActualStep()));
	}
	ModelDef AnimationPart::getDefAtStep(Step_t step) const
	{
		/// find the most fitting keystone range
		size_t keystoneId = 0;
		for (; keystoneId < keystones.size(); ++keystoneId)
			if (keystones[keystoneId].step > step)
				break;
		
		/// return limit defs 
		if (keystoneId == keystones.size() || keystoneId == 0)
			return keystones[keystoneId].desiredDef;

		/// keystone.step > step
		KeyStone keystonePrev = keystones[keystoneId-1];
		/// keystone.step < step
		KeyStone keystoneAc = keystones[keystoneId];
		
		return keystonePrev.desiredDef + 
			(keystoneAc.desiredDef - keystonePrev.desiredDef)
			* (step - keystonePrev.step);
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
			keystone.desiredDef.deserialise(file, loader);
			keystone.step = loader.load<Step_t>("step", 0.f);
			keystones.push_back(keystone);
		}

	}
}