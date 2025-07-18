#include <memory>
#include "Halib/Graphic.h"
#include "Halib/System.h"
#include "Character.h"
#include "Ball.h"
#include "Bounds.h"
#include <iostream>

void Halib::DrawUI() {

}

int main() 
{
	Halib::Init();

	//Create a player and add it to the system.
	//Entities will only be updated and drawn, when they have been added via AddEntity(...)
	

	std::shared_ptr<Ball> ball = std::make_shared<Ball>();
	Halib::AddEntity(ball);
	std::shared_ptr<Bounds> bounds = std::make_shared<Bounds>(ball);
	Halib::AddEntity(bounds);
	

	int lastControllerThatScored = 0;

	int r = 148;
	int g = 148;
	int b = 156;
	//We have 5 Bits per color channel, so 31 is the max value
	Halib::rendersystem.backgroundColor = Halib::Color(r/255.0f * 31.0f, g / 255.0f * 31.0f, b / 255.0f * 31.0f);
	while(!Halib::GetShouldClose()) 
	{
		Halib::Update();
		
		//This is stupid -_-
		//DeltaTime > 1.0f only in the first frame during resource load
		if(Halib::GetDeltaTime() < 1.0f)
			ball->Active = true;
	}
	
	return 0;
}
