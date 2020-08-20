#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sqlite3.h>
#include "Test.h"

int main(int argv, char** args)
{
    using std::cout;
    using std::endl;
    using std::string;
    using std::ifstream;

    //Test for assets
    string line;
    ifstream test_asset ("assets/test.txt");
    if (test_asset.is_open()) {
        while ( getline (test_asset,line) ) {
            cout << line << endl;
        }
        test_asset.close();
    }
    else cout << "Unable to open file"; 

    //Test for local headers
    test_function();

    //Test for sqlite3
    cout << "Sqlite3: " << sqlite3_libversion() << endl;

    //Test for SDL2
    cout << "Initializing SDL..." << endl;
    auto SDL_Init_Error = SDL_Init(SDL_INIT_VIDEO);
    if (SDL_Init_Error != 0) {
        cout << "SDL_Init Error: " << 
        SDL_GetError() << endl;
        return 0;
    }
    cout << "Done!" << endl;
    return 0;
}