#include "Manage.h"
#include "MouseDrag.h"
#include <iostream>


using std::cout;
using std::endl;



// ��ʼ���������
int initialize(Window *window) {

	// ���뱳��ͼ
	try {
		window->loadBackground("res/background.jpg");
	}
	catch (const std::runtime_error &e) {
		cout << e.what() << endl;
		delete window;
		return -1;
	}

	// ע������϶��¼����¼��ַ�ϵͳ
	// ����һ���ڶ��Ͻ�������
	MouseDrag::instance().registered(SDL_MOUSEBUTTONDOWN);
	MouseDrag::instance().registered(SDL_MOUSEBUTTONUP);

	return 1;
}

