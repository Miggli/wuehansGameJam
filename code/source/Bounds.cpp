#include "Bounds.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include "Halib/Audio.h"
#include "Kicker.h"

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

	hitaudio = Halib::audiosystem.LoudSound(AUDIOHIT_PATH);
	playeroneaudio = Halib::audiosystem.LoudSound(PLAYERONEAUDIO_PATH);
	playertwoaudio = Halib::audiosystem.LoudSound(PLAYERTWOAUDIO_PATH);
	kickers = CreateKickers();

}
void Bounds::Update(float deltaTime) {

	
	if (!isBallInBounds()) {
		myball->Active = false;
	}

	HandleInputs();
	
}
void Bounds::HandleInputs() {

	if (GetButtonPressed(0, UP)) {

		
		std::pair<bool, float> canBeReflected = kickers[0]->CanReflectBall(Directions::top, minY, myball->GetMiddlePoint());
		if (canBeReflected.first) {
			BounceBall(Directions::top,canBeReflected.second);
			
		}
		if (!kickers[0]->IsOnCooldown()) {
			kickers[0]->PutOnCooldown();
			Halib::audiosystem.Play(playeroneaudio);
		}

	}
	if (GetButtonPressed(0, RIGHT)) {
		std::pair<bool, float> canBeReflected = kickers[1]->CanReflectBall(Directions::right, maxX, myball->GetMiddlePoint());
		
		if (canBeReflected.first) {
			BounceBall(Directions::right, canBeReflected.second);
			kickers[1]->PutOnCooldown();
		}
		if (!kickers[1]->IsOnCooldown()) {
			kickers[1]->PutOnCooldown();
			Halib::audiosystem.Play(playertwoaudio);
		}
	}
	
	if (GetButtonPressed(0, DOWN)) {
		std::pair<bool, float> canBeReflected = kickers[2]->CanReflectBall(Directions::bottom, maxY, myball->GetMiddlePoint());
		if (canBeReflected.first) {
			BounceBall(Directions::bottom, canBeReflected.second);
			
		}
		if (!kickers[2]->IsOnCooldown()) {
			kickers[2]->PutOnCooldown();
			Halib::audiosystem.Play(playeroneaudio);
		}
	}
	if (GetButtonPressed(0, LEFT)) {
		std::pair<bool, float> canBeReflected = kickers[3]->CanReflectBall(Directions::left, minX, myball->GetMiddlePoint());
		if (canBeReflected.first) {
			BounceBall(Directions::left,canBeReflected.second);
			
		}
		if (!kickers[3]->IsOnCooldown()) {
			kickers[3]->PutOnCooldown();
			Halib::audiosystem.Play(playertwoaudio);
		}
	}
}
bool Bounds::isBallInBounds() {
	Vec2 point = myball->GetMiddlePoint();
	if (point.y < minY) return false;
	if (point.x > maxX) return false;
	if (point.y > maxY) return false;
	if (point.x < minX) return false;
	return true;
}

void Bounds::SetBallDirectionAndIncreaseSpeed(Vec2 newDir) {
	myball->SetDirection(newDir);

	myball->IncreaseSpeed(10.0f);

	Halib::audiosystem.Play(hitaudio);
}

void Bounds::BounceBall(Directions dir, float distanceFactor){

	std::cout << "distancefactor: " << distanceFactor << std::endl;
	if (myball->Active == false) return;

	Vec2 newBallDir = myball->GetDirection();
	Vec2 ballDirSign = GetBallDirSign(newBallDir);
	float offset = myball->sprite.GetFrameSize().x * 0.5f + 1.0f;
	
	//TODO: FIX DISTANCE FACTOR!
	switch (dir) {

		case top:
			
			newBallDir.y = abs(newBallDir.y) * 0.5f;
			newBallDir.x = ballDirSign.x * distanceFactor;
			break;

		case bottom:
			
			newBallDir.y = -1 * abs(newBallDir.y) * 0.5f;
			newBallDir.x = ballDirSign.x * distanceFactor;
			
			break;

		case left:
			
			newBallDir.x = abs(newBallDir.x) * 0.5f;
			newBallDir.y = ballDirSign.y * distanceFactor;
			break;

		case right:
			
			newBallDir.x = -1 * abs(newBallDir.x) * 0.5f;
			newBallDir.y = ballDirSign.y * distanceFactor;
			break;
	}
	SetBallDirectionAndIncreaseSpeed(newBallDir);
	

}
Vec2 Bounds::GetBallDirSign(Vec2 ballDir) {
	Vec2 newVec = Vec2(1, 1);
	if (ballDir.x < 0) newVec.x = -1;
	if (ballDir.y < 0) newVec.y = -1;

	return newVec;
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

