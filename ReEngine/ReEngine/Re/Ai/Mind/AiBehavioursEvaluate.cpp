#include <Re\Ai\Mind\AiBehavioursEvaluate.h>

namespace Ai
{
	//////////////////////////// Const

	void BehaviourEvConstant::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("baseUtility", baseUtility);
	}

	void BehaviourEvConstant::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		baseUtility = loader.load("baseUtility", 0.f);
	}


	//////////////////////////////// Emotion
	Utility_t BehaviourEvEmotion::getUtility() const
	{
		assert(ownersMood);
		return baseUtility + scaleUtility *behaviourEmotion.compare(*ownersMood);
	}

	void BehaviourEvEmotion::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		behaviourEmotion.serialise(file, saver);

		saver.save("baseUtility", baseUtility);
		saver.save("scaleUtility", scaleUtility);
	}

	void BehaviourEvEmotion::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		behaviourEmotion.deserialise(file, loader);

		baseUtility = loader.load("baseUtility", 0.f);
		scaleUtility = loader.load("scaleUtility", 1.f);
	}

	/////////////////////////////////////// Time

	void BehaviourEvTime::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("baseUtility", baseUtility);
		saver.save("scaleUtility", scaleUtility);
	}

	void BehaviourEvTime::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		baseUtility = loader.load("baseUtility", 0.f);
		scaleUtility = loader.load("scaleUtility", 1.f);
	}

}