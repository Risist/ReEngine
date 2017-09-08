#pragma once
#include <Re\Common\utility.h>

namespace Ai
{

	class EmotionDef : public Res::ISerialisable
	{
		EmotionDef(const Vector2D& v) : value(v) {}
	public:
		EmotionDef() = default;

		static EmotionDef unitAnger;
		static EmotionDef unitFear;
		static EmotionDef unitHappiness;
		static EmotionDef unitSadness;
		static EmotionDef unitTrust;
		static EmotionDef unitDisgust;
		static EmotionDef unitSurprice;
		static EmotionDef unitAnticipation;

		void addAnger(float s)
		{
			value += unitAnger.value*s;
		}
		void addFear(float s)
		{
			value += unitFear.value*s;
		}
		void addHappiness(float s)
		{
			value += unitHappiness.value*s;
		}
		void addSadness(float s)
		{
			value += unitSadness.value*s;
		}
		void addTrust(float s)
		{
			value += unitFear.value*s;
		}
		void addDisgust(float s)
		{
			value += unitFear.value*s;
		}
		void addSurprice(float s)
		{
			value += unitFear.value*s;
		}
		void addAnticipation(float s)
		{
			value += unitFear.value*s;
		}


		/// returns how similar are two emmotion states
		float compare(const EmotionDef& other) const
		{
			return (value - other.value).getLenght();
		}

		float getIntensitivity() const
		{
			return value.getLenght();
		}
		Angle getColor() const
		{
			return value.angle();
		}




		/// emotion intensitivity manipulations
		
		EmotionDef operator*(float s) const
		{
			return EmotionDef(value*s);
		}
		EmotionDef operator/(float s) const
		{
			assert(s != 0);
			return EmotionDef(value/s);
		}
		void operator*=(float s)
		{
			value *= s;
		}
		void operator/=(float s)
		{
			assert(s != 0);
			value /= s;
		}

		EmotionDef operator+(const EmotionDef& other) const
		{
			return EmotionDef(other.value + value);
		}
		EmotionDef operator-(const EmotionDef& other) const
		{
			return EmotionDef(other.value - value);
		}
		void operator+=(const EmotionDef& other)
		{
			value += other.value;
		}
		void operator-=(const EmotionDef& other)
		{
			value -= other.value;
		}

	private:
		/// position on Plutnichik's circle of emotions
		/// there are 4 pairs (refered to as color in comments)
		///		happiness - sadness		(0;180 degree)
		///		trust - disgust			(45;225 degree)
		///		fear - anger			(90;270 degree)
		///		surprise - anticipation	(135;315 degree)
		/// in that order they are placed in Polar cooridnates
		Vector2D value;

	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};
		
}
