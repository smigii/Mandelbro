#pragma once

#include <SDL.h>
#include <complex>

class Mandelbrot
{
	
	typedef long double ldouble;

private:
	ldouble REAL_S = -2;
	ldouble REAL_F = 2;
	ldouble IMAG_S = -2;
	ldouble IMAG_F = 2;
	ldouble FACTOR = 0.5;

	int width;
	int height;

	int max_iter = 200;

	int clamp = 0;

	SDL_Renderer* renderer;

	int compute(std::complex<ldouble> c);

public:
	Mandelbrot(int w, int h, SDL_Renderer* renderer);

	void draw();

};

