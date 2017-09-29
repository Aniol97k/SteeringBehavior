#include "PursueScene.h"

using namespace std;

PursueScene::PursueScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	Agent *enemy = new Agent;
	enemy->setPosition(Vector2D(TheApp::Instance()->getWinSize().x - 100, TheApp::Instance()->getWinSize().y - 100));
	enemy->setTarget(enemy->getPosition());
	agent->loadSpriteTexture("../res/zombie1.png", 8);
	agents.push_back(enemy);

	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/pursueDemo.png");
}

PursueScene::~PursueScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
}

void PursueScene::update(float dtime, SDL_Event *event) {
	// Keyboard & Mouse events
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[1]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Pursue(agents[0], agents[1], dtime);
	agents[0]->update(steering_force, dtime, event);

	Vector2D steering_force_enemy = agents[1]->Behavior()->Pursue(agents[1], agents[1]->getTarget(), dtime);
	agents[1]->update(steering_force_enemy, dtime, event);
}

void PursueScene::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
	text->Draw();
}

const char* PursueScene::getTitle() {
	return "SDL Steering Behaviors :: Pursue Demo";
}