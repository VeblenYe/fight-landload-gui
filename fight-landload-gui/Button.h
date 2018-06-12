#pragma once

#include <string>
#include "Widget.h"


class Button : public Widget {
public:
	Button(Window *window, int x, int y, int w, int h, int p = 0, SDL_Rect *c = nullptr);

	virtual void loadButtonImage(const std::string &file);

	void show() override;

	void registered(int type);

	void unregister();

	std::pair<int, int> handle(SDL_Event *e);

	SDL_Rect *getClip() const {
		return clip;
	}

	void setClip(int x, int y, int w, int h) {
		clip = new SDL_Rect({ x, y, w, h });
	}

	int getState() const {
		return state;
	}

	void setState(int s) {
		state = s;
	}

	~Button() { 
		SDL_DestroyTexture(buttonImage); 
		if (clip)
			delete clip;
	}
private:
	// 按钮图片
	SDL_Texture *buttonImage;

	// 裁剪区域
	SDL_Rect *clip;

	// 按钮状态：0、1有效，-1无效
	int state = -1;

	// 注册的事件及处理函数
	std::shared_ptr<ClassEventHandler<Button>> handler =
		std::make_shared<ClassEventHandler<Button>>(this, &Button::handle, getPriority());
};
