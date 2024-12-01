#include "IDrawable.h"

Vector2 IDrawable::getParentSize() const
{
	if (parent != nullptr) { // rozmiar elementu macierzystego
		Rectangle pBounding = parent->getBoundingBox();
		return { pBounding.width, pBounding.height };
	}
	return { // a jak brak no to ekranu
		static_cast<float>(GetScreenWidth()),
		static_cast<float>(GetScreenHeight())
	};
}

Vector2 IDrawable::getParentPos() const
{
	if (parent == nullptr) return { 0, 0 };
	return parent->getDrawPos();
}
#include <iostream>
// Wartości zwracane - w pikselach.
Rectangle IDrawable::getBoundingBox() const
{
	Vector2 dPos = getDrawPos();
	Vector2 ourSize = getSizePixels();
	// Minimum.
	if (constraints.first.x != -1 && constraints.first.y != -1 ) {
		ourSize.x = std::max(ourSize.x, constraints.first.x);
		ourSize.y = std::max(ourSize.y, constraints.first.y);
	}
	// Maksimum.
	if (constraints.second.x != -1 && constraints.second.y != -1) {
		ourSize.x = std::min(ourSize.x, constraints.second.x);
		ourSize.y = std::min(ourSize.y, constraints.second.y);
	}
	return { 
		dPos.x, 
		dPos.y, 
		ourSize.x,
		ourSize.y
	};
}

Vector2 IDrawable::getDrawPos() const
{
	Vector2 pPos = getParentPos();
	Vector2 pSize = getParentSize();
	return {
		pPos.x + (position.x + size.x * offset.x) * pSize.x,
		pPos.y + (position.y + size.y * offset.y) * pSize.y
	};
}

Vector2 IDrawable::getSizePixels() const
{
	Vector2 pSize = getParentSize();
	if (drawFlags & DRAWABLE_MAINTAIN_ASPECT_RATIO) {
		float aspectRatio = size.x / size.y;
		float parentRatio = pSize.x / pSize.y;
		float baseScreenRatio = static_cast<float>(OknoSzerBaz) / static_cast<float>(OknoWysBaz);
		// TODO.

		float ourHeight = size.y * pSize.y;
		float requiredWidth = ourHeight / (aspectRatio);

		return {
			requiredWidth / baseScreenRatio,
			ourHeight
		};
	}

	return {
		size.x * pSize.x,
		size.y * pSize.y
	};
}
