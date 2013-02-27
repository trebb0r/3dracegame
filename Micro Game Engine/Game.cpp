#include <cassert>

#include "Time.hpp"
#include "FPS.hpp"

#include "Hud.hpp"
#include "Renderer.hpp"
#include "ShaderProgram.hpp"
#include "Game.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Behaviours/KeysBehaviour.hpp"
#include "Behaviours/WASDBehaviour.hpp"
#include "Behaviours/RotatingBehaviour.hpp"
#include "Collider.hpp"

Game::Game()
:	window(NULL), hud(NULL), renderer(NULL), world(NULL), camera(NULL), light(NULL)
{
	window = new sf::RenderWindow( sf::VideoMode( 800, 600 ), "Saxion Game" ); // get a window
	std::cout << "Init Glew" << glewInit() << std::endl;
	hud = new Hud( window );
	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	renderer = new Renderer( window );
}

Game::~Game()
{
	//dtor
}

void Game::build()
{
	renderer->use(  new ShaderProgram( "shaders/default.vs", "shaders/default.fs" ) );
	camera = new Camera( "Camera", glm::vec3( 0, 1, 10 ) );
		//camera->setBehaviour( new WASDBehaviour( camera, window ) );
	light = new Light( "Light", glm::vec3( 2.0f, 10.0f, 15.0f ) );
	Mesh * suzanna = Mesh::load( "models/suzanna.obj");
	world = new World( "World" );
		world->add( camera );
		world->add( light );
		GameObject * player = new GameObject("Player", glm::vec3( 0.0, 0.0, 0.0 ));
			//player->setBehaviour( new RotatingBehaviour( player ) );
			player->setBehaviour(new KeysBehaviour( player , this ));
			player->setMesh( suzanna );
			player->setColorMap( Texture::load("models/bricks.jpg") );
			player->setCollider( new Collider( player ) );
			world->add( player  );
		//GameObject * enemy = new GameObject("Enemy", glm::vec3( 2,0,-5 ) );
			//enemy->setBehaviour( new KeysBehaviour( enemy ) );
			//enemy->setMesh( suzanna );
			//enemy->setColorMap( Texture::load("models/monkey.jpg") );
			//enemy->setCollider( new Collider( enemy ) );
			//world->add( enemy );
		GameObject * floor = new GameObject("Floor", glm::vec3( 0,0,0 ) );
			floor->setMesh( Mesh::load( "models/floor.obj" ) );
			floor->setColorMap( Texture::load( "models/land.jpg" ) );
			world->add( floor );
}

void Game::run()
{
	running = true;
	while ( running ) {
		Time::update();
		FPS::update();
		control();
		if ( running ) { // control may have changed running;
			update( Time::step() );
			draw();
		}
	}
}

void Game::stop()
{
    window->close();
    running = false;
}

// private functions

void Game::control()
{
	sf::Event event;
	while( window->pollEvent( event ) ) {
		if ( event.type == sf::Event::Closed ) {
			window->close();
			running = false; // running = false;
		}
	}
}

void Game::update( float step )
{
	assert( world != NULL );
	world->update( step );
	checkCollisions();
}

void Game::draw()
{
	assert( window != NULL );
	assert( renderer != NULL );
	assert( world != NULL );

	renderer->draw( world );
	window->pushGLStates();
	hud->draw();
	window->popGLStates();
	window->display();
}


bool Game::checkCollisions()
{
	return world->checkCollisions();
}
