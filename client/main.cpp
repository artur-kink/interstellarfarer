#include <iostream>
#include <SDL.h>

#include "client.hpp"

using namespace std;
int main(int argc, char** argv){

    Client client;
    cout << "Initializing SDL" << endl;
    if(client.initSDL()){
        cout << "Could not create window: " << SDL_GetError() << endl;
        return 1;
    }

    client.run();

    client.cleanupSDL();

    return 0;
}
