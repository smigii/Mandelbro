#pragma once

#include <SDL.h>
#include <complex>

class Mandelbrot
{
	
	typedef long double ldouble;

private:

	ldouble real_s = -2.5;
	ldouble imag_s = -2;

	ldouble factor = 4.0;

	int width;
	int height;

	int max_iter = 400;

	int clamp = 0;

	SDL_Renderer* renderer;

	int compute(std::complex<ldouble> c);

public:
	Mandelbrot(int w, int h, SDL_Renderer* renderer);

	SDL_Texture* draw();

	void update(int x, int y, int size);

};

