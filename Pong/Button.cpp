#include "Button.h"

void drawButton(Button& btn)
{
	const Vector2 txtSize = MeasureTextEx(btn.font, btn.text, btn.size, btn.txtSpacing);

	btn.rec.width = txtSize.x + 2 * btn.indent;
	btn.rec.height = txtSize.y;

	const Color printColor = CheckCollisionPointRec(GetMousePosition(), btn.rec) ? btn.hovered : btn.normal;
	DrawRectangleRec(btn.rec, printColor);

	DrawTextEx(btn.font, btn.text, {btn.rec.x + btn.indent, btn.rec.y}, btn.size, btn.txtSpacing, btn.txtColor);
}

bool isButtonPressed(Button btn)
{
	return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
		CheckCollisionPointRec(GetMousePosition(), btn.rec));
}