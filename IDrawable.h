#pragma once
#include <vector>
#include "raylib.h"
#include "Grafika.h"

#define NO_MIN {-1, -1}
#define NO_MAX {-1, -1}

class IBase {
protected:
	Vector2 position; // pozycja od 0 do 1, względem elementu w którym sie znajduje
	Vector2 size; // rozmiar od 0 do 1, no podobnie jak wyżej
	Vector2 offset;
	// { min, max }
	std::pair<Vector2, Vector2> constraints;
public:
	IBase(Vector2 pos, Vector2 size) : position(pos), size(size), offset({0.f,0.f}) {
		constraints = { NO_MIN, NO_MAX };
	};

	void setPos(Vector2 newPos) { position = newPos; }
	void setSize(Vector2 newSize) { this->size = newSize; }
	void setMinSize(Vector2 newMin) { this->constraints.first = newMin; }
	void setMaxSize(Vector2 newMax) { this->constraints.second = newMax; }
	void setConstraints(Vector2 min, Vector2 max) { setMinSize(min); setMaxSize(max); }

	// Ustawia rozmiar względem bazowego rozmiaru okna.
	// setSizeRelative(500, 560) -> przy rozmiarze bazowym
	// będzie rozmiar tak by było 500 na 560 pikseli. Skaluje sie jakoś.
	virtual void setSizeRelative(float x, float y)  {
		this->size = {
			(x / OknoSzerBaz),
			(y / OknoWysBaz)
		};
	}
	void setOffset(Vector2 newOffset) { offset = newOffset; }
};

class IDrawable : public IBase
{
protected:
	IDrawable* parent;
	// funkcje do rysowania
	Vector2 getParentPos() const;
	Vector2 getParentSize() const;
	Rectangle getBoundingBox() const;
	Vector2 getDrawPos() const;
public:
	// Nadpisać swoim kodem:
	virtual void update() = 0; // Update, przed rysowaniem.
	virtual void draw() const = 0; // Logika sterująca rysowaniem

	IDrawable(Vector2 pos, Vector2 size) : IBase(pos, size), parent(nullptr) {};

	void registerParent(IDrawable* who) {
		parent = who;
	};

	IDrawable* getParent() { return parent; }
};

class IContainer : public IDrawable
{
	std::vector<IDrawable*> children;
public:
	IContainer(Vector2 pos, Vector2 size) : IDrawable(pos, size) {};

	virtual void update() {
		for (auto* kid : children) {
			kid->update();
		}
	}

	virtual void draw() const {
		for (auto* kid : children) {
			kid->draw();
		}
	}
	// upewnijcie sie, że dodajecie tylko rzeczy które da się rysować (IDrawable)
	template <typename... Drawables>
	void addChildren(Drawables... kids) {
		for (auto k : { kids... }) {
			addChild(k);
		}
	}
	void addChild(IDrawable* kid = nullptr) {
		if (kid == nullptr) return;
		children.push_back(kid); 
		kid->registerParent(this); 
	}
};