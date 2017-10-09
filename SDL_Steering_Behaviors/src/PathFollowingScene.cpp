#include "PathFollowingScene.h"

using namespace std;

PathFollowingScene::PathFollowingScene() {
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	text = new Image(Vector2D(TheApp::Instance()->getWinSize().x / 2, 100));
	text->LoadImage("../res/Text/pathFollowing.png");
}

PathFollowingScene::~PathFollowingScene() {
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
	delete text;
}

void PathFollowingScene::update(float dtime, SDL_Event *event) {
	// Keyboard & Mouse events
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			path.emplace(Vector2D((float)(event->button.x), (float)(event->button.y)));
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->PathFollowing(agents[0], agents[0]->getTarget(), dtime, &path);
	agents[0]->update(steering_force, dtime, event);
}

void PathFollowingScene::draw() {
	
	std::queue<Vector2D> drawPath = path;
	Line line;
	if (!path.empty()) {
		line.setOrigin(agents[0]->getPosition());
		line.setDestiny(drawPath.front());
		line.drawLine();
		for (int i = 0; i < path.size(); i++) {
			if (drawPath.size() != 1) {
				line.setOrigin(drawPath.front());
				draw_circle(TheApp::Instance()->getRenderer(), (int)drawPath.front().x, (int)drawPath.front().y, 10, 255, 0, 0, 255);
				drawPath.pop();
				line.setDestiny(drawPath.front());
				line.drawLine();
			}
			else {
				draw_circle(TheApp::Instance()->getRenderer(), (int)drawPath.front().x, (int)drawPath.front().y, 10, 255, 0, 0, 255);
				drawPath.pop();
			}
		}
	}
	agents[0]->draw();
	text->Draw();
}

const char* PathFollowingScene::getTitle() {
	return "SDL Steering Behaviors :: Simple Path Finding Demo";
}

