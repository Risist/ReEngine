#pragma once

#include <Re/Game/Effect/Physics/EffectRigidbody.h>

namespace Effect
{


	/// fixture effects holds ptr to box2D fixture
	/// receives from it event about collisions
	/// and propagates to his childrens
	///	@parent Rigidbody	
	///
	/// @note only Rigidbody can be parent for Fixture
	/// @note collision events are called only for childs of rigidbody and fixtures
	class Fixture final : public Composite
	{
		SERIALISATION_NAME(Fixture)
	public:

		/// default constructor -> does not create fixture
		Fixture();
		virtual ~Fixture();

	public:

		Fixture* createFixture(const CircleColliderDef& def) { return createFixture(&def.fixDef); }
		Fixture* createFixture(const PolygonColliderDef& def) { return createFixture(&def.fixDef); }
		Fixture* createFixture(const ChainColliderDef& def) { return createFixture(&def.fixDef); }
		/// creates fixture from manually provided definition
		Fixture* createFixture(const b2FixtureDef* def);

		void destroyFixture();

		b2Fixture* getFixture() const { return fixture; }

	public: /// events

		virtual bool canBeParent(Base* potentialParent) const override { return dynamic_cast<Rigidbody*>(potentialParent); }

		virtual void onDeconstructionFixture(b2Fixture* fixture) override;

		/// WIP

	/*public: /// shadows
		/// is this fixture alowed to cast shadows?
		Fixture* setCastShadows(bool b)
		{
			castShadows = b;
			return this;
		}

		/// is this fixture alowed to cast shadows?
		/// to cast shadows fixture has to be creted
		///		and cant be a sensor
		bool castsShadows() const
		{
			return fixture && !fixture->IsSensor() && castsShadows;
		}

		sf::ConvexShape createShadow(Vector2D lightPosition, Color lightColor) const
		{

		}*/

	private:
		b2Fixture* fixture;

		//bool castShadows	: 1;
	protected:
		//virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		//virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader)override;
	};
}