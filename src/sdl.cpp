/***************************************************************************
 *   Copyright (C) 2009-2013 by Veselin Georgiev, Slavomir Kaslev et al    *
 *   admin@raytracing-bg.net                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <SDL2/SDL.h>
#include <stdio.h>
#include "sdl.h"
#include <iostream>
using namespace std;


//SDL_Surface* screen = NULL;
SDL_Window* screen;
SDL_Renderer* renderer;


/// try to create a frame window with the given dimensions
bool initGraphics(int frameWidth, int frameHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Cannot initialize SDL: %s\n", SDL_GetError());
		return false;
	}
	//screen = SDL_SetVideoMode(frameWidth, frameHeight, 32, 0);
//	screen = SDL_CreateWindow("My VFB Window",
//                                SDL_WINDOWPOS_UNDEFINED,
//                                SDL_WINDOWPOS_UNDEFINED,
//                                frameWidth, frameHeight,
//                                SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);


    SDL_CreateWindowAndRenderer(frameWidth, frameHeight, SDL_WINDOW_SHOWN, &screen, &renderer );



	if (!screen) {
		printf("Cannot set video mode %dx%d - %s\n", frameWidth, frameHeight, SDL_GetError());
		return false;
	}
	return true;
}

/// closes SDL graphics
void closeGraphics(void)
{
	SDL_Quit();
}

/// displays a VFB (virtual frame buffer) to the real framebuffer, with the necessary color clipping
//void displayVFB(Color vfb[VFB_MAX_SIZE][VFB_MAX_SIZE])
//{
//	int rs = screen->format->Rshift;
//	int gs = screen->format->Gshift;
//	int bs = screen->format->Bshift;
//	for (int y = 0; y < screen->h; y++) {
//		Uint32 *row = (Uint32*) ((Uint8*) screen->pixels + y * screen->pitch);
//		for (int x = 0; x < screen->w; x++)
//			row[x] = vfb[y][x].toRGB32(rs, gs, bs);
//	}
//	SDL_Flip(screen);
//}

void displayVFBB(void)
{
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    // Show the window
//    SDL_RenderPresent( renderer );

    for ( int y=0; y<480; y++)
    {
        for (int x=0; x<640; x++)
        {
            //set the color of the pixel. The color is first converted to 0..1 range, and then multiplied to 255 to convert it to 0..255 range
            SDL_SetRenderDrawColor(renderer, (x/640.0)*255, (y/480.0)*255, 0, 255);
            //draw the pixel over the window/screen
            SDL_RenderDrawPoint(renderer, x, y);

        }
    }

    SDL_RenderPresent( renderer );
}



/// waits the user to indicate he wants to close the application (by either clicking on the "X" of the window,
/// or by pressing ESC)
void waitForUserExit(void)
{
	SDL_Event ev;
	while (1) {
		while (SDL_WaitEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT:
					return;
				case SDL_KEYDOWN:
				{
					switch (ev.key.keysym.sym) {
						case SDLK_ESCAPE:
							return;
						default:
							break;
					}
				}
				default:
					break;
			}
		}
	}
}


// returns the frame width
int frameWidth(void)
{
	if (screen) return SDL_GetWindowSurface(screen)->w;
	return 0;
}

//int frameHeight(void)
int frameHeight(void)
{
	if (screen) return SDL_GetWindowSurface(screen)->h;
	return 0;
}



//int main(int argv, char** args)
//{
//    initGraphics(200, 400);
//    cout << "Hello World!";
//    cout << "I am learning C++";
//    cout << "\n" << frameWidth() << " " << frameHeight() << "\n";
//    return 0;
//}
