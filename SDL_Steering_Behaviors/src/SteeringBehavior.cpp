#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior(){}

SteeringBehavior::~SteeringBehavior(){}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime){
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime){
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime){
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime){	return KinematicFlee(agent, target->position, dtime);}

//Seek behaviour
Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime){
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity = desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	return steeringForce;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime){
	return Seek(agent, target->position, dtime);
}

//Flee behaviour
Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime) {
	Vector2D desiredVelocity = agent->getPosition() - target;
	desiredVelocity = desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	return steeringForce;
	
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime){
	return Flee(agent, target->position, dtime);
}

//Arrive behaviour
Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float dtime){
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity = desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	float distanceToTarget = target.Distance(target, agent->position);
	float slowingRadius = 0.5f;

	if (distanceToTarget > slowingRadius) {	return steeringForce; }
	else { return steeringForce*(distanceToTarget/slowingRadius); }
	return steeringForce;
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, float dtime){
	return Arrive(agent, target->position, dtime);
}

//Pursue behaviour
Vector2D SteeringBehavior::Pursue(Agent *agent, Vector2D target, float dtime){
	//Vector2D predictedTarget = target + targetV * (distanceToTarget / velocity);
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity = desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	return steeringForce;
}

Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime){
	return Pursue(agent, target->position, dtime);
}

//Evade behaviour
Vector2D SteeringBehavior::Evade(Agent *agent, Vector2D target, float dtime){
	return Vector2D(0, 0);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime){
	return Evade(agent, target->position, dtime);
}

//Wander behaviour
Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D target, float dtime){
	return Vector2D(0, 0);
}

Vector2D SteeringBehavior::Wander(Agent *agent, Agent *target, float dtime){
	return Wander(agent, target->position, dtime);
}

