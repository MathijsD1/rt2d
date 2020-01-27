#include <rt2d/core.h>
#include "gamescene.h"

/// @brief main entry point
int main( void )
{
	// Core instance
	Core core;

	// Scene01
	GameScene* gameScene = GameScene::getInstance();

	while(gameScene->isRunning()) { // check status of Scene every frame
		core.run(gameScene); // update and render the current scene
		core.showFrameRate(1); // show framerate in output every n seconds
	}
	//core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete gameScene; // delete Scene and everything in it from the heap to make space for next Scene

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
