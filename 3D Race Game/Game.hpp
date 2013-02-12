#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>

class Renderer;
class World;
class Camera;
class Light;
class Game
{
	private: // data members
		sf::Window * window;
		Renderer * renderer;
		World * world;
		Camera * camera;
		Light * light;

		bool running;

	public: // functions
		Game();
		virtual ~Game();

		void build();
		void run();
		void stop();

	private:
		void control();
		void update( float step );
		void draw();
		bool checkCollisions();

};

#endif // GAME_H
