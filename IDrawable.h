#pragma once
#include <vector>
#include <initializer_list>
#include "raylib.h"
class IBase {
protected:
	Vector2 position; // pozycja od 0 do 1, względem elementu w którym sie znajduje
	Vector2 size; // rozmiar od 0 do 1, no podobnie jak wyżej
	Vector2 offset;
public:
	IBase(Vector2 pos, Vector2 size) : position(pos), size(size), offset({0.f,0.f}) {};

	void setPos(Vector2 newPos) { position = newPos; }
	void setSize(Vector2 newSize) { this->size = newSize; }
	void setOffset(Vector2 newOffset) { offset = newOffset; }
};

class IDrawable : public IBase
{
protected:
	IDrawable* parent;
	// funkcje do rysowania
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
#include <iostream>
class IContainer : public IDrawable
{
	std::vector<IDrawable*> children;
public:
	template<typename... Ts>
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

	void addChild(IDrawable* kid) { children.push_back(kid); kid->registerParent(this); }
};