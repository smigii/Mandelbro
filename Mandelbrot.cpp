#include "Mandelbrot.h"
#include "helpers.h"

Mandelbrot::Mandelbrot(int w, int h, SDL_Renderer* renderer)
	: width{ w }, height{ h }, renderer{renderer}
{

}

void Mandelbrot::draw()
{
	for (int x = 0; x < width; x++) {

		ldouble excess = (width - height) / 2;
		ldouble y_min = -excess;
		ldouble y_max = height + excess;
		for (int y = 0; y < height; y++) {

			ldouble imag = map(y, -excess, height + excess, IMAG_S, IMAG_F);
			ldouble real = map(x, 0, width, REAL_S, REAL_F);

			int n = compute(std::complex<ldouble>(real, imag));

			int bright = (n == max_iter) ? 0 : map(n, 0, max_iter, 0, 255);
			//bright = (bright < clamp) ? 0 : bright;

			int r = map(pow(bright, 2), 0, 6502, 0, 255);
			int g = bright;
			int b = map(sqrt(bright), 0, sqrt(255), 0, 255);

			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			SDL_RenderDrawPoint(renderer, x, y);

		}
	}
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