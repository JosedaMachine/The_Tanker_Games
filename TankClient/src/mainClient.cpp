#include <unistd.h>
#include <iostream>

#include "Game.h"

void start(){
    // char buffer[256];    
    // getcwd( buffer, 256 );
    // printf("%s\n", buffer);

    Game g;

    g.init(1080, 720);
    g.run();
    g.shutdown();
}

int main(int argc, char *argv[]){
    try {
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