#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Image.h"
#include <queue>

class PathFollowingScene :
	public Scene
{
public:
	PathFollowingScene();
	~PathFollowingScene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	std::queue<Vector2D> path;
private:
	std::vector<Agent*> agents;
	Image* text;
	Vector2D target;
};
