#pragma once
#include <Re\Ai\Mind\AiMind.h>
#include <Re\Ai\AiEmotionDef.h>

namespace Ai
{
	////////////////////////////////////////////////////////////////////////////////
	/// evaluation with constant wague
	class BehaviourEvConstant :public BehaviourBase
	{
	public:
		BehaviourEvConstant(Utility_t _base) :baseUtility(_base){}
		virtual Utility_t getUtility() const override { return baseUtility; }

		Utility_t baseUtility{ 0 };

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

	////////////////////////////////////////////////////////////////////////////////
	/// evaluation behaviour to fullfil emotional behaviours purpose 
	class BehaviourEvEmotion : public BehaviourEvConstant
	{
	public:
		BehaviourEvEmotion(EmotionDef *_ownersMood = nullptr, Utility_t _base = 0.f, Utility_t _scale = 1.f) 
			:BehaviourEvConstant(_base), scaleUtility(_scale), ownersMood(_ownersMood) {}
		BehaviourEvEmotion(const EmotionDef& myEmotion, EmotionDef *_ownersMood = nullptr, Utility_t _base = 0.f, Utility_t _scale = 1.f) 
			:BehaviourEvConstant(_base), scaleUtility(_scale), ownersMood(_ownersMood), behaviourEmotion(myEmotion) {}
		virtual Utility_t getUtility() const override;

		EmotionDef *ownersMood{nullptr};
		EmotionDef behaviourEmotion;
		Utility_t scaleUtility{ 1 };


	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

	////////////////////////////////////////////////////////////////////////////////
	/// evaluation behaviour allowing to done evaluation based on inactive time
	class BehaviourEvTime : public BehaviourEvConstant
	{
	public:
		BehaviourEvTime(Utility_t _base = 0.f, Utility_t _scale = 1.f)
			:BehaviourEvConstant(_base), scaleUtility(_scale) {}

		virtual void onExit() override { clock.restart(); }
		virtual Utility_t getUtility() const override
		{
			return baseUtility + scaleUtility *clock.getElapsedTime().asSeconds();
		}

		EmotionDef *ownersMood;
		EmotionDef behaviourEmotion;
		Utility_t scaleUtility{ 1 };

	private:
		sf::Clock clock;
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};





}