#pragma once
#include "IDrawable.h"

class Panel : public IContainer {
	typedef IContainer super;
	Color borderColor;
	Color bgColor;
protected:
	Color getBorderColor() { return borderColor; }
	Color getBackgroundColor() { return bgColor; }
	void setBorderColor(Color newBoderColor) { borderColor = newBoderColor; }
	void setBackgroundColor(Color newBackgroundColor) { bgColor = newBackgroundColor; }
public:
	Panel(Vector2 pos, Vector2 size = {0,0}) : IContainer(pos, size) {
		borderColor = BLACK;
		bgColor = Fade(WHITE, 0.75);
	}

	void draw() const {
		Rectangle bounding = getBoundingBox();
		DrawRectangleRec(bounding, bgColor);
		DrawRectangleLinesEx(bounding, 1.f, borderColor);
		super::draw();
	}

};