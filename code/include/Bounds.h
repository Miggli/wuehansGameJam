#pragma once

#include "Halib/Entity.h"
#include <Ball.h>
#include "Halib/Audio.h"
#include "Halib/System.h"
#include <array>
#include "Enums.h"
#include "Kicker.h"
struct Bounds : public Halib::Entity
{


public:
	static inline const char* const GRAPHIC_PATH = "assets/bounds.bmp";
	static inline const char* const AUDIOHIT_PATH = "assets/normalhit.wav";
	static inline const char* const PERFECTHITAUDIO_PATH = "assets/perfecthit.wav";

	static inline const char* const PLAYERONEAUDIO_PATH = "assets/clicktop.wav";
	static inline const char* const PLAYERTWOAUDIO_PATH = "assets/clickleft.wav";
	
	std::shared_ptr<Halib::Audio> hitaudio;
	std::shared_ptr<Halib::Audio> perfecthitaudio;
	std::shared_ptr<Halib::Audio> playeroneaudio;
	std::shared_ptr<Halib::Audio> playertwoaudio;
	
	std::shared_ptr<Halib::Audio> hitSoundToPlay;

	Bounds(std::shared_ptr<Ball> ball);
	
	void Update(float deltaTime) override;

	
	
private: 
	std::shared_ptr<Ball> myball;
	int maxY;
	int maxX;
	int minY;
	int minX;


	void HandleInputs();
	bool isBallInBounds();

	void SetBallDirection(Halib::Vec2 newDir);

	
	void BounceBall(Directions dir, float distanceFactor);
	Halib::Vec2 GetBallDirSign(Halib::Vec2 ballDir);

	std::array<std::shared_ptr<Kicker>, 4> kickers;
	std::array<std::shared_ptr<Kicker>, 4> CreateKickers();
	//0 - Top Kicker
	//1 - Right Kicker
	//2 - Bottom Kicker
	//3 - Left Kicker
};
