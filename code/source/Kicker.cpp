#include "Kicker.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include <iostream>
using namespace Halib;

Kicker::Kicker(Halib::Vec3 position, Halib::Button button) : Entity(Sprite(GRAPHIC_PATH, VecI2(1, 1)), position) {
	SetPosition(position - sprite.GetFrameSize().x * 0.5f);
	buttonToUse = button;
}

void Kicker::Update(float deltaTime) {
	
	if (!isOnCooldown && Halib::GetButtonDown(0, buttonToUse)) {
		
		isPressed = true;
		isOnCooldown = true;

	}
	if (isPressed) {

		if (hasBeenPressedTimer >= leeWayTime) {
			isPressed = false;
			hasBeenPressedTimer = 0.0f;
			
		}
		else hasBeenPressedTimer += deltaTime;
	}

	if (isOnCooldown) {

		if (coolDownTimer >= coolDown) {
			isOnCooldown = false;
			coolDownTimer = 0.0f;

		}
		else coolDownTimer += deltaTime;	
	}

	
}
bool Kicker::HasBeenPressedInTime() {
	return isPressed;
}
float Kicker::GetPerfectTimingFactor() {
	if (hasBeenPressedTimer == 0) return 0.1;
	else return leeWayTime / hasBeenPressedTimer;
	
}
void Kicker::ResetPress() {
	hasBeenPressedTimer = 0.0f;
	isPressed = false;
}