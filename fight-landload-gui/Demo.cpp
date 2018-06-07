

#include "Manage.h"
#include "EventManager.h"
#include "Table.h"


int main(int, char **) {
	auto window = std::make_shared<Window>();
	initialize(window.get());

	auto table = std::make_shared<Table>(window.get());
	table->addToWindow();

	SDL_Event e;
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				quit = true;
			EventManager::instance().DispatchEvent(&e);
		}
		window->clear();
		window->show();
		window->present();
	}

	return 0;
}
