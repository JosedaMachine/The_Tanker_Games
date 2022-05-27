#include <unistd.h>


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Game.h"


void start(){
    Game g;

    g.init(1000, 1000);
    g.start();
}

int main(int argc, char *argv[]){

    char buffer[256];    
    getcwd( buffer, 256 );
    printf("%s\n", buffer);

    try{
        start();
    }
    catch(const std::string& e)
    {
        std::cerr << e << '\n';
    }
    catch(const char* e)
    {
        std::cerr << e << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(...)
    {
        std::cerr << "Caught an exception ok unknown type...\n";
    }
    
    return 0;
}