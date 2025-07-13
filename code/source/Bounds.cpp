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

	int wallWidth = 14;
	minY = GetPosition().y + wallWidth;
	maxY = GetPosition().y + sprite.GetFrameSize().y - wallWidth;
	minX = GetPosition().x + wallWidth;
	maxX = GetPosition().x + sprite.GetFrameSize().x - wallWidth;

	hitaudio = Halib::audiosystem.LoudSound(AUDIOHIT_PATH);
	playeroneaudio = Halib::audiosystem.LoudSound(PLAYERONEAUDIO_PATH);
	playertwoaudio = Halib::audiosystem.LoudSound(PLAYERTWOAUDIO_PATH);
	perfecthitaudio = Halib::audiosystem.LoudSound(PERFECTHITAUDIO_PATH);

	hitSoundToPlay = hitaudio;
	kickers = CreateKickers();

	player1Counter = std::make_shared<ScoreCounter>();
	player1Counter->SetPosition(Vec3(GetPosition().x- player1Counter->sprite.GetFrameSize().x -64, GetPosition().y + 72, 0));
	AddEntity(player1Counter);
	player2Counter = std::make_shared<ScoreCounter>();
	player2Counter->SetPosition(Vec3(GetPosition().x + sprite.GetFrameSize().x + 64, GetPosition().y + 72, 0));
	AddEntity(player2Counter);

}
void Bounds::Update(float deltaTime) {

	
	if (!isBallInBounds()) {
		myball->DisableBallWithGracePeriod();
		
	}

	HandleInputs();
	
}
void Bounds::HandleInputs() {

	if (!myball->Active) {
		if (GetButtonPressed(lastPlayerScored, START) || GetButtonPressed(0, RIGHT_SHOULDER) || GetButtonPressed(1, RIGHT_SHOULDER)){
			
			if (gameOver) {
				player1Counter->ResetScore();
				player2Counter->ResetScore();
			}
			myball->ResetBall(lastPlayerScored);
		}
	}

	if (GetButtonPressed(0, UP)) {

		
		std::pair<bool, float> canBeReflected = kickers[0]->CanReflectBall(Directions::top, minY, myball->GetPosition());
		if (canBeReflected.first) {
			BounceBall(Directions::top,canBeReflected.second);
			
		}
		if (!kickers[0]->IsOnCooldown()) {
			kickers[0]->PutOnCooldown();
			Halib::audiosystem.Play(playeroneaudio);
		}

	}
	if (GetButtonPressed(1, RIGHT)) {
		std::pair<bool, float> canBeReflected = kickers[1]->CanReflectBall(Directions::right, maxX, myball->GetPosition() + Vec3(myball->sprite.GetFrameSize().x,0,0));
		
		if (canBeReflected.first) {
			BounceBall(Directions::right, canBeReflected.second);
			
		}
		if (!kickers[1]->IsOnCooldown()) {
			kickers[1]->PutOnCooldown();
			Halib::audiosystem.Play(playertwoaudio);
		}
	}
	
	if (GetButtonPressed(0, DOWN)) {
		std::pair<bool, float> canBeReflected = kickers[2]->CanReflectBall(Directions::bottom, maxY, myball->GetPosition() + Vec3(0, myball->sprite.GetFrameSize().y, 0));
		if (canBeReflected.first) {
			BounceBall(Directions::bottom, canBeReflected.second);
			
		}
		if (!kickers[2]->IsOnCooldown()) {
			kickers[2]->PutOnCooldown();
			kickers[2]->sprite.frameIndex = VecI2(1,1);
			Halib::audiosystem.Play(playeroneaudio);
		}
	}
	if (GetButtonPressed(1, LEFT)) {
		std::pair<bool, float> canBeReflected = kickers[3]->CanReflectBall(Directions::left, minX, myball->GetPosition());
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
	if (point.y < minY) 
	{
		myball->SetPosition(Vec3(myball->GetPosition().x, minY, myball->GetPosition().z));
		
		return false;
	}

	if (point.x > maxX) {
		myball->SetPosition(Vec3(maxX - (myball->sprite.GetFrameSize().x), myball->GetPosition().y, myball->GetPosition().z));
		
		return false;
	}
	if (point.y > maxY) {
		myball->SetPosition(Vec3(myball->GetPosition().x, maxY - (myball->sprite.GetFrameSize().y ), myball->GetPosition().z));
		
		return false;
	}
	if (point.x < minX) {
		myball->SetPosition(Vec3(minX, myball->GetPosition().y, myball->GetPosition().z));
		
		return false;
	}
	return true;
}

void Bounds::SetBallDirection(Vec2 newDir) {
	myball->SetDirection(newDir);


	Halib::audiosystem.Play(hitSoundToPlay);
}

void Bounds::BounceBall(Directions dir, float distanceFactor){

	std::cout << "distancefactor: " << distanceFactor << std::endl;
	if (distanceFactor == 0) distanceFactor = 0.1f;
	if (myball->Active == false) return;

	Vec2 newBallDir = myball->GetDirection();
	Vec2 ballDirSign = GetBallDirSign(newBallDir);
	
	
	Vec3 newBallPos = myball->GetPosition();
	switch (dir) {

		case top:
			
			newBallDir.y = fabs(newBallDir.y) * 0.5f * 1 / distanceFactor;
			newBallDir.x = ballDirSign.x * distanceFactor;
			if (myball->GetMiddlePoint().y <= minY) newBallPos.y = minY +1;
			break;

		case bottom:
			
			newBallDir.y = -1 * fabs(newBallDir.y) * 0.5f * 1/distanceFactor;
			newBallDir.x = ballDirSign.x * distanceFactor;
			if (myball->GetMiddlePoint().y >= maxY) newBallPos.y = maxY - 1 - myball->sprite.GetFrameSize().y;
			
			break;

		case left:
			
			newBallDir.x = fabs(newBallDir.x) * 0.5f * 1 / distanceFactor;
			newBallDir.y = ballDirSign.y * distanceFactor;
			if (myball->GetMiddlePoint().x >= minX) newBallPos.x = minX + 1;
			break;

		case right:
			
			newBallDir.x = -1 * fabs(newBallDir.x) * 0.5f * 1 / distanceFactor;;
			newBallDir.y = ballDirSign.y * distanceFactor;
			if (myball-> GetMiddlePoint().x >= maxX) newBallPos.x = maxX - 1 - myball->sprite.GetFrameSize().x;
			break;
	}
	float speedMod;
	if (distanceFactor >= 0.93) {
		hitSoundToPlay = perfecthitaudio;
		speedMod = 1.6f;
	}
	else {
		hitSoundToPlay = hitaudio;
		speedMod = 1.0f;
	}
	myball->SetPosition(newBallPos);
	SetBallDirection(newBallDir);

	myball->IncreaseSpeed(4.0f);
	myball->speedModifier = speedMod;
	myball->ResetGracePeriod();
	

}
Vec2 Bounds::GetBallDirSign(Vec2 ballDir) {
	Vec2 newVec = Vec2(1, 1);
	if (ballDir.x < 0) newVec.x = -1;
	if (ballDir.y < 0) newVec.y = -1;

	return newVec;
}

std::array<std::shared_ptr<Kicker>, 4> Bounds::CreateKickers() {
	std::array<std::shared_ptr<Kicker>, 4> localKickers;
	localKickers[0] = std::make_shared<Kicker>(Vec3(200, 120, -1), Halib::UP);
	
	localKickers[1] = std::make_shared<Kicker>(Vec3(200, 120, -1), Halib::RIGHT);
	localKickers[1]->sprite.frameIndex = VecI2(2, 1);

	localKickers[2] = std::make_shared<Kicker>(Vec3(200, 121, -1), Halib::DOWN);
	localKickers[2]->sprite.flipY = true;

	localKickers[3] = std::make_shared<Kicker>(Vec3(200, 120, -1), Halib::LEFT);
	localKickers[3]->sprite.frameIndex = VecI2(2, 1);
	localKickers[3]->sprite.flipX = true;

	Halib::AddEntity(localKickers[0]);
	Halib::AddEntity(localKickers[1]);
	Halib::AddEntity(localKickers[2]);
	Halib::AddEntity(localKickers[3]);

	return localKickers;
}

void Bounds::PlayerScore(int controllerID) {
	if (controllerID == 0) {
		player1Score++;
		lastPlayerScored = 0;
		player1Counter->AddScoreVisual();
		if (player1Score > 5) gameOver = true;
		return;
	}
	else {
		player2Score++;
		lastPlayerScored = 1;
		player2Counter->AddScoreVisual();
		if (player2Score > 5) gameOver = true;
		return;
	}
}

void Bounds::BallHasDied(Vec2 ballMiddlePoint) {
	
	Directions closestDir = top;
	int currentClosest = 1000;

	float distance = abs(minY - ballMiddlePoint.y);
	if (distance < currentClosest) {
		currentClosest = distance;
		closestDir = top;
	}
	distance = abs(maxX - ballMiddlePoint.x);
	if (distance < currentClosest) {
		currentClosest = distance;
		closestDir = right;
	}
	distance = abs(maxY - ballMiddlePoint.y);
	if (distance < currentClosest) {
		currentClosest = distance;
		closestDir = bottom;
	}
	distance = abs(minX - ballMiddlePoint.y);
	if (distance < currentClosest) {
		currentClosest = distance;
		closestDir = left;
	}
	
	switch (closestDir) {
	case top:
		PlayerScore(1);
		break;
	case right:
		PlayerScore(0);
		break;
	case bottom:
		PlayerScore(1);
		break;
	case left:
		PlayerScore(0);
		break;

	}
}

