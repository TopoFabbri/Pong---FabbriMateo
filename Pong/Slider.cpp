#include "Slider.h"

void Slider::drawSlider(Slider slider)
{
	slider.handle.center = { slider.pos.x + slider.value, slider.pos.y + slider.thickness / 2 };

	DrawRectangle((int)slider.handle.center.x, (int)slider.pos.y, (int)(slider.length - slider.handle.center.x), (int)slider.thickness, slider.barColor);
	DrawRectangle((int)slider.pos.x, (int)slider.pos.y, (int)(slider.handle.center.x - slider.pos.x), (int)slider.thickness, slider.fillColor);

	drawCircleCir(slider.handle, slider.handleColor);
}

void Slider::updateHandle(Slider& slider)
{
	if (!slider.handlePressed &&
		IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
		CheckCollisionPointCircle(GetMousePosition(), slider.handle.center, slider.handle.radius))
	{
		slider.handlePressed = true;
	}
	else if (!slider.handlePressed && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		slider.handlePressed = false;
	}

	if (slider.handlePressed)
		slider.handle.center.x = (float)GetMouseX();
}