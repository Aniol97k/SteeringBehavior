#include "Line.h"

Line::Line() : 
	origin(Vector2D(0, 0)), 
	destiny(Vector2D(0, 0)) 
{
	CalculateVectorArrows();
	setColor(255, 255, 255);
}
Line::Line(const Vector2D& orig, const Vector2D& dest) : 
	origin(orig),
	destiny(dest)
{
	setColor(255, 255, 255);
	CalculateVectorArrows();
}

Line::~Line() {}

void Line::CalculateVectorArrows() {
	Vector2D pointDifference = destiny - origin;
	if (pointDifference.x == 0 && pointDifference.y == 0) {
		pointDifference.x = 0.01f;
	}
	float arrowsAngle = 30;

	float angle = atan(pointDifference.y / pointDifference.x);
	if (destiny.x >= origin.x) {
		vectorArrowRight.x = cos(angle - (180 - arrowsAngle) * DEG2RAD) * 20 + destiny.x;
		vectorArrowRight.y = sin(angle - (180 - arrowsAngle) * DEG2RAD) * 20 + destiny.y;

		vectorArrowLeft.x = cos(angle + (180 - arrowsAngle) * DEG2RAD) * 20 + destiny.x;
		vectorArrowLeft.y = sin(angle + (180 - arrowsAngle) * DEG2RAD) * 20 + destiny.y;
	}
	else {
		vectorArrowRight.x = cos(angle + arrowsAngle * DEG2RAD) * 20 + destiny.x;
		vectorArrowRight.y = sin(angle + arrowsAngle * DEG2RAD) * 20 + destiny.y;

		vectorArrowLeft.x = cos(angle - arrowsAngle * DEG2RAD) * 20 + destiny.x;
		vectorArrowLeft.y = sin(angle - arrowsAngle * DEG2RAD) * 20 + destiny.y;
	}
}
void Line::drawLine() {
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), origin.x, origin.y, destiny.x, destiny.y);
}
void Line::drawVector() {
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), origin.x, origin.y, destiny.x, destiny.y);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), destiny.x, destiny.y, vectorArrowRight.x, vectorArrowRight.y);
	SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), destiny.x, destiny.y, vectorArrowLeft.x, vectorArrowLeft.y);
}