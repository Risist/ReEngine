#include "Camera.h"

Camera cam;

Camera::Camera() : lastScale(1), darkness(1), alpha(1)
{
}
void Camera::create(const sf::Vector2f& size, const sf::Vector2f& center)
{
	reset(sf::FloatRect(size, size));

	RenderTexture::create((unsigned int)size.x, (unsigned int)size.y);

	setCenter(center);
}

void Camera::draw(const sf::Drawable & s, const RenderStates & states)
{
	RenderTexture::draw(s,states);
}

void Camera::display(sf::RenderWindow& wnd, const RenderStates& states)
{
	RenderTexture::display();
	RenderTexture::setView(*this);

	sf::Sprite sprite(RenderTexture::getTexture());
	sprite.setColor(sf::Color(
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * alpha)));

	wnd.draw(sprite,states);
	RenderTexture::clear(background);
}