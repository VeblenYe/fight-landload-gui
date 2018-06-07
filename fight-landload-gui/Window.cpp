#include "Window.h"
#include "Widget.h"
#include <SDL_image.h>
#include <iostream>


using std::runtime_error;


std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> Window::mWindow =
std::unique_ptr<SDL_Window, void(*)(SDL_Window *)>(nullptr, SDL_DestroyWindow);

std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> Window::mRenderer =
std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)>(nullptr, SDL_DestroyRenderer);

SDL_Rect Window::mBox;


Window::Window(const std::string &title, int w, int h) try {
	if (SDL_Init( SDL_INIT_EVERYTHING) == -1)
		throw runtime_error("SDL_Init Failed");

	if (TTF_Init() == -1)
		throw runtime_error("TTF_Init Failed");

	mBox.x = 0; mBox.y = 0;
	mBox.w = w; mBox.h = h;

	mWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, mBox.w, mBox.h, SDL_WINDOW_SHOWN));
	if (mWindow == nullptr)
		throw runtime_error("SDL_CreateWindow Failed");

	mRenderer.reset(SDL_CreateRenderer(mWindow.get(), -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
	if (mRenderer == nullptr)
		throw runtime_error("SDL_CreateRenderer Failed");
}
catch (const runtime_error &e) {
	std::cout << e.what() << std::endl;
}


SDL_Texture *Window::loadImage(const std::string &file) {
	SDL_Texture *tex = IMG_LoadTexture(mRenderer.get(), file.c_str());
	if (tex == nullptr)
		throw runtime_error("IMG_Load_Texture Failed");
	return tex;
}


SDL_Texture *Window::renderText(const std::string &fontFile, const std::string &msg,
	SDL_Color color, int fontSize) {
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw runtime_error("TTF_OpenFont Failed");

	SDL_Surface *surf = TTF_RenderText_Blended(font, msg.c_str(), color);
	if (surf == nullptr)
		throw runtime_error("TTF_RenderText_Blended Failed");

	SDL_Texture *tex = SDL_CreateTextureFromSurface(mRenderer.get(), surf);
	if (tex == nullptr)
		throw runtime_error("SDL_CreateTextureFromSurface Failed");

	TTF_CloseFont(font);
	SDL_FreeSurface(surf);

	return tex;
}


void Window::draw(SDL_Texture *tex, const SDL_Rect &dst, const SDL_Rect *clip, double angle,
	int xPivot, int yPivot, SDL_RendererFlip flip) {
	xPivot += dst.w / 2;
	yPivot += dst.h / 2;

	SDL_Point pivot = { xPivot, yPivot };

	SDL_RenderCopyEx(mRenderer.get(), tex, clip, &dst, angle, &pivot, flip);
}


void Window::show() {
	draw(background, mBox);
	for (auto w : widgets)
		w->show();
}
