#include "Line.h"
#include "ArriveScene.h"

using namespace std;

ArriveScene::ArriveScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/arriveDemo.png");
	linea = new Line(Vector2D(20, 20), Vector2D(30, 300));
	linea->setColor(0, 190, 0);
}

ArriveScene::~ArriveScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
	delete linea;
}

void ArriveScene::update(float dtime, SDL_Event *event) {
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
	Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], agents[0]->getTarget(), dtime);
	agents[0]->update(steering_force, dtime, event);

	linea->setOrigin(agents[0]->getPosition());
	linea->setDestiny(agents[0]->getPosition() + agents[0]->getVelocity());
}

void ArriveScene::draw() {
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	linea->drawVector();
	agents[0]->draw();
	text->Draw();
}

const char* ArriveScene::getTitle() {
	return "SDL Steering Behaviors :: Arrive Demo";
}