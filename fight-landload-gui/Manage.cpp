#include "Manage.h"
#include "MouseDrag.h"
#include <iostream>


using std::cout;
using std::endl;



// 初始化所有组件
int initialize(Window *window) {

	// 载入背景图
	try {
		window->loadBackground("res/background.jpg");
	}
	catch (const std::runtime_error &e) {
		cout << e.what() << endl;
		delete window;
		return -1;
	}

	// 注册鼠标拖动事件到事件分发系统
	// 这里一定在堆上建立对象
	MouseDrag::instance().registered(SDL_MOUSEBUTTONDOWN);
	MouseDrag::instance().registered(SDL_MOUSEBUTTONUP);

	return 1;
}

