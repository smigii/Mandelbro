#include "Mandelbrot.h"
#include "helpers.h"
#include <iostream>

Mandelbrot::Mandelbrot(int w, int h, SDL_Renderer* renderer)
	: width{ w }, height{ h }, renderer{renderer}
{

}

SDL_Texture* Mandelbrot::draw()
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, width, height);
	Uint32* pixels = new Uint32[width * height];

	ldouble real_f = real_s + factor;
	ldouble imag_f = imag_s + factor;

	for (int x = 0; x < width; x++) {

		ldouble excess = (width - height) / 2;
		ldouble y_min = -excess;
		ldouble y_max = height + excess;
		for (int y = 0; y < height; y++) {

			ldouble imag = map(y, -excess, height + excess, imag_s, imag_f);
			ldouble real = map(x, 0, width, real_s, real_f);

			Uint32 n = compute(std::complex<ldouble>(real, imag));

			Uint32 bright = (n == max_iter) ? 0 : map(n, 0, max_iter, 0, 255);
			//bright = (bright < clamp) ? 0 : bright;

			Uint32 r = map(pow(bright, 2), 0, 6502, 0, 255);
			Uint32 g = bright;
			Uint32 b = map(sqrt(bright), 0, sqrt(255), 0, 255);

			Uint32 color = 255; // First channel, opacity.
			color <<= 8;
			color |= r;
			color <<= 8;
			color |= g;
			color <<= 8;
			color |= b;

			pixels[y * width + x] = color;// (r << 16) | (g << 8) | (b);
		
		}
	}
	SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(Uint32));
	return texture;
	
}

int Mandelbrot::compute(std::complex<ldouble> c)
{
	std::complex<ldouble> z = 0;
	int n = 0;

	while (abs(z) <= 2 && n < max_iter) {
		z = z * z + c;
		n++;
	}

	return n;
}

/*
void Mandelbrot::set_real_s(ldouble val)
{
	real_s = val;
}

void Mandelbrot::set_imag_s(ldouble val)
{
	imag_s = val;
}

void Mandelbrot::set_factor(ldouble val)
{
	factor = val;
}
*/

void Mandelbrot::update(int x, int y, int size)
{
	real_s = map(x, 0, width, real_s, real_s + factor);

	ldouble excess = (width - height) / 2;
	ldouble y_min = -excess;
	ldouble y_max = height + excess;
	imag_s = map(y, y_min, y_max, imag_s, imag_s + factor);

	factor *= ((ldouble)size / (ldouble)width);

}