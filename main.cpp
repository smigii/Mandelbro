#include <SDL.h>
#include <ccomplex>

// KEYBOARD ACCESS
#ifdef _WIN32 || _WIN64
#include <Windows.h>
#endif

typedef long double ldouble;

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;
int SCR_WH_RATIO = SCR_WIDTH / SCR_HEIGHT;

ldouble REAL_S = -2.5;
ldouble REAL_F = 2.5;
ldouble IMAG_S = -2.5;
ldouble IMAG_F = 2.5;
ldouble FACTOR = 0.5;

int MAX_ITER = 200;
int CLAMP = 20;

int mandelbrot(std::complex<ldouble> c, int max_iter)
{
	std::complex<ldouble> z = 0;
	int n = 0;

	while (abs(z) <= 2 && n < max_iter) {
		z = z * z + c;
		n++;
	}

	return n;
}

ldouble map(ldouble val, ldouble from_min, ldouble from_max, ldouble to_min, ldouble to_max)
{
	return (val - from_min) * (to_max - to_min) / (from_max - from_min) + to_min;
}

// SDL needs argc, argv and a return
int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* win;
	SDL_Renderer* renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(SCR_WIDTH, SCR_HEIGHT, 0, &win, &renderer);
	SDL_RenderSetLogicalSize(renderer, SCR_WIDTH, SCR_HEIGHT);

	while (1) {
		SDL_RenderPresent(renderer);

		for (int x = 0; x < SCR_WIDTH; x++) {

			if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
				break;
			if (GetKeyState('q') & 0x8000) // lol this doesn't work
				break;

			ldouble excess = (SCR_WIDTH - SCR_HEIGHT) / 2;
			ldouble y_min = -excess;
			ldouble y_max = SCR_HEIGHT + excess;
			for (int y = 0; y < SCR_HEIGHT; y++) {

				ldouble imag = map(y, -excess, SCR_HEIGHT + excess, IMAG_S, IMAG_F);
				ldouble real = map(x, 0, SCR_WIDTH, REAL_S, REAL_F);

				int n = mandelbrot(std::complex<ldouble>(real, imag), MAX_ITER);

				int bright = (n == MAX_ITER) ? 0 : map(n, 0, MAX_ITER, 0, 255);
				//bright = (bright < CLAMP) ? 0 : bright;

				int r = map(pow(bright, 2), 0, 6502, 0, 255);
				int g = bright;
				int b = map(sqrt(bright), 0, sqrt(255), 0, 255);

				SDL_SetRenderDrawColor(renderer, r, g, b, 255);
				SDL_RenderDrawPoint(renderer, x, y);

			}
		}

	}

	return 0;
}

/* ============================================================================
Started from https://www.youtube.com/watch?v=KnCNfBb2ODQ
============================================================================ */