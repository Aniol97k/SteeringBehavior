#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Image.h"

class PathFollowingScene :
	public Scene
{
public:
	PathFollowingScene();
	~PathFollowingScene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	struct Path;
	Image* text;
	Vector2D target;
};
