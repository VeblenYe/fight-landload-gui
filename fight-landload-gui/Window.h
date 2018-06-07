#pragma once

/* 窗口类 */

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <vector>
#include "GUIfwd.h"


class Window {
public:
	Window(const std::string &title = "Demo", int w = 1600, int h = 900);

	// 载入图片
	SDL_Texture *loadImage(const std::string &file);

	// 载入背景图
	void loadBackground(const std::string &file) {
		background = loadImage(file);
	}

	// 渲染文本
	SDL_Texture *renderText(const std::string &fontFile, const std::string &msg,
		SDL_Color color, int fontSize);

	// 清屏
	void clear() { SDL_RenderClear(mRenderer.get()); }

	// 绘制
	void draw(SDL_Texture *tex, const SDL_Rect &dst, const SDL_Rect *clip = NULL, double angle = 0.0,
		int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// 显示背景图
	void show();

	// 呈现
	void present() { SDL_RenderPresent(mRenderer.get()); }

	// 返回窗口矩形大小；
	SDL_Rect Box() { SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h); return mBox; }
	
	// 添加窗口组件
	void addWidget(std::shared_ptr<Widget> w) {
		if (w != nullptr)
			widgets.push_back(w);
	}

	// 移除窗口组件
	void removeWidget(std::shared_ptr<Widget> w) {
		auto pos = std::find(widgets.begin(), widgets.end(), w);
		if (pos != widgets.end())
			widgets.erase(pos);
	}

	~Window() {
		SDL_DestroyTexture(background);
		SDL_Quit();
		TTF_Quit();
	}
private:
	static std::unique_ptr<SDL_Window, void(*)(SDL_Window *)> mWindow;
	static std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer *)> mRenderer;
	static SDL_Rect mBox;

	// 背景图
	SDL_Texture *background;

	// 注册的组件
	std::vector<std::shared_ptr<Widget>> widgets;
};
