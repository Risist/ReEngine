#pragma once
#include <Re\Graphics\Model\GraphicsModelDef.h>
#include <Re\Graphics\Model\GraphicsAnimationStep.h>

namespace Graphics
{
	class ModelPart;

	class AnimationPart :
		public AnimationStepHolder,
		public Res::ISerialisable
	{
	public:

		/// desired model state at certain animation step
		/// state between keystones is interpolated
		struct KeyStone
		{
			ModelDef desiredDef;
			Step_t step;
			bool operator< (const KeyStone& other) const { return step < other.step; }
			bool operator> (const KeyStone& other) const { return step > other.step; }
		};

		/// applies animation offset to the model
		void onUpdate();

		ModelDef getDefAtStep(Step_t step) const;

		void attachToModel(ModelPart* part) { maintainedModel = part; }
		
		KeyStone getKeyStone(size_t id) const { return keystones[id]; }
		size_t getKeyStoneCount() const { return keystones.size(); }

	private:
		/// container of Keystones sorted by step
		vector<KeyStone> keystones;

		/// model part which the animaion part will edit while update
		ModelPart *maintainedModel{ nullptr };

		size_t modelId{0};

		friend class AnimationController;
	protected:
		/// adds new keystone
		void addKeyStone(ModelDef def, Step_t step){keystones.push_back({def, step});}

		/// call this when al the keystones are added
		/// sorts them by step;
		void finaliseKeystones();
		
		virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
		virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
	};

}