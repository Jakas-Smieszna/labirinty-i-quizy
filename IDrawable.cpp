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

// Wartości zwracane - w pikselach.
Rectangle IDrawable::getBoundingBox() const
{
	Vector2 pSize = getParentSize();
	Vector2 dPos = getDrawPos();
	return { 
		dPos.x, 
		dPos.y, 
		size.x * pSize.x, 
		size.y * pSize.y 
	};
}

Vector2 IDrawable::getDrawPos() const
{
	Vector2 pSize = getParentSize();
	if (parent != nullptr) {
		Vector2 pPos = parent->getDrawPos();
		return {
			pPos.x + position.x * pSize.x,
			pPos.y + position.y * pSize.y
		};
	}
	return {
		position.x * pSize.x,
		position.y * pSize.y
	};
}
