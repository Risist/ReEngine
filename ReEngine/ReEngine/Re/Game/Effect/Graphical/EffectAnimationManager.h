#pragma once
#include <Re\Game\Effect\EffectBase.h>
#include <Re\Game\Effect\Graphical\EffectModel.h>
#include <Re\Graphics\Model\GraphicsAnimationController.h>
#include <Re\Graphics\ResourceManager.h>

namespace Effect
{
	/// class to maintain animations
	/// since animation need to be updated separately from models
	/// this component is able does the job
	///
	class AnimationManager : public Base
	{
		SERIALISATION_NAME(AnimationManager)
	public:
		/// creates animation manager attached to specific model
		AnimationManager(vector<Graphics::ModelPart*>* modelsUpdate = nullptr);
		AnimationManager(Effect::Model& model);

		////// events
		virtual bool canBeParent(Base* potentialParent) const override;

		virtual void onInit() override;
		virtual void onUpdate(sf::Time dt) override;



		////// setters
		Graphics::AnimationController* insertAnimation(ResId animationScriptId)
		{
			controllers.push_back(make_unique<Graphics::AnimationController>());
			controllers.back()->deserialiseFromString(scriptInst[animationScriptId]);
			controllers.back()->attachToModel(*modelsUpdate);
			return controllers.back().get();
		}
		Graphics::AnimationController* insertAnimation(const char* path)
		{
			controllers.push_back(make_unique<Graphics::AnimationController>());
			controllers.back()->deserialise(path);
			controllers.back()->attachToModel(*modelsUpdate);	
			return controllers.back().get();
		}
		AnimationManager* applyPose(ResId animationScriptId) 
		{
			Graphics::AnimationController controller;
			controller.deserialiseFromString(scriptInst[animationScriptId]);
			controller.attachToModel(*modelsUpdate);
			controller.applyPose();
			return this;
		}
		AnimationManager* applyPose(const char* path)
		{
			Graphics::AnimationController controller;
			controller.deserialise(path);
			controller.attachToModel(*modelsUpdate);
			controller.applyPose();
			return this;
		}


		AnimationManager* removeAnimation(size_t id)
		{
			assert(controllers.size() > id);
			controllers.erase(controllers.begin() + id);

			return this;
		}
		AnimationManager* removeAnimation(Graphics::AnimationController* anim)
		{
			for (auto it = controllers.begin(); it != controllers.end(); ++it)
				if (it->get() == anim)
				{
					controllers.erase(it);
					break;
				}
			return this;
		}


		AnimationManager* attachToModel(vector<Graphics::ModelPart*>* _modelsUpdate);
		AnimationManager* attachToModel(Effect::Model& model)
		{
			attachToModel(&model.modelsUpdate);
			return this;
		}

		Graphics::AnimationController& getAnimation(size_t id)
		{
			assert(controllers.size() > id);
			return *controllers[id];
		}
		Graphics::AnimationController& getAnimation()
		{
			return *controllers.back();
		}
		size_t animationCount() const { return controllers.size(); }

	private:
		/// animations holded and managed in the class
		vector<unique_ptr<Graphics::AnimationController>> controllers;
		
		/// reference to vectorised model conntrollers are attached to
		vector<Graphics::ModelPart*>* modelsUpdate{nullptr};
	};


}