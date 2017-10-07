#include "Transform.h"

Math::Transform::Transform()
	:needToUpdateTransform(true), scale(1,1)
{
}

void Math::Transform::updateTransform() const
{
	if (needToUpdateTransform)
	{
		float cosine = rotation.cos();
		float sine = rotation.sin();
		float sxc = scale.x * cosine;
		float syc = scale.y * cosine;
		float sxs = scale.x * sine;
		float sys = scale.y * sine;
		float tx = /*-origin.x * sxc - origin.y * sys +*/ position.x;
		float ty = /*origin.x * sxs - origin.y * syc +*/ position.y;

		transform = sf::Transform
		(
			sxc, sys, tx,
			-sxs, syc, ty,
			0.f, 0.f, 1.f
		);
		needToUpdateTransform = false;
	}
}
