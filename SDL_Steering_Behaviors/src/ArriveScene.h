#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Image.h"
#include "Line.h"

class ArriveScene :
	public Scene
{
public:
	ArriveScene();
	~ArriveScene();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Line* linea;
	Image* text;
	Vector2D target;
};


