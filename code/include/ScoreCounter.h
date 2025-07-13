#pragma once

#include "Halib/Entity.h"

struct ScoreCounter : public Halib::Entity
{
	static inline const char* const GRAPHIC_PATH = "assets/scorecounter.bmp";
	ScoreCounter();
	
	
	void Update(float deltaTime) override;

	void AddScoreVisual();

};