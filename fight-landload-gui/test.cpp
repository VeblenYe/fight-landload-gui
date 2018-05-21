

/* ²âÊÔ */

#include "Manage.h"



int main(int, char **) {

	// ³õÊ¼»¯
	Window *window = new Window("Fight-Landlord");
	initialize(window);
	auto vec = readIn(window);

	Player *p1 = new Player();
	Player *p2 = new Player();
	Player *p3 = new Player();

	SDL_Event e;
	bool quit = false;
	
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_SPACE)
					deal(vec, p1, p2, p3);
			EventManager::instance().DispatchEvent(&e);
		}
		window->clear();
		window->show();
		for (auto i : p1->hold)
			i->show();
		for (auto i : p2->hold)
			i->show();
		for (auto i : p3->hold)
			i->show();
		window->present();
	}

	delete window;

	return 0;
}

