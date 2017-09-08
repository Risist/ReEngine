#pragma once
#include <Re\Ai\Mind\AiMind.h>

/// WIP
namespace Ai
{

	

	class Caller
	{
	public:



		//EmotionDef mood;

		sf::Clock timerLastSay;
		Utility_t lastSayScale{1.f};
		Utility_t lastSayAnyoneScale{1.f};
	};

	class Dialogue
	{
	public:


		sf::Clock timerLastSayAnyone;
		vector<Caller> participants;
	};

	class BehaviourSay : public BehaviourBase
	{
	public:

	};
	
}