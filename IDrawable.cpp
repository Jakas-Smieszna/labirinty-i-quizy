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

// Wartości zwracane - w pikselach.
Rectangle IDrawable::getBoundingBox() const
{
	Vector2 pSize = getParentSize();
	Vector2 dPos = getDrawPos();
	Vector2 ourSize = {
		size.x * pSize.x,
		size.y * pSize.y
	};
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
