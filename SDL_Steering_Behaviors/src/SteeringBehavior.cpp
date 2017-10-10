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

//Advanced Path Following
Vector2D SteeringBehavior::AdvancedPathFollowing(Agent *agent, Vector2D target, float dtime, std::vector<Vector2D>* path) {

	Vector2D steeringForce(0, 0);

	if (path->empty())
		return agent->getVelocity() * -0.5f;



	if (path->size() == 1) {
		steeringForce = Arrive(agent, *path->begin(), 25, dtime);
		if ((agent->position - *path->begin()).Length() <= ARRIVAL_DISTANCE) {
			path->clear();
		}
	}
	else if (!path->empty()) {
		steeringForce = Seek(agent, *path->begin(), dtime);
		if ((agent->getPosition() - *path->begin()).Length() <= ARRIVAL_DISTANCE) {

			float distance = (agent->getPosition() - path->at(1)).Length();
			float shortestDistance = distance;
			int position = 0;

			for (int i = 1; i < path->size(); i++) {
				distance = (agent->getPosition() - path->at(i)).Length();
				if (distance <= shortestDistance) {
					position = i;
					shortestDistance = distance;
				}
				
			}
			if (position != 0)
				path->erase(path->begin(), path->begin() + position);
			else
				path->erase(path->begin());
		}
	}
	/*else if (!path->empty()) {
		steeringForce = Seek(agent, *path->begin(), dtime);
		if ((agent->getPosition() - *path->begin()).Length() <= ARRIVAL_DISTANCE) {

			float distance = (agent->getPosition() - path->at(1)).Length();
			float shortestDistance = distance;
			int position = 0;

			for (int i = 1; i < path->size() - 1; i++) {
				//Line equation ->  y = (Vy / Vx)x + c
				//Calculate the line vector
				Vector2D lineVector(path->at(i).x - path->at(i + 1).x, path->at(i).y - path->at(i + 1).y);
				lineVector.Normalize();
				//calculate the line offset variable
				float c = path->at(i).y - (lineVector.y / lineVector.x) * path->at(i).x;
				//Calculate the projection of the agent in that line
				Vector2D closestPoint = abs(lineVector.x * agent->getPosition().x + lineVector.y * agent->getPosition().y + c) / sqrt(pow(lineVector.x, 2) + pow(lineVector.y, 2));
				//Calculate the distance from the agent to it's projection in the line
				distance = (agent->getPosition() - closestPoint).Length();

				if (distance <= shortestDistance) {
					position = i;
					path->at(i) = closestPoint;
					shortestDistance = distance;
				}

			}
			if (position != 0)
				path->erase(path->begin(), path->begin() + position - 1);
			else
				path->erase(path->begin());
		}
	}*/

	return steeringForce;
}


Vector2D SteeringBehavior::AdvancedPathFollowing(Agent *agent, Agent *target, float dtime, std::vector<Vector2D>* path) {
	return AdvancedPathFollowing(agent, target->position, dtime, path);
}


//Flocking behavior
Vector2D SteeringBehavior::Flocking(std::vector <Agent*> agents, float dtime, int agentIndex) {
	//Constants used in the function
	float SEPARATION_K = 0.5;
	float COHESION_K = 0.3;
	float ALIGNMENT_K = 0.2;

	float NEIGHBOR_RADIUS = 200.f;

	//Shared variables
	int agentCount = 0;
	Vector2D flockingForce;

	//Separation variables
	Vector2D separationVector;
	Vector2D separationDirection;
	//Cohesion variables
	Vector2D averagePosition;
	Vector2D cohesionDirection;
	//Alignment variables
	Vector2D averageVelocity;
	Vector2D alignmentDirection;
	
	//We iterate all the agents, for each agent we check all the others
	for (int i = 0; i < agents.size(); i++) {
		//The agent won't use the algorithm on itself
		if (i != agentIndex) {
			//Check if the other agent is in it's neighborhood
			if ((agents[agentIndex]->getPosition() - agents[i]->getPosition()).Length() < NEIGHBOR_RADIUS) {
				averagePosition += agents[i]->getPosition();
				averageVelocity += agents[i]->getVelocity();
				separationVector += agents[agentIndex]->getPosition() - agents[i]->getPosition();

				agentCount++;
			}
		}
	}
	separationVector /= agentCount;
	averageVelocity /= agentCount;
	averagePosition /= agentCount;
	averagePosition -= agents[agentIndex]->getPosition();

	separationDirection = separationVector.Normalize();
	cohesionDirection = averagePosition.Normalize();
	alignmentDirection = averageVelocity.Normalize();

	return flockingForce = separationDirection * SEPARATION_K + cohesionDirection * COHESION_K + alignmentDirection * ALIGNMENT_K;
}

