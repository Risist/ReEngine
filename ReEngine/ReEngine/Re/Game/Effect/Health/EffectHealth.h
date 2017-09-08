#include <Re\Game\Effect\EffectBase.h>

namespace Effect
{
	/*
	health component
		manages health state, 
		gives some callbacks to damage events
		heal,damage function with bleed effect
	@parent Game::Actor only
	*/
	class Health final: public Base
	{
		SERIALISATION_NAME(Health)
	public:
		Health(float32 maxHealth = 100.f, float32 percentInitialHealth = 1.f);


	public: /// events

		virtual bool canBeParent(Base * potentialParent) const override;
		virtual void onUpdate(sf::Time dt) override;

	public:
		/// functions for initialization
		Health*	setDamageReaction(function<void(float32&, Effect::Base*)> s)
		{
			damageReaction = s;
			return this;
		}
		Health* setMax(float32 maxHp, function<void(Effect::Health&)>  _maxReaction = maxReaction_allign)
		{
			max = maxHp;
			maxReaction = _maxReaction;
			return this;
		}
		Health* setRegeneration(float32 _regeneration, float32 _regenerationDamping)
		{
			regeneration = _regeneration;
			regenerationDamping = _regenerationDamping;
			return this;
		}
		Health* setDefence(float32 s)
		{
			assert(s != 0);
			inverseDefence = 1 / s;
			return this;
		}
		Health* setInverseDefence(float32 s)
		{
			inverseDefence = s;
			return this;
		}
		Health* setActual(float32 s)
		{
			actual = s;
			return this;
		}


	public:
		/// what happens to health when it has value above max?
		function<void(Effect::Health& health)> maxReaction{maxReaction_allign};

			/// allign health to max value
		static void maxReaction_allign(Effect::Health& health);

			/// there is no max health cap
		static void maxReaction_nothing(Effect::Health& health, float32 max) {};

	public:
		/// callback for what happeneds after taking damage
		/// @param:damage how much damage the actor is going to take (defense is just applied)
		///		damage is dealed after callback, so you can change the amount
		///	@param:causer	effect which did damage
		///		@note Effect::Base has getActor() function which will give you acces to whole dealing damage
		///		@note Actor has a field instigator -> it is an actor responsible of dealing dmg 
		///			(for examgle player (instigator) and bullet (causer) )
		function<void(float32& damage, Effect::Base* causer)> damageReaction{ [](float32&, Effect::Base*) {} };
	
		/// heal/damage events
		/// both can have negative arguments, which is basically using another function with positive arg
		/// @param:amount	how much damage will be dealed
		///	@param:causer	effect which did damage ( for callback purposes)
		/// @param:bleed	ratio of how much percent of damage will be dealed instantly
		///		and how much will be dealed as a bleed effect ( or regeneration for heal)
		///		0 - whole dmg is treated as a bleed, 1 - whole damage is dealed instantly
		void damage(float32 amount, Effect::Base* causer, float32 bleed = 1.f);
		void heal(float32 amount, Effect::Base* causer, float32 bleed = 1.f);
	public:

		bool isInMaxRange() const { return actual < max; }
		float32 getPercent() const { return actual / max; }


	public:
		float32 regeneration{ 0.f };
		float32 regenerationDamping{ 0.5f };

		float32 actual{0.f};
		float32 max{100.f};
		float32 inverseDefence{ 1.f };

		/*
	protected:
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)override;*/
	};

}