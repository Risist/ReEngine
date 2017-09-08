#pragma once
#include <Re\Common\utility.h>
#include <initializer_list>

/*
This file contains physics definitions for entities like Rigidbody, Fixture or shapes

Although box2d has everything you need to create bodies/fixtures/shapes
syntax is not so handy

The classes defines many fucntion which are designed to be used in chain calls
(like std::cin or cout)
here is an example:


rigidbody->createRigidbody( RigidbodyDef()
	.setLinearDamping(1.f)
	.setAngularDamping(1.f)
	.setBullet(true)
);

*/

/// TODO add serialisation to def types
namespace Effect
{
	class Rigidbody;
	class Fixture;

	/*
	simplified syntax for b2BodyDef creation
	position, angle and user data is setted up by Effect::Rigidbody::createRigidbody() function
	*/
	class RigidbodyDef
	{
	public:

		RigidbodyDef& setType( b2BodyType type)
		{
			def.type = type;
			return *this;
		}
		RigidbodyDef& setLinearDamping(float32 s)
		{
			def.linearDamping = s;
			return *this;
		}
		RigidbodyDef& setAngularDamping(float32 s)
		{
			def.angularDamping = s;
			return *this;
		}
		RigidbodyDef& setAllowSleep(bool b)
		{
			def.allowSleep = b;
			return *this;
		}
		RigidbodyDef& setBullet(bool b)
		{
			def.bullet = b;
			return *this;
		}
		RigidbodyDef& setAwake(bool b)
		{
			def.awake = b;
			return *this;
		}
		RigidbodyDef& setFixedRotation(bool b)
		{
			def.fixedRotation = b;
			return *this;
		}
		RigidbodyDef& setAngularVelocity(Angle s)
		{
			def.angularDamping = s.asRadian();
			return *this;
		}
		RigidbodyDef& setAngularVelocity(Vector2D s)
		{
			def.linearVelocity = (b2Vec2)(s*toB2Position);
			return *this;
		}

	private:
		b2BodyDef def;
		friend class Rigidbody;
	};

	/*
	Simplified syntax for Fixture + CircleShape creation
	user data is setted up by Effect::Fixture::createFixture() function
	*/
	class CircleColliderDef
	{
	public:
		CircleColliderDef()
		{
			fixDef.shape = &sh;
			setDensity(1.0f);
		}

		CircleColliderDef& setFriction(float32 friction)
		{
			fixDef.friction = friction;
			return *this;
		}
		CircleColliderDef& setRestitution(float32 restitution)
		{
			fixDef.restitution = restitution;
			return *this;
		}
		CircleColliderDef& setDensity(float32 density)
		{
			fixDef.density = density*toB2Position;
			return *this;
		}
		CircleColliderDef& setSensor(bool b)
		{
			fixDef.isSensor = b;
			return *this;
		}
		CircleColliderDef& setFriction(b2Filter filter)
		{
			fixDef.filter = filter;
			return *this;
		}
		CircleColliderDef& setOffset(Vector2D offset)
		{
			sh.m_p = offset *toB2Position;
			return *this;
		}
		CircleColliderDef& setRadius(float32 radius)
		{
			sh.m_radius = radius* toB2Position;
			return *this;
		}

	private:
		b2FixtureDef fixDef;
		b2CircleShape sh;
		friend class Fixture;
	};

	/*
	Simplified syntax for Fixture + PolygonShape creation
	user data is setted up by Effect::Fixture::createFixture() function
	*/
	class PolygonColliderDef
	{
	public:
		PolygonColliderDef()
		{
			fixDef.shape = &sh;
			setDensity(1.0f);
		}

		PolygonColliderDef& setFriction(float32 friction)
		{
			fixDef.friction = friction;
			return *this;
		}
		PolygonColliderDef& setRestitution(float32 restitution)
		{
			fixDef.restitution = restitution;
			return *this;
		}
		PolygonColliderDef& setDensity(float32 density)
		{
			fixDef.density = density*toB2Position;
			return *this;
		}
		PolygonColliderDef& setSensor(bool b)
		{
			fixDef.isSensor = b;
			return *this;
		}
		PolygonColliderDef& setFriction(b2Filter filter)
		{
			fixDef.filter = filter;
			return *this;
		}

		PolygonColliderDef& setAsBox( Vector2D wh)
		{
			sh.SetAsBox(wh.x *toB2Position, wh.y*toB2Position);
			return *this;
		}
		PolygonColliderDef& setAsBox(Vector2D wh, Vector2D center, Angle angle)
		{
			sh.SetAsBox(wh.x *toB2Position, wh.y*toB2Position, center*toB2Position, angle.asRadian() );
			return *this;
		}
		PolygonColliderDef& setVertexes(const std::initializer_list<Vector2D>& vertexes)
		{
			vector<b2Vec2> v;
			v.reserve(vertexes.size());
			for(auto it: vertexes)
				v.push_back(it*toB2Position);
			sh.Set(v.data(), v.size());
			return *this;
		}
		

	private:
		b2FixtureDef fixDef;
		b2PolygonShape sh;
		friend class Fixture;
	};


	/*
	Simplified syntax for Fixture + ChainShape creation
	user data is setted up by Effect::Fixture::createFixture() function
	*/
	class ChainColliderDef
	{
	public:
		ChainColliderDef()
		{
			fixDef.shape = &sh;
			setDensity(1.0f);
		}

		ChainColliderDef& setFriction(float32 friction)
		{
			fixDef.friction = friction;
			return *this;
		}
		ChainColliderDef& setRestitution(float32 restitution)
		{
			fixDef.restitution = restitution;
			return *this;
		}
		ChainColliderDef& setDensity(float32 density)
		{
			fixDef.density = density*toB2Position;
			return *this;
		}
		ChainColliderDef& setSensor(bool b)
		{
			fixDef.isSensor = b;
			return *this;
		}
		ChainColliderDef& setFriction(b2Filter filter)
		{
			fixDef.filter = filter;
			return *this;
		}

		ChainColliderDef& setVertexes(const std::initializer_list<Vector2D>& vertexes)
		{
			vector<b2Vec2> v;
			v.reserve(vertexes.size());
			for (auto it : vertexes)
				v.push_back(it*toB2Position);
			sh.CreateChain(v.data(), v.size());
			return *this;
		}

		ChainColliderDef& setNextVertex(Vector2D vertex)
		{
			sh.SetNextVertex(vertex * toB2Position);
			return *this;
		}
		ChainColliderDef& setPreviousVertex(Vector2D vertex)
		{
			sh.SetPrevVertex(vertex * toB2Position);
			return *this;
		}
		ChainColliderDef& setLoop()
		{
			sh.CreateLoop(sh.m_vertices, sh.m_count);
			return *this;
		}


	private:
		b2FixtureDef fixDef;
		b2ChainShape sh;
		friend class Fixture;
	};
}