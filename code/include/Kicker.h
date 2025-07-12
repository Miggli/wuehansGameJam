#pragma once

#include "Halib/Entity.h"
#include "Halib/Audio.h"
#include "Halib/System.h"

struct Kicker : public Halib::Entity
{
public:
	Kicker(Halib::Vec3 position, Halib::Button button);
	void Update(float deltaTime) override;
	bool HasBeenPressedInTime();
	//Factor between 0 and 1. 0 = earliest possible time (worst); 1 = latest possible time = (best)
	float GetPerfectTimingFactor();
	void ResetPress();
private:
	static inline const char* const GRAPHIC_PATH = "assets/Ball.bmp";
	Halib::Button buttonToUse;
	float hasBeenPressedTimer = 0.0f;
	float leeWayTime = 0.4f;
	bool isPressed = false;

	float coolDownTimer = 0.0f;
	float coolDown= 0.5f;
	bool isOnCooldown = false;
	

};