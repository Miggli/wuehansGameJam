#pragma once

#include "Halib/Entity.h"
#include "Halib/Audio.h"
struct Ball : public Halib::Entity 
{

	static inline const char* const GRAPHIC_PATH = "assets/ball.bmp";
	static inline const char* const FAILSOUND_PATH = "assets/fail.wav";
	std::shared_ptr<Halib::Audio> failsound;

	Halib::Vec2 direction = Halib::Vec2(0.0f, 0.0f);
	Ball();
	void Update(float deltaTime) override;
	Halib::Vec2 CalculateRandomDir();

private:
	
	float speed = 50.0f;

	bool isInGracePeriod = false;
	float gracePeriodTime = 0.10f;
	float graceTimer = 0.0f;

	void HandleGracePeriod();

	bool shouldMove = true;

public:
	float speedModifier = 1.0f;
	void PlayFailSound();
	Halib::Vec2 GetMiddlePoint();
	Halib::Vec2 GetDirection();
	void SetDirection(Halib::Vec2 dir);
	void IncreaseSpeed(float increase = 2.0f);
	void DisableBallWithGracePeriod();
	void ResetGracePeriod();
	float GetSpeed();

	bool Active = true;
};