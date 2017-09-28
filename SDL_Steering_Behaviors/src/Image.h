#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"

class Image {
private:
	SDL_Texture *sprite_texture;
	Vector2D position;
	Uint32 width, height;

public:
	Image(const Vector2D&);
	~Image();
	bool LoadImage(const std::string&);
	void Draw();
};