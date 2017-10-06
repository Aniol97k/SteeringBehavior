#include "SteeringBehavior.h"

float ARRIVAL_DISTANCE = 20;


SteeringBehavior::SteeringBehavior() : time(1), wanderUpdateTime(1){}

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
Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D target, float dtime, float wanderMaxAngleChange, float wanderOffset, float wanderRadius, Vector2D* circle, Vector2D* newT){

	//Calculate the angle
	if (time > wanderUpdateTime) {
		float angle = AngleSmooth(atan2f(agent->velocity.x, agent->velocity.y));

		wanderAngle += RandomBinomial() * wanderMaxAngleChange;
		targetAngle = angle + wanderAngle;
		time -= wanderUpdateTime;
	}

	Vector2D circleCenter = agent->position + agent->getVelocity().Normalize() * wanderOffset;
	Vector2D newTarget(circleCenter.x + wanderRadius * cos(targetAngle * DEG2RAD),
					   circleCenter.y + wanderRadius * sin(targetAngle * DEG2RAD));

	time += dtime;
	*circle = circleCenter;
	*newT = newTarget;
	return Seek(agent, newTarget, dtime);

}

Vector2D SteeringBehavior::Wander(Agent *agent, Agent *target, float dtime, float wanderMaxAngleChange, float wanderOffset, float wanderRadius, Vector2D* circle, Vector2D* newT) {
	return Wander(agent, target->position, dtime, wanderMaxAngleChange, wanderOffset, wanderRadius, circle, newT);
}

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

//Path Following behaviour
Vector2D SteeringBehavior::PathFollowing(Agent *agent, Vector2D target, float dtime, std::queue<Vector2D>* path) {

	Vector2D steeringForce(0, 0);
	
	if (path->size() == 1) {
		steeringForce = Arrive(agent, path->front(), 25, dtime);
		if ((agent->position - path->front()).Length() <= ARRIVAL_DISTANCE) {
			path->pop();
		}
	}
	else if (!path->empty()) {
		steeringForce = Seek(agent, path->front(), dtime);
		if ((agent->position - path->front()).Length() <= ARRIVAL_DISTANCE) {
			path->pop();
		}
	}
	else {
		steeringForce = agent->getVelocity() * -0.5f;
	}
	return steeringForce;
}



Vector2D SteeringBehavior::PathFollowing(Agent *agent, Agent *target, float dtime, std::queue<Vector2D>* path) {
	return PathFollowing(agent, target->position, dtime, path);
}

Vector2D SteeringBehavior::AdvancedPathFollowing(Agent *agent, Vector2D target, float dtime, std::vector<Vector2D>* path) {

	Vector2D steeringForce(0, 0);

	if (path->size() == 1) {
		steeringForce = Arrive(agent, *path->begin(), 25, dtime);
		if ((agent->position - *path->begin()).Length() <= ARRIVAL_DISTANCE) {
			
			int position = 0;
			for (int i = 0; i < path->size(); i++) {
				if ((agent->getPosition() - path->at(i)).Length() < (agent->getPosition() - path->at(i)).Length()) {
					position = i;
				}
				path->erase(path->begin(), path->begin() + position - 1);
			}
		}
	}
	else if (!path->empty()) {
		steeringForce = Seek(agent, *path->begin(), dtime);
		if ((agent->position - *path->begin()).Length() <= ARRIVAL_DISTANCE) {
			//path->pop();
			int position = 0;
			for (int i = 0; i < path->size(); i++) {
				if ((agent->getPosition() - path->at(i)).Length() < (agent->getPosition() - path->at(i)).Length()) {
					position = i;
				}
				path->erase(path->begin(), path->begin() + position - 1);
			}
		}
	}
	else {
		steeringForce = agent->getVelocity() * -0.5f;
	}
	return steeringForce;
}



Vector2D SteeringBehavior::AdvancedPathFollowing(Agent *agent, Agent *target, float dtime, std::vector<Vector2D>* path) {
	return AdvancedPathFollowing(agent, target->position, dtime, path);
}

