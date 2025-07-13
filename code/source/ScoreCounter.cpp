#include "ScoreCounter.h"
#include "Halib/Graphic.h"
#include "Halib/System.h"

using namespace Halib;

ScoreCounter::ScoreCounter() : Entity(Sprite(GRAPHIC_PATH, VecI2(7, 1)), Vec3(0.0f,0.0f,0.0f)) {

}

void ScoreCounter::Update(float deltaTime) {

}

void ScoreCounter::AddScoreVisual() {
	sprite.frameIndex += VecI2(1, 0);
}