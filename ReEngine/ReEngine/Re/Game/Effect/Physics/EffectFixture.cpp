#include <Re\Game\Effect\Physics\EffectFixture.h>
#include <Re\Game\GameActor.h>

namespace Effect
{
	


	Fixture::Fixture()
	{
	}

	Fixture::~Fixture()
	{
		destroyFixture();
	}

	Fixture * Fixture::createFixture(const b2FixtureDef * def)
	{
		Rigidbody* parent = (Rigidbody*)getParent();
		fixture = parent->getRigidbody()->CreateFixture(def);
		fixture->SetUserData(this);
		return this;
	}

	void Fixture::destroyFixture()
	{
		Rigidbody* parent = (Rigidbody*)getParent();
		assert(parent);
		if (parent->getRigidbody() && fixture)
		{
			fixture->SetUserData(nullptr);
			parent->getRigidbody()->DestroyFixture(fixture);
		}
		fixture = nullptr;
	}

	void Fixture::onDeconstructionFixture(b2Fixture * _fixture)
	{
		fixture = nullptr;
		Super::onDeconstructionFixture(_fixture);
	}

	/*void Fixture::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save<ResId>("fixtureDefId", fixtureDefId, 0);
		saver.save<ResId>("shapeId", shapeId, 0);
		
		if (fixture)
		{
			//if (fixture->GetType() == b2Shape::e_circle )
				//saver.save<string>("shapeType", "circle");
			// else 
			if (fixture->GetType() == b2Shape::e_polygon)
				saver.save<string>("shapeType", "polygon");
			else if (fixture->GetType() == b2Shape::e_chain)
				saver.save<string>("shapeType", "chain");
		}
		
		Super::serialiseF(file, saver);;
	}

	void Fixture::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		fixtureDefId = loader.load<ResId>("fixtureDefId", 0);
		shapeId = loader.load<ResId>("shapeId", 0);
		std::string shapeType = loader.load<string>("shapeType", "circle");
		b2Shape::Type type;
		if (shapeType == "circle")
			type = b2Shape::e_circle;
		else if (shapeType == "polygon")
			type = b2Shape::e_polygon;
		else if (shapeType == "chain")
			type = b2Shape::e_chain;
		else
			cerr << "\"" << shapeType << "\" is not a valid shape type" << endl;

		createFixture(fixtureDefId, shapeId, type);

		Super::deserialiseF(file, loader);
	}*/

}