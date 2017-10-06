#pragma once
#include "Agent.h"
#include "Vector2D.h"

class Agent;

class SteeringBehavior
{
private:
	//All the times are stored as seconds
	float time;
	float wanderUpdateTime;
	//Wander variables
	float wanderAngle = 0.f;
	float targetAngle = 0.f;
public:
	SteeringBehavior();
	~SteeringBehavior();

	inline float RandomBinomial() { return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX)); };
	float AngleSmooth(float);

	Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Seek(Agent *agent, Agent *target, float dtime);

	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Agent *target, float dtime);

	Vector2D Arrive(Agent *agent, Vector2D target, int radius, float dtime);
	Vector2D Arrive(Agent *agent, Agent *target, int radius, float dtime);

	Vector2D Pursue(Agent *agent, Vector2D target, Vector2D targetV, float dtime, Vector2D* predictedTarget);
	Vector2D Pursue(Agent *agent, Agent *target, float dtime, Vector2D* predictedTarget);

	Vector2D Evade(Agent *agent, Vector2D target, float dtime);
	Vector2D Evade(Agent *agent, Agent *target, float dtime);

	Vector2D Wander(Agent *agent, Vector2D target, float dtime, float wanderMaxAngleChange, float wanderOffset, float wanderRadius, Vector2D* circle, Vector2D* newT);
	Vector2D Wander(Agent *agent, Agent *target, float dtime, float wanderMaxAngleChange, float wanderOffset, float wanderRadius, Vector2D* circle, Vector2D* newT);

};
