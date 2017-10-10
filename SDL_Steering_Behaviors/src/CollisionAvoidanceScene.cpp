#include "CollisionAvoidanceScene.h"

using namespace std;

CollisionAvoidanceScene::CollisionAvoidanceScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/collisionAvoidance.png");
}

CollisionAvoidanceScene::~CollisionAvoidanceScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
}

void CollisionAvoidanceScene::update(float dtime, SDL_Event *event) {
	// Keyboard & Mouse events
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			path.push_back(Vector2D((float)(event->button.x), (float)(event->button.y)));
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->AdvancedPathFollowing(agents[0], agents[0]->getTarget(), dtime, &path);
	agents[0]->update(steering_force, dtime, event);
}

void CollisionAvoidanceScene::draw() {

	Line line;
	line.setOrigin(agents[0]->getPosition());
	for (int i = 0; i < path.size(); i++) {
		line.setDestiny(path[i]);
		line.drawLine();
		draw_circle(TheApp::Instance()->getRenderer(), (int)path[i].x, (int)path[i].y, 10, 255, 0, 0, 255);
		line.setOrigin(path[i]);
	}
	agents[0]->draw();
	text->Draw();
}

const char* CollisionAvoidanceScene::getTitle() {
	return "SDL Steering Behaviors :: Collision Avoidance Finding Demo";
}
