#pragma once

#include "Halib/Entity.h"

struct Bounds : public Halib::Entity
{
	static inline const char* const GRAPHIC_PATH = "assets/ball.bmp";
	
	Bounds();
	void Update(float deltaTime) override;
	

};