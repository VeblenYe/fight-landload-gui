

/* ≤‚ ‘ */

#include <iostream>
#include <string>
#include <stdexcept>

#include "Window.h"
#include "Button.h"
#include "MouseDrag.h"
#include "Poker.h"
#include "ClassEventHandler.h"
#include "EventManager.h"


using std::cout;
using std::endl;
using std::string;
using std::runtime_error;


int main(int, char **) {

	Window *win = new Window();

	Poker *p1 = new Poker(win, 300, 400);
	Poker *p2 = new Poker(win, 350, 400);
	Poker *p3 = new Poker(win, 400, 400);

	auto background = win->loadImage("background.jpg");
	try {
		p1->loadButtonImage("30.jpg");
		p2->loadButtonImage("31.jpg");
		p3->loadButtonImage("32.jpg");
	}
	catch (const runtime_error &e) {
		cout << e.what() << endl;
		delete p1;
		delete p2;
		delete p3;
		delete win; 
	}

	ClassEventHandler<Poker> handler1(p1, &Poker::handle, p1->priority);
	ClassEventHandler<Poker> handler2(p2, &Poker::handle, p2->priority);
	ClassEventHandler<Poker> handler3(p3, &Poker::handle, p3->priority);
	ClassEventHandler<MouseDrag> handler4(&MouseDrag::instance(), &MouseDrag::handle, MouseDrag::instance().priority);
	EventManager::instance().AddEventHandler(SDL_MOUSEBUTTONDOWN, { &handler1, &handler2, &handler3, &handler4 });
	EventManager::instance().AddEventHandler(SDL_MOUSEBUTTONUP, { &handler1, &handler2, &handler3, &handler4 });

	SDL_Event e;
	bool quit = false;


	SDL_Rect dst = win->Box();
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			EventManager::instance().DispatchEvent(&e);
		}
		win->clear();
		win->draw(background, dst);
		p1->show(); p2->show(); p3->show();
		win->present();
	}


	delete win;

	return 0;
}

