#include "Kicker.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include <iostream>
using namespace Halib;

Kicker::Kicker(Halib::Vec3 position, Halib::Button button) : Entity(Sprite(GRAPHIC_PATH, VecI2(4, 1)), position) {
	SetPosition(Vec3(position.x - sprite.GetFrameSize().x * 0.5f, position.y - sprite.GetFrameSize().y * 0.5f,position.z));
	
}

void Kicker::Update(float deltaTime) {
	
	
	if (isOnCooldown) coolDownTimer += deltaTime;
	if (coolDownTimer >= coolDown) {
		isOnCooldown = false;
		coolDownTimer = 0.0f;
		sprite.frameIndex += VecI2(-1, 0);
	}
	
}
void Kicker::PutOnCooldown() {

	sprite.frameIndex += VecI2(1, 0);
	isOnCooldown = true;
}

bool Kicker::IsOnCooldown() {
	return isOnCooldown;
}


std::pair<bool,float> Kicker::CanReflectBall(Directions kickerDir, float boundValue, Vec2 ballPos) {
	
	
	
	float distance = 100000;
	bool canReflect = false;

	switch (kickerDir) {
	case top:
		distance = abs(ballPos.y - boundValue);
		break;
	
	case right:
		distance = abs(ballPos.x - boundValue);
		break;

	case bottom:
		distance = abs(ballPos.y - boundValue);
		break;
	case left:
		distance = abs(ballPos.x - boundValue);
		break;

	}

	
	float distancefactor = 1.0f - distance / allowedDistance;
	bool isInRange = false;
	if (distance <= allowedDistance && !isOnCooldown) isInRange = true;
	std::pair<bool, float> myPair(isInRange, distancefactor);

	return myPair;
	
}