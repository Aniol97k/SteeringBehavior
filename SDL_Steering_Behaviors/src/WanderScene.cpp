#include "WanderScene.h"

using namespace std;

WanderScene::WanderScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/wanderDemo.png");
	wanderMaxAngleDiff = 45.f;
	wanderRadius = 200.f;
}

WanderScene::~WanderScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
}

void WanderScene::update(float dtime, SDL_Event *event) {
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
	Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], agents[0]->getTarget(), dtime, wanderMaxAngleDiff, wanderRadius);
	agents[0]->update(steering_force, dtime, event);
}

void WanderScene::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, wanderRadius, 30, 150, 190, 255);
	agents[0]->draw();
	text->Draw();
}

const char* WanderScene::getTitle() {
	return "SDL Steering Behaviors :: Seek Demo";
}


