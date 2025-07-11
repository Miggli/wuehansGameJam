#include "Bounds.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include "Halib/Audio.h"
#include <iostream>
#include <cmath>

using namespace Halib;

Bounds::Bounds(std::shared_ptr<Ball> ball) : Halib::Entity(Sprite(GRAPHIC_PATH, VecI2(1,1)), Vec3(200,120,-10)) {
	myball = ball;
	
	SetPosition(GetPosition() - 0.5f * Halib::Vec3(sprite.GetFrameSize(), 0));

	int wallWidth = 10;
	minY = GetPosition().y + wallWidth;
	maxY = GetPosition().y + sprite.GetFrameSize().y - wallWidth;
	minX = GetPosition().x + wallWidth;
	maxX = GetPosition().x + sprite.GetFrameSize().x - wallWidth;

	audio = Halib::audiosystem.LoudSound(AUDIOHIT_PATH);
}
void Bounds::Update(float deltaTime) {

	Vec2 currentBallDir = myball->GetDirection();
	Vec2 newBallDir;
	if (myball->GetMiddlePoint().x <= minX) {
		
		newBallDir = myball->CalculateRandomDir();
		newBallDir.x = abs(newBallDir.x);
		SetBallDirectionAndIncreaseSpeed(newBallDir);
		
	}
	if (myball->GetMiddlePoint().x >= maxX) {
		
		newBallDir = myball->CalculateRandomDir();
		newBallDir.x = -1 * abs(newBallDir.x);
		SetBallDirectionAndIncreaseSpeed(newBallDir);
	}
	if (myball->GetMiddlePoint().y <= minY) {
		
		newBallDir = myball->CalculateRandomDir();
		newBallDir.y =abs(newBallDir.y);
		SetBallDirectionAndIncreaseSpeed(newBallDir);
	}
	if (myball->GetMiddlePoint().y >= maxY) {
		
		newBallDir = myball->CalculateRandomDir();
		newBallDir.y = -1 * abs(newBallDir.y);
		SetBallDirectionAndIncreaseSpeed(newBallDir);
	}
	
}

void Bounds::SetBallDirectionAndIncreaseSpeed(Vec2 newDir) {
	myball->SetDirection(newDir);

	myball->IncreaseSpeed(myball->GetSpeed() * 0.3f);

	Halib::audiosystem.Play(audio);
}

