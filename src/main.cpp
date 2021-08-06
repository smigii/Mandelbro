#include <SDL.h>
#include <algorithm>
// KEYBOARD ACCESS
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

#include "Mandelbrot.h"

typedef long double ldouble;

int SCR_WIDTH = 1920;
int SCR_HEIGHT = 1080;
float SCR_WH_RATIO = (float)SCR_WIDTH / (float)SCR_HEIGHT;


// SDL needs argc, argv and a return
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Texture* background = NULL;
	
	SDL_CreateWindowAndRenderer(SCR_WIDTH, SCR_HEIGHT, 0, &win, &renderer);
	SDL_RenderSetLogicalSize(renderer, SCR_WIDTH, SCR_HEIGHT);

	Mandelbrot* mandel = new Mandelbrot(SCR_WIDTH, SCR_HEIGHT, renderer);

	bool drawn = false;
	bool mouse_held = false;
	bool key_held = false;

	SDL_Event ev;
	SDL_Rect rect;

	bool running = true;
	while (running) {

		if (!drawn) {
			background = mandel->draw();
			drawn = true;
		}

		SDL_RenderCopy(renderer, background, NULL, NULL);

		while (SDL_PollEvent(&ev) != 0) {

			switch (ev.type) {
			case SDL_MOUSEBUTTONDOWN:
				mouse_held = true;
				rect.x = ev.button.x; 
				rect.y = ev.button.y;
				break; 
			case SDL_MOUSEBUTTONUP:
				if (mouse_held) {
					mouse_held = false;
					mandel->update(rect.x, rect.y, rect.w);
					drawn = false;
					SDL_DestroyTexture(background);
				}
				break;

			case SDL_KEYDOWN:
				mouse_held = false;
				{
					SDL_Scancode sc = ev.key.keysym.scancode;
					if (sc == SDL_SCANCODE_ESCAPE || sc == SDL_SCANCODE_Q)
						running = false;
				}
				break;

			case SDL_QUIT:
				running = false;
				break;

			}
		}
		if (mouse_held) {
			int nx;
			int ny;
			SDL_GetMouseState(&nx, &ny);
			rect.w = abs(nx - rect.x);
			rect.h = abs(ny - rect.y);
			
			rect.w > rect.h ? rect.h = rect.w : rect.w = rect.h;

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