#include <Re\Ai\Mind\AiBehaviours.h>

namespace Ai
{
	

	////////////////////////////////////////////// Wait

	void BehaviourWait::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("waitTime", waitTime.asSeconds());
	}

	void BehaviourWait::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		waitTime = seconds(loader.load("waitTime", 1.f ));
	}

	////////////////////////////// Lambda
	BehaviourLambda* BehaviourLambda::setOnStart(onStart_t __onStart)
	{
		_onStart = __onStart;
		return this;
	}
	BehaviourLambda* BehaviourLambda::setOnExit(onExit_t __onExit)
	{
		_onExit = __onExit;
		return this;
	}
	BehaviourLambda* BehaviourLambda::setOnExecute(onExecute_t __onExecute)
	{
		_onExecute = __onExecute;
		return this;
	}
	BehaviourLambda* BehaviourLambda::setGetUtility(getUtility_t __getUtility)
	{
		_getUtility = __getUtility;
		return this;
	}
	BehaviourLambda* BehaviourLambda::setGetUtility(Utility_t s)
	{
		_getUtility = [=]() {return s; };
		return this;
	}

}