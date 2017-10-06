#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior(){}

SteeringBehavior::~SteeringBehavior(){}

float SteeringBehavior::AngleSmooth(float angle) {
	float angleToUpdate = angle;
	float angleDelta = angleToUpdate - angle;
	if (angleDelta > 180.f) {
		angle += 360;
	}
	else if (angleDelta < -180.f) {
		angle -= 360.f;
	}
	return (angle + angleToUpdate * 0.1f);
}

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
Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, int radius, float dtime){
	int slowingRadius = radius;
	if (slowingRadius == 0) {
		slowingRadius = 1;
	}
	Vector2D desiredVelocity = target - agent->getPosition();

	float distanceToTarget = Vector2D(target - agent->getPosition()).Length();
	desiredVelocity = desiredVelocity.Normalize();

	if (distanceToTarget > slowingRadius) { desiredVelocity *= agent->max_velocity; }
	else { desiredVelocity *= agent->max_velocity * (distanceToTarget / slowingRadius); }

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	return steeringForce;

}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, int radius, float dtime){
	return Arrive(agent, target->position, radius, dtime);
}

//Pursue behaviour
Vector2D SteeringBehavior::Pursue(Agent *agent, Vector2D target, Vector2D targetV, float dtime, Vector2D* predictedTarget) {

	*predictedTarget = target;

	if (targetV.Length() != 0) {
		float distanceToTarget = Vector2D(target - agent->getPosition()).Length();
		float T = distanceToTarget / targetV.Length();

		*predictedTarget = target + targetV * T;
	}

	Vector2D desiredVelocity = *predictedTarget - agent->getPosition();
	desiredVelocity = desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	return steeringForce;
}

Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime, Vector2D* predictedTarget){
	return Pursue(agent, target->position, target->velocity, dtime, predictedTarget);
}

//Evade behaviour
Vector2D SteeringBehavior::Evade(Agent *agent, Vector2D target, float dtime){
	return Vector2D(0, 0);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime){
	return Evade(agent, target->position, dtime);
}

//Wander behaviour
Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D target, float dtime, float wanderMaxAngleChange, float wanderRadius){
	float wanderAngle = 0.01;
	float targetAngle;
	float wanderOffset = (target - agent->position).Length();
	//Calculate the angle
	float angle = AngleSmooth(atan2f(agent->velocity.x, agent->velocity.y));
	float distance = (agent->position - target).Length();
	
	wanderAngle += RandomBinomial() * wanderMaxAngleChange;
	targetAngle = angle + wanderAngle;

	Vector2D circleCenter = agent->position + agent->velocity * wanderOffset;
	Vector2D newTarget(circleCenter.x * wanderRadius * cos(targetAngle), circleCenter.y * wanderRadius * sin(targetAngle));

	return Seek(agent, newTarget, dtime);
	
}


//Path Following behaviour
Vector2D SteeringBehavior::PathFollowing(Agent *agent, Vector2D target, float dtime) {
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity = desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;

	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;

	return steeringForce;
}

Vector2D SteeringBehavior::PathFollowing(Agent *agent, Agent *target, float dtime) {
	return Seek(agent, target->position, dtime);
}
