#include <Re\Game\Effect\Graphical\EffectAnimationManager.h>
#include <Re\Game\Effect\Graphical\EffectModel.h>

#include <Re\Game\GameActor.h>


namespace Effect
{

	AnimationManager::AnimationManager(vector<Graphics::ModelPart*>* modelsUpdate)
	{
		attachToModel(modelsUpdate);
	}
	AnimationManager::AnimationManager(Effect::Model& model)
	{
		attachToModel(model);
	}

	bool AnimationManager::canBeParent(Base * potentialParent) const
	{
		return dynamic_cast<Game::Actor*>(potentialParent);
	}
	void AnimationManager::onInit()
	{
		Super::onInit();
	}
	void AnimationManager::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);
		for (auto it = controllers.begin(); it < controllers.end(); ++it)
		{
			(*it)->onUpdate();
		}
	}

	AnimationManager * AnimationManager::attachToModel(vector<Graphics::ModelPart*>* _modelsUpdate)
	{
		modelsUpdate = _modelsUpdate;
		for (auto it = controllers.begin(); it != controllers.end(); ++it)
			it->get()->attachToModel(*modelsUpdate);
		return this;
	}
}