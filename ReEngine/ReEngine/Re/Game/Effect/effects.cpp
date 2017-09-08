#include <Re\Game\Effect\effects.h>



namespace Effect
{
	/// define function which will be used for serialisation of all standard efects
	MULTI_SERIALISATION_INTERFACE_IMPL(Base)
	{
		/// physics
		MULTI_SERIALISATION_INTERFACE_CHECK(Rigidbody);
		else MULTI_SERIALISATION_INTERFACE_CHECK(Fixture);

		/// audio
		else MULTI_SERIALISATION_INTERFACE_CHECK(AudioSource);
		else MULTI_SERIALISATION_INTERFACE_CHECK(AudioListener);

		/// graphics
		MULTI_SERIALISATION_INTERFACE_CHECK(FollowCamera);
		MULTI_SERIALISATION_INTERFACE_CHECK(Model);
		MULTI_SERIALISATION_INTERFACE_CHECK(AnimationManager);
		
		/// health
		MULTI_SERIALISATION_INTERFACE_CHECK(Health);
		MULTI_SERIALISATION_INTERFACE_CHECK(DamageOnCollision);
		///MULTI_SERIALISATION_INTERFACE_CHECK(SpawnOnDeath); /// TODO: loading prototype from string name
		MULTI_SERIALISATION_INTERFACE_CHECK(RespawnAfterAWhile);
		MULTI_SERIALISATION_INTERFACE_CHECK(DieAfterAWhile);
		MULTI_SERIALISATION_INTERFACE_CHECK(DieOnCollision);

		/// movement
		MULTI_SERIALISATION_INTERFACE_CHECK(Motor);
		MULTI_SERIALISATION_INTERFACE_CHECK(MovementAim);
		/// /// Player
		MULTI_SERIALISATION_INTERFACE_CHECK(MouseMovement);


		return nullptr;
	}
}