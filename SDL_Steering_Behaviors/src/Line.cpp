#include "Line.h"

Line::Line() : 
	origin(Vector2D(0, 0)), 
	destiny(Vector2D(0, 0)) 
{
	CalculateVectorArrows();
}
Line::Line(const Vector2D& orig, const Vector2D& dest) : 
	origin(orig), 
	destiny(dest) 
{
	CalculateVectorArrows();
}
Line::~Line() {}
void Line::CalculateVectorArrows() {
	Vector2D pointDifference = destiny - origin;
	float angle = atan(pointDifference.x / pointDifference.y);

	vectorArrowRight.x = sin(-90 -angle + 30) * 20;
	vectorArrowRight.y = sin(-90 -angle + 30) * 20;

	vectorArrowLeft.x = sin(-90 -angle - 30) * 20;
	vectorArrowLeft.y = sin(-90 -angle - 30) * 20;
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