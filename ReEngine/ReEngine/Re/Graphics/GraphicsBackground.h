#pragma once
#include <Re\Common\utility.h>

namespace Graphics
{
	/// simplified class to display many sprites together
	/// indended to use in Game::State
	class Background : public sf::Drawable
	{
	public:
		void addSprite(sf::Sprite sp)
		{
			sprites.push_back(sp);
		}

		vector<sf::Sprite> sprites;
	protected:
		virtual void draw(sf::RenderTarget& target, RenderStates states) const  override;
	};

}