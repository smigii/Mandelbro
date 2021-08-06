#include <SDL.h>
#include <ccomplex>

// KEYBOARD ACCESS
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

#include "Mandelbrot.h"

typedef long double ldouble;

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;


// SDL needs argc, argv and a return
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(SCR_WIDTH, SCR_HEIGHT, 0, &win, &renderer);
	SDL_RenderSetLogicalSize(renderer, SCR_WIDTH, SCR_HEIGHT);

	Mandelbrot* mandel = new Mandelbrot(SCR_WIDTH, SCR_HEIGHT, renderer);

	while (1) {

		SDL_RenderPresent(renderer);
		mandel->draw();

	}

	return 0;
}

/* ============================================================================
Started from https://www.youtube.com/watch?v=KnCNfBb2ODQ
============================================================================ */