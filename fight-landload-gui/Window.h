#pragma once

/* ������ */

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>


using std::unique_ptr;
using std::string;


class Window {
public:
	Window(const string &title = "Demo", int w = 1280, int h = 640);

	// ����ͼƬ
	SDL_Texture *loadImage(const string &file);

	// ��Ⱦ�ı�
	SDL_Texture *renderText(const string &fontFile, const string &msg,
		SDL_Color color, int fontSize);

	// ����
	void clear() { SDL_RenderClear(mRenderer.get()); }

	// ����
	void draw(SDL_Texture *tex, SDL_Rect &dst, SDL_Rect *clip = NULL, double angle = 0.0,
		int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// ����
	void present() { SDL_RenderPresent(mRenderer.get()); }

	// ���ش��ھ��δ�С��
	SDL_Rect Box() { SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h); return mBox; }

	~Window() {
		SDL_Quit();
		TTF_Quit();
	}
private:
	static unique_ptr<SDL_Window, void(*)(SDL_Window *)> mWindow;
	static unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> mRenderer;
	static SDL_Rect mBox;
};

