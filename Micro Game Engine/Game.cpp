#include <cassert>
#include "Time.hpp"
#include "FPS.hpp"

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
:	window(NULL), renderer(NULL), world(NULL), camera(NULL), light(NULL)
{
	window = new sf::Window( sf::VideoMode( 800, 600 ), "Saxion Game" ); // get a window
	//window->setVerticalSyncEnabled( true ); // sync with monitor ->60 hz approx
	std::cout << "Init Glew" << glewInit() << std::endl;
	renderer = new Renderer( window );
}

Game::~Game()
{
	//dtor
}

void Game::build()
{
	renderer->use(  new ShaderProgram( "shaders/default.vs", "shaders/default.fs" ) );
	camera = new Camera( "Camera", glm::vec3( 0, 0, 10 ) );
		camera->setBehaviour( new WASDBehaviour( camera, window ) );
	light = new Light( "Light", glm::vec3( 2.0f, 10.0f, 15.0f ) );
	Mesh * suzanna = Mesh::load( "models/suzanna.obj");
	world = new World( "World" );
		//world->setCamera( camera );
		//world->setLight( light );
		world->add( camera );
		world->add( light );
		GameObject * player = new GameObject("Player", glm::vec3( 0.0, -1.0, 0.0 ));
			player->setBehaviour( new RotatingBehaviour( player ) );
			player->setMesh( suzanna );
			player->setColorMap( Texture::load("models/bricks.jpg") );
			player->setCollider( new Collider( player ) );

			world->add( player  );
		GameObject * enemy = new GameObject("Enemy", glm::vec3( 2,-1,-5 ) );
			enemy->setBehaviour( new KeysBehaviour( enemy ) );
			enemy->setMesh( suzanna );
			enemy->setColorMap( Texture::load("models/monkey.jpg") );
			enemy->setCollider( new Collider( enemy ) );
			world->add( enemy );
}

void Game::run()
{
	running = true;
	while ( running ) {
		Time::update();
		control();
		if ( running ) { // control may have changed running;
			update( Time::step() );
			draw();
			FPS::update();
		}
	}
}

void Game::stop()
{
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
	assert( renderer != NULL );
	assert( world != NULL );

	renderer->setTime( Time::now() );
	//std::cout << "Time " << Time::now() << std::endl;
	world->draw( renderer );
	renderer->display();
}


bool Game::checkCollisions()
{
	return world->checkCollisions();
}
