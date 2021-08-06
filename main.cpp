#include <SDL.h>

// KEYBOARD ACCESS
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

#include "Mandelbrot.h"

typedef long double ldouble;

int SCR_WIDTH = 1920*0.9;
int SCR_HEIGHT = 1080*0.9;
float SCR_WH_RATIO = (float)SCR_WIDTH / (float)SCR_HEIGHT;


// SDL needs argc, argv and a return
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Surface mandel_surface;

	SDL_CreateWindowAndRenderer(SCR_WIDTH, SCR_HEIGHT, 0, &win, &renderer);
	SDL_RenderSetLogicalSize(renderer, SCR_WIDTH, SCR_HEIGHT);

	Mandelbrot* mandel = new Mandelbrot(SCR_WIDTH, SCR_HEIGHT, renderer);

	bool drawn = false;

	SDL_Event ev;
	bool mouse_held = false;
	SDL_Rect rect;

	bool running = true;
	while (running) {

		if (!drawn) {
			mandel->draw();
			drawn = true;
		}

		while (SDL_PollEvent(&ev) != 0) {
			switch (ev.type) {
			case SDL_MOUSEBUTTONDOWN:
				mouse_held = true;
				rect.x = ev.button.x;
				rect.y = ev.button.y;

				rect.w = 200;
				rect.h = 200/SCR_WH_RATIO;

				break;
			case SDL_MOUSEBUTTONUP:
				mouse_held = false;
				break;
			case SDL_QUIT:
				running = false;
				break;

			}
		}
		if (mouse_held) {
			/*int nx;
			int ny;
			SDL_GetMouseState(&nx, &ny);
			rect.w = nx - rect.x;
			rect.h = ny - rect.y;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 40);
			SDL_RenderDrawRect(renderer, &rect);*/
			
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			SDL_RenderDrawRect(renderer, &rect);
		}


		SDL_RenderPresent(renderer);

	}

	return 0;
}

/* ============================================================================
Started from https://www.youtube.com/watch?v=KnCNfBb2ODQ
============================================================================ */