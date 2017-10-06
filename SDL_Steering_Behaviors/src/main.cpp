#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "SceneKinematicSeek.h"
#include "SeekScene.h"
#include "FleeScene.h"
#include "ArriveScene.h"
#include "PursueScene.h"
#include "WanderScene.h"
#include "PathFollowingScene.h"
#include "SceneKinematicFlee.h"
#include "AdvancedPathFollowingScene.h"


using namespace std; 

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SeekScene;
	app->setWindowTitle(curr_scene->getTitle());

	while (!quit)
	{
		// Run app frame by frame
		event = app->run(curr_scene);

		// Keyboard events
		switch (event.type){

			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_8){
					delete(curr_scene);
					curr_scene = new SceneKinematicSeek;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_9){
					delete(curr_scene);
					curr_scene = new SceneKinematicFlee;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_1){
					delete(curr_scene);
					curr_scene = new SeekScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_2){
					delete(curr_scene);
					curr_scene = new FleeScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_3) {
					delete(curr_scene);
					curr_scene = new ArriveScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_4) {
					delete(curr_scene);
					curr_scene = new PursueScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_5) {
					delete(curr_scene);
					curr_scene = new WanderScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_6) {
					delete(curr_scene);
					curr_scene = new PathFollowingScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_7) {
					delete(curr_scene);
					curr_scene = new AdvancedPathFollowingScene;
					app->setWindowTitle(curr_scene->getTitle());
				}

				if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)){quit = true;}

				if (event.key.keysym.scancode == SDL_SCANCODE_F){app->setFullScreen();}

				break;
			case SDL_QUIT:
				quit = true;
				break;
			}

	}

	return 0;
}