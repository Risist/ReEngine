#include <Re\Game\Effect\Graphical\EffectModel.h>
#include <Re\Game\GameActor.h>

namespace Effect
{
	Model::Model(const char* path)
	{
		rootModel.deserialise(path);

		rootModel.rewriteTo_Rendering(modelsRendering);
		rootModel.rewriteTo_Dfs(modelsUpdate);
	}

	Model::Model(ResId scriptId)
	{
		rootModel.deserialiseFromString(scriptInst[scriptId]);

		rootModel.rewriteTo_Rendering(modelsRendering);
		rootModel.rewriteTo_Dfs(modelsUpdate);
	}

	void Model::onInit()
	{
		Super::onInit();
		setModelParent((Effect::Transformable*)getParent());
	}

	void Model::onUpdate(sf::Time dt)
	{
		Super::onUpdate(dt);

		for (auto&it : modelsUpdate)
			it->onUpdate();
	}

	void Model::onDisplay()
	{
		//Super::onDisplay();
		
		for (auto&it : modelsRendering)
			it->onDraw(cam,sf::RenderStates::Default);
	}
}