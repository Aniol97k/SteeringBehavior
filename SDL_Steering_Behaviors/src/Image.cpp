#include "Image.h"

Image::Image(const Vector2D& pos) : sprite_texture(nullptr),
				 position(pos),
				 width(0),
				 height(0)
{}

Image::~Image() {
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
}

bool Image::LoadImage(const std::string& path) {
	SDL_Surface *image = IMG_Load(path.c_str());
	if (!image) {
		std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);
	
	width = image->w;
	height = image->h;

	if (image)
		SDL_FreeSurface(image);
}
void Image::Draw() {
	
	SDL_Rect rect = { 0, 0, width, height };
	SDL_Rect drawRect = { (int)position.x - (width / 2), (int)position.y - (height / 2), width, height };

	SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &rect, &drawRect, 0, NULL, SDL_FLIP_NONE);
}

/*int SDL_RenderCopyEx(SDL_Renderer*          renderer,
						SDL_Texture*           texture,
						const SDL_Rect*        srcrect,
						const SDL_Rect*        dstrect,
						const double           angle,
						const SDL_Point*       center,
						const SDL_RendererFlip flip)*/