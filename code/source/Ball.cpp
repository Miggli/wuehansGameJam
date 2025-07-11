#include "Ball.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include <iostream>
#include <cstdlib>
using namespace Halib;

Ball::Ball() : Entity(Sprite(GRAPHIC_PATH, VecI2(1, 1)), Vec3(200, 120, 0)){
	
	direction = CalculateRandomDir();
}

void Ball::Update(float deltaTime) {
	AddPosition(Halib::Vec3(direction.x, direction.y,0.0f) * deltaTime * speed);

}

Halib::Vec2 Ball::CalculateRandomDir() {
	

	int randomValueX = (rand() % 101);
	randomValueX -= 50;
	float randomFloatX = (float)randomValueX / 100.0f;

	int randomValueY = (rand() % 101);
	randomValueY -= 50;
	float randomFloatY = (float)randomValueY / 100.0f;

	if (randomFloatX == 0 && randomFloatY == 0) return Halib::Vec2(1.0f, 0.0f);
	Halib::Vec2 vector = Halib::Normalize(Halib::Vec2(randomFloatX, randomFloatY));

	std::cout << "calculating random dir for ball: " << vector.x << "   " << vector.y << std::endl;
	
	
	return vector;
}

Halib::Vec2 Ball::GetMiddlePoint() {


	return Vec2(GetPosition()) + Vec2(sprite.GetFrameSize()) * 0.5f;
}

Halib::Vec2 Ball::GetDirection() {
	return direction;
}

void Ball::SetDirection(Halib::Vec2 dir) {
	direction = Halib::Normalize(dir);
}

void Ball::IncreaseSpeed(float increase) {
	float maxSpeed = 200.0f;
	float newSpeed;
	newSpeed = speed + increase;
	if (newSpeed >= maxSpeed) newSpeed = maxSpeed;

	speed = newSpeed;
}

float Ball::GetSpeed() {
	return speed;
}