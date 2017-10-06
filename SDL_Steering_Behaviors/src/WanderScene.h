#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Image.h"

class WanderScene :
	public Scene
{
public:
	WanderScene();
	~WanderScene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Image* text;
	Vector2D target;
	float wanderMaxAngleDiff, wanderOffset, wanderRadius;
	Vector2D circleCenter, newTarget;
};
