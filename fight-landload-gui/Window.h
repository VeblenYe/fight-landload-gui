#pragma once

/* ������ */

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>
#include <vector>
#include "GUIfwd.h"


class Window {
public:
	Window(const std::string &title = "Demo", int w = 1600, int h = 900);

	// ����ͼƬ
	SDL_Texture *loadImage(const std::string &file);

	// ���뱳��ͼ
	void loadBackground(const std::string &file) {
		background = loadImage(file);
	}

	// ��Ⱦ�ı�
	SDL_Texture *renderText(const std::string &fontFile, const std::string &msg,
		SDL_Color color, int fontSize);

	// ����
	void clear() { SDL_RenderClear(mRenderer.get()); }

	// ����
	void draw(SDL_Texture *tex, const SDL_Rect &dst, const SDL_Rect *clip = NULL, double angle = 0.0,
		int xPivot = 0, int yPivot = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// ��ʾ����ͼ
	void show();

	// ����
	void present() { SDL_RenderPresent(mRenderer.get()); }

	// ���ش��ھ��δ�С��
	SDL_Rect Box() { SDL_GetWindowSize(mWindow.get(), &mBox.w, &mBox.h); return mBox; }
	
	// ��Ӵ������
	void addWidget(std::shared_ptr<Widget> w) {
		if (w != nullptr)
			widgets.push_back(w);
	}

	// �Ƴ��������
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

	// ����ͼ
	SDL_Texture *background;

	// ע������
	std::vector<std::shared_ptr<Widget>> widgets;
};
