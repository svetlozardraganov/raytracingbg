#include <exception>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
using namespace std;

int vfb_width = 640;
int vfb_height = 480;


class InitError : public std::exception
{
    std::string msg;
public:
    InitError();
    InitError( const std::string & );
    virtual ~InitError() throw();
    virtual const char * what() const throw();
};

InitError::InitError() :
    exception(),
    msg( SDL_GetError() )
{
}

InitError::InitError( const std::string & m ) :
    exception(),
    msg( m )
{
}

InitError::~InitError() throw()
{
}

const char * InitError::what() const throw()
{
    return msg.c_str();
}

class SDL
{
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
public:
    SDL( Uint32 flags = 0 );
    virtual ~SDL();
    void draw();
};

SDL::SDL( Uint32 flags )
{
    if ( SDL_Init( flags ) != 0 )
        throw InitError();

    if ( SDL_CreateWindowAndRenderer( vfb_width, vfb_height, SDL_WINDOW_SHOWN,
                                      &m_window, &m_renderer ) != 0 )
        throw InitError();
}

SDL::~SDL()
{
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    SDL_Quit();
}

//void SDL::draw()
//{
//    // Clear the window with a black background
//    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
//    SDL_RenderClear( m_renderer );
//
//    // Show the window
//    SDL_RenderPresent( m_renderer );
//
//    int rgb[] = { 203, 203, 203, // Gray
//                  254, 254,  31, // Yellow
//                    0, 255, 255, // Cyan
//                    0, 254,  30, // Green
//                  255,  16, 253, // Magenta
//                  253,   3,   2, // Red
//                   18,  14, 252, // Blue
//                    0,   0,   0  // Black
//                };
//
//    SDL_Rect colorBar;
//    colorBar.x = 0; colorBar.y = 0; colorBar.w = 90; colorBar.h = 480;
//
//    // Render a new color bar every 0.5 seconds
//    for ( int i = 0; i != sizeof rgb / sizeof *rgb; i += 3, colorBar.x += 90 )
//    {
//        SDL_SetRenderDrawColor( m_renderer, rgb[i], rgb[i + 1], rgb[i + 2], 255 );
//        SDL_RenderFillRect( m_renderer, &colorBar );
//        SDL_RenderPresent( m_renderer );
//        SDL_Delay( 500 );
//
//        std::cout << "i=" << i << "\n";
//        std::cout << "rgb[i]=" << rgb[i] << "\n";
//        std::cout << "rgb[i+1]=" << rgb[i+1] << "\n";
//        std::cout << "rgb[i+2]=" << rgb[i+2] << "\n";
//        std::cout << "colorBar.x=" << colorBar.x << "\n";
//        std::cout << "colorBar.y=" << colorBar.y << "\n";
//        std::cout << "colorBar.h=" << colorBar.h << "\n";
//        std::cout << "colorBar.w=" << colorBar.w << "\n";
//        std::cout << "sizeof rgb=" << sizeof rgb << "\n";
//        std::cout << "sizeof *rgb=" << sizeof *rgb << "\n";
//        std::cout << "-------------\n";
//    }
//}



void SDL::draw()
{
    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );

    // Show the window
    SDL_RenderPresent( m_renderer );

    //SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);

    //loop over screen-pixels
    for ( int y=0; y<vfb_height; y++)
    {
        for (int x=0; x<vfb_width; x++)
        {
            //set the color of the pixel. The color is first converted to 0..1 range, and then multiplied to 255 to convert it to 0..255 range
            SDL_SetRenderDrawColor(m_renderer, (x/(float)vfb_width)*255, (y/(float)vfb_height)*255, 0, 255);
            //draw the pixel over the window/screen
            SDL_RenderDrawPoint(m_renderer, x, y);
        }
    }


    SDL_RenderPresent( m_renderer );
    SDL_Delay( 3000 );

}


int main( int argc, char * argv[] )
{

    try
    {
        SDL sdl( SDL_INIT_VIDEO | SDL_INIT_TIMER );
        sdl.draw();

        return 0;
    }
    catch ( const InitError & err )
    {
        std::cerr << "Error while initializing SDL:  "
                  << err.what()
                  << std::endl;
    }

    return 1;
}
