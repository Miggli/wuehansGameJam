#pragma once

#include "Halib/Entity.h"

struct Ball : public Halib::Entity 
{
	static inline const char* const GRAPHIC_PATH = "assets/ball.bmp";
	float speed = 50.0f;
	Halib::Vec2 direction = Halib::Vec2(0.0f, 0.0f);
	Ball();
	void Update(float deltaTime) override;
	Halib::Vec2 CalculateRandomDir();

};