#include <SDL.h>
#include <iostream>
#include "Screen.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

using namespace maky;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	Screen screen;

	if (screen.init() == false)
	{
		std::cout << "Error initialising SDL." << std::endl;
	}

	Swarm swarm;

	while (true)
	{
		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		unsigned char green = (unsigned char)((1 + std::sin(elapsed * 0.0001)) * 128);
		unsigned char blue = (unsigned char)((1 + std::sin(elapsed * 0.0002)) * 128);
		unsigned char red = (unsigned char)((1 + std::sin(elapsed * 0.0003)) * 128);
		
		const Particle* const pParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * (Screen::SCREEN_WIDTH / 2);
			int y = particle.m_y * (Screen::SCREEN_WIDTH / 2) + Screen::SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		screen.update();

		if (screen.processEvents() == false)
		{
			break;
		}

	}
	screen.close();

	return 0;
}