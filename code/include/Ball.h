#pragma once

#include "Halib/Entity.h"

struct Ball : public Halib::Entity 
{

	static inline const char* const GRAPHIC_PATH = "assets/ball.bmp";
	
	Halib::Vec2 direction = Halib::Vec2(0.0f, 0.0f);
	Ball();
	void Update(float deltaTime) override;
	Halib::Vec2 CalculateRandomDir();

private:
	float speed = 50.0f;

	bool isInGracePeriod = false;
	float gracePeriodTime = 0.2f;
	float graceTimer = 0.0f;

	void HandleGracePeriod();

	bool shouldMove = true;

public:
	
	Halib::Vec2 GetMiddlePoint();
	Halib::Vec2 GetDirection();
	void SetDirection(Halib::Vec2 dir);
	void IncreaseSpeed(float increase = 2.0f);
	void DisableBallWithGracePeriod();
	void ResetGracePeriod();
	float GetSpeed();

	bool Active = true;
};