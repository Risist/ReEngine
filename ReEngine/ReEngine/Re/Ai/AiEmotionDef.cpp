#include <Re\Ai\AiEmotionDef.h>


namespace Ai
{
	///		happiness - sadness		(0;180 degree)
	///		trust - disgust			(45;225 degree)
	///		fear - anger			(90;270 degree)
	///		surprise - anticipation	(135;315 degree)
	EmotionDef EmotionDef::unitAnger		= Vector2D(1, 0).getRotated(Degree(270));
	EmotionDef EmotionDef::unitFear			= Vector2D(1, 0).getRotated(Degree(90));
	EmotionDef EmotionDef::unitHappiness	= Vector2D(1, 0).getRotated(Degree(0));
	EmotionDef EmotionDef::unitSadness		= Vector2D(1, 0).getRotated(Degree(180));
	EmotionDef EmotionDef::unitTrust		= Vector2D(1, 0).getRotated(Degree(45));
	EmotionDef EmotionDef::unitDisgust		= Vector2D(1, 0).getRotated(Degree(225));
	EmotionDef EmotionDef::unitSurprice		= Vector2D(1, 0).getRotated(Degree(135));
	EmotionDef EmotionDef::unitAnticipation = Vector2D(1, 0).getRotated(Degree(315));
	void EmotionDef::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("emotionPosX", value.x);
		saver.save("emotionPosY", value.y);
	}
	void EmotionDef::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		value.x = loader.load("emotionPosX", 0.f);
		value.y = loader.load("emotionPosY", 0.f);

		addAnger		(loader.load("anger", 0.f));
		addFear			(loader.load("fear", 0.f));
		addHappiness	(loader.load("happiness", 0.f));
		addSadness		(loader.load("sadness", 0.f));
		addTrust		(loader.load("trust", 0.f));
		addDisgust		(loader.load("disgust", 0.f));
		addSurprice		(loader.load("surprice", 0.f));
		addAnticipation	(loader.load("anticipation", 0.f));
	}
}