#include <SDL2/SDL.h>

int main()
{
	SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    surface = SDL_CreateRGBSurface(0, 1280, 720, 32,
                                   rmask, gmask, bmask, amask);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }

    /* or using the default masks for the depth: */
    surface = SDL_CreateRGBSurface(0, 1280, 720, 32, 0, 0, 0, 0);

	Uint32 var = SDL_MapRGBA(surface->format, 0xAA, 0xBB, 0xCC, 0xDD);

	Uint8 lol = var >> 16;

	printf("0x%x\n", lol);
}

// 0000 0000 0000 0000 0000 0000
