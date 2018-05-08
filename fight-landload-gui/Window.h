#pragma once

/* 窗口类 */

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>


using std::unique_ptr;
using std::string;


class Window {
public:
	Window(const string &title = "Demo", int w = 1280, int h = 640);

	// 载入图片
	SDL_Texture *loadImage(const string &file);

	// 渲染文本
	SDL_Texture *renderText(const string &fontFile, const string &msg,
		SDL_Color color, int fontSize);

	// 清屏
	void clear() { SDL_RenderClear(mRenderer.get()); }

	// 绘制
	void draw(SDL_Texture *tex, SDL_Rect &dst, SDL_Rect *clip = NULL, double angle = 0.0,
		int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// 呈现
	void present() { SDL_RenderPresent(mRenderer.get()); }

	// 返回窗口矩形大小；
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

