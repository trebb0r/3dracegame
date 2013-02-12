#include <iostream>

#include "FPS.hpp"
#include "Time.hpp"

float FPS::startTime = 0.0f;
int FPS::count = 0;

void FPS::update()
{
	float time = Time::now();
	FPS::count++;
	if ( time - startTime >= 1.0f ) {
		std::cout << "FPS " << count << std::endl;
		count = 0;
		startTime = time;
	}
}

