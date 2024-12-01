#pragma once
#include "IDrawable.h"
class testRect : public IContainer {
	typedef IContainer super;
	Color color;
public:
	void draw() const override {
		Rectangle b = getBoundingBox();
		DrawRectangleRec(getBoundingBox(), color);
		super::draw();
	}
	void update() override { super::update(); };
	testRect(Vector2 pos, Vector2 size, Color color) : IContainer(pos, size), color(color) {};
};