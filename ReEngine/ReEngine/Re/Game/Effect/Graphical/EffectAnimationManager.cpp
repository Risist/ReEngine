#include <Re\Game\Effect\Graphical\EffectAnimationManager.h>
#include <Re\Game\Effect\Graphical\EffectModel.h>

#include <Re\Game\GameActor.h>


namespace Effect
{

	AnimationManager::AnimationManager(vector<Graphics::Model*>* modelsUpdate)
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
			(*it)->onUpdateModel();
		}
	}

	AnimationManager * AnimationManager::attachToModel(vector<Graphics::Model*>* _modelsUpdate)
	{
		modelsUpdate = _modelsUpdate;
		for (auto it = controllers.begin(); it != controllers.end(); ++it)
			it->get()->attachToModel(*modelsUpdate);
		return this;
	}

	/*void AnimationManager::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		Super::serialiseF(file, saver);

		/// TODO
	}

	void AnimationManager::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		Super::deserialiseF(file, loader);

		DATA_SCRIPT_MULTILINE(file, loader)
		{
			ResId resId = loader.load<ResId>("resId", 0);
			if (resId)
			{
				addAnimation(resId);
			}
			else
			{
				std::string path = loader.loadRaw("path", "");
				addAnimation(path.c_str());
			}
		}
	}*/

}