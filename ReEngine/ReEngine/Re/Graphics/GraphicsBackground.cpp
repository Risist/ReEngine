#include <Re\Graphics\GraphicsBackground.h>

namespace Graphics
{
	void Background::draw(sf::RenderTarget & target, RenderStates states) const
	{
		for (auto& it : sprites)
			target.draw(it, states);
	}
}