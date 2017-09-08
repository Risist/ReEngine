#pragma once
#include <Re\Ai\Mind\AiMind.h>

namespace Ai
{
	
	//////////////////////////////////////////////////
	/// behaviour with lambda functions on events
	class BehaviourLambda : public BehaviourBase
	{
	public:

		typedef function<void()> onStart_t;
		typedef function<bool(sf::Time)> onExecute_t;
		typedef function<void()> onExit_t;
		typedef function<Utility_t()> getUtility_t;

		BehaviourLambda* setOnStart(onStart_t __onStart);
		BehaviourLambda* setOnExit(onExit_t __onExit);
		BehaviourLambda* setOnExecute(onExecute_t __onExecute);
		BehaviourLambda* setGetUtility(getUtility_t __getUtility);
		BehaviourLambda* setGetUtility(Utility_t s);


		virtual void onStart() override { if (_onStart) _onStart(); }
		virtual bool onExecute(sf::Time dt)override { if (_onExecute) return _onExecute(dt); else return false; }
		virtual void onExit() override { if (_onExit) _onExit(); }
		virtual Utility_t getUtility() const override { if (_getUtility) return _getUtility(); }

		onStart_t _onStart{ []() {} };
		onExecute_t _onExecute{ [](sf::Time dt) { return true; } };
		onExit_t _onExit{ []() {} };
		getUtility_t _getUtility{ []() {return 1.f; } };
	};

	///////////////////////////////////////////////////////////////////////
	/// behaviour which does nothing for certain amount of time
	class BehaviourWait : public BehaviourBase
	{
	public:
		BehaviourWait(sf::Time _waitTime = sf::seconds(1.f), Utility_t _utility = 1.f)
			:waitTime(_waitTime)
		{

		}

		virtual void onStart() override { clock.restart(); }
		virtual bool onExecute(sf::Time dt ) override{ return clock.getElapsedTime() > waitTime; }

		sf::Time waitTime;
	private:
		Clock clock;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

	///////////////////////////////////////////////////////////////////
	/// behaviour to divide Evaluation, execution and finish up condition to separated behaviours

	///////////////////////////////////////////////////////////////////////
	/// behaviour which allows to execute many other behaviours at once

}