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

	Halib::Vec2 vector = Halib::Normalize(Halib::Vec2(randomFloatX, randomFloatY));

	std::cout << "calculating random dir for ball: " << vector.x << "   " << vector.y << std::endl;
	
	return vector;
}