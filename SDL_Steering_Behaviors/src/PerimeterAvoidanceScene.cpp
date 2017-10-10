#include "PerimeterAvoidanceScene.h"

using namespace std;

PerimeterAvoidanceScene::PerimeterAvoidanceScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/perimeterAvoidance.png");
}

PerimeterAvoidanceScene::~PerimeterAvoidanceScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
}

void PerimeterAvoidanceScene::update(float dtime, SDL_Event *event) {
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
	Vector2D steering_force = agents[0]->Behavior()->PerimeterAvoidance(agents[0], agents[0]->getTarget(), dtime, Vector2D(100, 100));
	Vector2D wanderForce = agents[0]->Behavior()->Wander(agents[0], agents[0]->getTarget(), dtime, 180.f, 200.f, 75.f, &circleCenter, &newTarget);;
	if(steering_force.Length() <= 0.f)
		steering_force = wanderForce;
	agents[0]->update(steering_force, dtime, event);

}

void PerimeterAvoidanceScene::draw() {

	draw_circle(TheApp::Instance()->getRenderer(), (int)newTarget.x, (int)newTarget.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)circleCenter.x, (int)circleCenter.y, 3, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)circleCenter.x, (int)circleCenter.y, 75.f, 30, 150, 190, 255);
	agents[0]->draw();
	text->Draw();
}

const char* PerimeterAvoidanceScene::getTitle() {
	return "SDL Steering Behaviors :: Perimeter avoidance Demo";
}
