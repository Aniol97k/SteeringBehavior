#include "Line.h"
#include "FlockingScene.h"

using namespace std;

FlockingScene::FlockingScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/flocking.png");
}

FlockingScene::~FlockingScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
}

void FlockingScene::update(float dtime, SDL_Event *event) {
	// Keyboard & Mouse events
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < agents.size(); i++) {
		Vector2D steering_force = agents[i]->Behavior()->Flocking(agents, dtime, i);
		agents[i]->update(steering_force, dtime, event);
	}

}

void FlockingScene::draw() {
	for (int i = 0; i < agents.size(); i++) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)agents[i]->getPosition().x, (int)agents[i]->getPosition().y, 15, 255, 0, 0, 255);
	}
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	text->Draw();
}

const char* FlockingScene::getTitle() {
	return "SDL Steering Behaviors :: Arrive Demo";
}