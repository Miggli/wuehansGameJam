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

	int wallWidth = 12;
	minY = GetPosition().y + wallWidth;
	maxY = GetPosition().y + sprite.GetFrameSize().y - wallWidth;
	minX = GetPosition().x + wallWidth;
	maxX = GetPosition().x + sprite.GetFrameSize().x - wallWidth;

	audio = Halib::audiosystem.LoudSound(AUDIOHIT_PATH);


	kickers = CreateKickers();

}
void Bounds::Update(float deltaTime) {

	Vec2 currentBallDir = myball->GetDirection();
	float ballWidth = myball->sprite.GetFrameSize().x * 0.5f;
	Vec2 newBallDir;
	if (myball->GetMiddlePoint().x < minX + ballWidth) {
		if (kickers[3]->HasBeenPressedInTime()) {
			BounceBall(Directions::left);
			kickers[3]->ResetPress();
		}
		else if (myball->GetMiddlePoint().x < minX) myball->Active = false;
	}
	if (myball->GetMiddlePoint().x > maxX - ballWidth) {
		
		if (kickers[1]->HasBeenPressedInTime()) {
			BounceBall(Directions::right);
			kickers[1]->ResetPress();
		}
		else if (myball->GetMiddlePoint().x > maxX) myball->Active = false;
	}
	if (myball->GetMiddlePoint().y < minY + ballWidth) {
		
		if (kickers[0]->HasBeenPressedInTime()) {
			BounceBall(Directions::top);
			kickers[0]->ResetPress();
		}
		else if (myball->GetMiddlePoint().y < minY) myball->Active = false;
	}
	if (myball->GetMiddlePoint().y > maxY - ballWidth) {
		
		if (kickers[2]->HasBeenPressedInTime()) {
			BounceBall(Directions::bottom);
			kickers[2]->ResetPress();
		}
		else if (myball->GetMiddlePoint().y > maxY) myball->Active = false;
	}
	
}

void Bounds::SetBallDirectionAndIncreaseSpeed(Vec2 newDir) {
	myball->SetDirection(newDir);

	myball->IncreaseSpeed(10.0f);

	Halib::audiosystem.Play(audio);
}

void Bounds::BounceBall(Directions dir){
	if (myball->Active == false) return;

	Vec2 newBallDir = myball->GetDirection();
	Vec3 newBallPos = Vec3(0.0f, 0.0f, 0.0f);
	float offset = myball->sprite.GetFrameSize().x * 0.5f + 1.0f;
	float timingFactor = 1.0f;
	switch (dir) {

		case top:
			timingFactor = kickers[0]->GetPerfectTimingFactor();
			newBallDir.y = abs(newBallDir.y);
			newBallDir.x = newBallDir.x * 0.5f * timingFactor;
			newBallPos = Vec3(Vec3(myball->GetPosition().x, minY + 1, myball->GetPosition().z));
				break;

		case bottom:
			timingFactor = kickers[2]->GetPerfectTimingFactor();
			newBallDir.y = -1 * abs(newBallDir.y);
			newBallDir.x = newBallDir.x * 0.5f * timingFactor;
			newBallPos = Vec3(myball->GetPosition().x, maxY - offset, myball->GetPosition().z);

			break;

		case left:
			timingFactor = kickers[3]->GetPerfectTimingFactor();
			newBallDir.x = abs(newBallDir.x);
			newBallDir.y = newBallDir.y * timingFactor;
			newBallPos = Vec3(minX + 1, myball->GetPosition().y, myball->GetPosition().z);
			break;

		case right:
			timingFactor = kickers[1]->GetPerfectTimingFactor();
			newBallDir.x = -1 * abs(newBallDir.x);
			newBallDir.y = newBallDir.y * 0.5f * timingFactor;
			newBallPos = Vec3(maxX - offset, myball->GetPosition().y, myball->GetPosition().z);
			break;
	}
	SetBallDirectionAndIncreaseSpeed(newBallDir);
	myball->SetPosition(newBallPos);

}

std::array<std::shared_ptr<Kicker>, 4> Bounds::CreateKickers() {
	std::array<std::shared_ptr<Kicker>, 4> localKickers;
	localKickers[0] = std::make_shared<Kicker>(Vec3(200.0f, minY, 0.0f), Halib::UP);
	localKickers[1] = std::make_shared<Kicker>(Vec3(maxX, 120.0f, 0.0f), Halib::RIGHT);
	localKickers[2] = std::make_shared<Kicker>(Vec3(200.0f, maxY, 0.0f), Halib::DOWN);
	localKickers[3] = std::make_shared<Kicker>(Vec3(minX, 120.0f, 0.0f), Halib::LEFT);

	Halib::AddEntity(localKickers[0]);
	Halib::AddEntity(localKickers[1]);
	Halib::AddEntity(localKickers[2]);
	Halib::AddEntity(localKickers[3]);

	return localKickers;
}

