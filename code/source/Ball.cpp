#include "Ball.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include <iostream>
#include <cstdlib>
#include "Bounds.h"
using namespace Halib;

Ball::Ball() : Entity(Sprite(GRAPHIC_PATH, VecI2(1, 1)), Vec3(200, 120, 0)){
	
	speed = baseSpeed;
	direction = CalculateRandomDir();
	failsound = Halib::audiosystem.LoudSound(FAILSOUND_PATH);
}

void Ball::Update(float deltaTime) {
	
	if (!Active) return;
	if (shouldMove) AddPosition(Halib::Vec3(direction.x, direction.y,0.0f) * deltaTime * speed * speedModifier);

	if (isInGracePeriod) HandleGracePeriod();
}

Halib::Vec2 Ball::CalculateRandomDir() {
	
	/*
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
	*/
	if (direction.x == 0 && direction.y == 0) return Vec2(1.0f, 0.0f);
	return direction;
}

void Ball::DisableBallWithGracePeriod() {
	shouldMove = false;
	isInGracePeriod = true;
}
void Ball::ResetGracePeriod() {
	isInGracePeriod = false;
	shouldMove = true;
	graceTimer = 0.0f;
}

void Ball::HandleGracePeriod() {
	if (graceTimer >= gracePeriodTime) {
		isInGracePeriod = false;
		Active = false;
		graceTimer = 0.0f;
		PlayFailSound();
		Bounds::BallHasDied(GetMiddlePoint());
	}

	graceTimer += GetDeltaTime();
}
void Ball::PlayFailSound() {
	Halib::audiosystem.Play(failsound);
}

Halib::Vec2 Ball::GetMiddlePoint() {


	return (Vec2(GetPosition()) + 0.5f* Vec2(sprite.GetFrameSize()));
}

Halib::Vec2 Ball::GetDirection() {
	return direction;
}

void Ball::SetDirection(Halib::Vec2 dir) {
	/*Vec2 newDir = dir;
	{
		//without normalizing
		if (dir.x == 0 && dir.y == 0) direction = newDir;
		return;
	}*/
	direction = Halib::Normalize(dir);
	shouldMove = true;
	
}

void Ball::IncreaseSpeed(float increase) {
	float maxSpeed = 1500.0f;
	float newSpeed;
	newSpeed = speed + increase;
	if (newSpeed >= maxSpeed) newSpeed = maxSpeed;

	speed = newSpeed;
}

float Ball::GetSpeed() {
	return speed;
}

void Ball::ResetBall(int lastPlayerScored) {
	ResetGracePeriod();
	SetPosition(Vec3(200, 120, GetPosition().z));
	speed = baseSpeed;
	speedModifier = 1.0f;
	Active = true;

	if (lastPlayerScored == 0) SetDirection(Vec2(0, 1));
	else SetDirection(Vec2(1, 0));
}