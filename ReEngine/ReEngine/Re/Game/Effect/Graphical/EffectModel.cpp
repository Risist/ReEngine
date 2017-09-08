#include <Re\Game\Effect\Graphical\EffectModel.h>
#include <Re\Game\GameActor.h>

namespace Effect
{
	Model::Model(const char* path)
	{
		model.deserialise(path);

		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
	}

	Model::Model(ResId scriptId)
		:model(scriptId)
	{
		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
	}

	void Model::onInit()
	{
		Super::onInit();
		setModelParent((Transformable*)getParent());
	}

	void Model::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);
		//model.drawRecursive(cam);
		for (auto&it : modelsUpdate)
			it->updateAsParent();
	}

	void Model::onDisplay()
	{
		//Super::onDisplay();
		for (auto&it : modelsRendering)
			it->drawOnly(cam);
	}


	/*void Model::serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const
	{
		if (resId)
		{
			saver.save<ResId>("resId", resId);
		}
		else
		{
			model.serialise(file, saver);
		}
		Super::serialiseF(file, saver);

	}
	void Model::deserialiseF(std::istream& file, Res::DataScriptLoader& loader)
	{
		resId = loader.load<ResId>("resId", 0);
		if (resId)
		{
			model.deserialiseFromString(scriptInst[resId]);
		}
		else
		{
			model.deserialise(file, loader);
		}

		model.rewriteToVectorRendering(modelsRendering);
		model.rewriteToVectorUpdate(modelsUpdate);
		
		Super::deserialiseF(file, loader);
	}*/
}