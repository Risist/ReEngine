#include <Re\Game\Effect\Graphical\EffectFollowCamera.h>
#include <Re\Graphics\Camera.h>
#include <Re\Game\GameActor.h>

namespace Effect
{
	FollowCamera::FollowCamera()
	{
	}

	bool FollowCamera::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Transformable*>(potentialParent);
	}

	void FollowCamera::onInit()
	{
		Super::onInit();
		updateTarget = (Effect::Transformable*)getParent();
	}

	void FollowCamera::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);

		assert(updateTarget);

		cam.setCenter(
			lerp(
				cam.getCenter(), 
				(Vector2D)updateTarget->getTransform().transformPoint(offset), 
				smoothness.x
			)
		);

		Angle desredRot = Degree(updateTarget->getRotation()) + addictionalRotation;
		cam.setRotation( 
				lerp(
					cam.getRotation(),
					desredRot,
					smoothness.y
				)
		);

	}

	/*void FollowCamera::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);
		

		saver.save<float32>("smoothnessPosition", smoothness.x, 0.f);
		saver.save<float32>("smoothnessRotation", smoothness.y, 0.f);

		saver.save<float32>("offsetX", offset.x, 0.f);
		saver.save<float32>("offsetY", offset.y, 0.f);

		saver.save<float32>("rotation", addictionalRotation.asDegree() , 0.f);
	}

	void FollowCamera::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);
		
		smoothness = {
			loader.load<float32>("smoothnessPosition", 0.f),
			loader.load<float32>("smoothnessRotation", 0.f)
		};
		offset = {
			loader.load<float32>("offsetX", 0.f),
			loader.load<float32>("offsetY", 0.f)
		};
		addictionalRotation = Degree(loader.load<float32>("rotation", 0.f));
	}*/

}