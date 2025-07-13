#pragma once

#include "Halib/Entity.h"
#include "Halib/Audio.h"
#include "Halib/System.h"
#include "Enums.h"
struct Kicker : public Halib::Entity
{
public:
	Kicker(Halib::Vec3 position, Halib::Button button);
	void Update(float deltaTime) override;

	//returns the bool if can be reflected. 
	// will also return a distance factor (how close the ball is to the kicker): 0=lowest ; 1 = highest
	std::pair<bool, float> CanReflectBall(Directions kickerDir, float boundValue, Halib::Vec2 ballPos);
	void PutOnCooldown();
	bool IsOnCooldown();
	
	
private:
	
	int allowedDistance = 12;
	static inline const char* const GRAPHIC_PATH = "assets/kickers.bmp";
	

	float coolDownTimer = 0.0f;
	float coolDown= 0.5f;
	bool isOnCooldown = false;
	

};
