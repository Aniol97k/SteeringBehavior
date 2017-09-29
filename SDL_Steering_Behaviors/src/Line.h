#pragma once
#include "Vector2D.h"
#include "SDL_SimpleApp.h"
#include "SDL.h"

class Line{
private:
	Vector2D origin;
	Vector2D destiny;
	Vector2D vectorArrowRight;
	Vector2D vectorArrowLeft;
	int red;
	int green;
	int blue;
	void CalculateVectorArrows();
public:
	Line();
	Line(const Vector2D&, const Vector2D&);
	~Line();
	void drawLine();
	void drawVector();

	inline Vector2D getOrigin() { return origin; }
	inline Vector2D getDestiny() { return destiny; }

	inline void setOrigin(const Vector2D& value) { origin = value; CalculateVectorArrows(); }
	inline void setDestiny(const Vector2D& value) { destiny = value; CalculateVectorArrows(); }

	inline void setColor(const int& r, const int& g, const int& b) { 
		if(!(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0))		
			red = r; green = g; blue = b;
	}
};
	
	
	