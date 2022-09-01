#include "CheckBox.h"

	void draw(CheckBox check)
	{
		Color fillColor = (check.checked ? check.fill : check.empty);

		DrawRectangle(check.pos.x, check.pos.y, check.size, check.size, check.out);
		DrawRectangle(check.pos.x + 2, check.pos.y + 2, check.size - 4, check.size - 4, fillColor);
	}
