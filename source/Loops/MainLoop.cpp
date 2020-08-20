#include "../AppClass.hpp"

void
App::MainLoop()
{
    /*
        Perform universal calculations, then pass control to the desired
        loop function
    */
    SDL_GetWindowSize(window, &window_width, &window_height);

    float eighty_percent_width_float = static_cast< float >(window_width) * 0.8;
    int window_eighty_width = static_cast< int >(floor(eighty_percent_width_float + 0.4));
    int window_ten_width = (window_width - window_eighty_width)/2;

    float eighty_percent_height_float = static_cast< float >(window_height) * 0.8;
    int window_eighty_height = static_cast< int >(floor(eighty_percent_height_float + 0.4));
    int window_ten_height = (window_height - window_eighty_height)/2;

    switch(current_frame) 
    {
    case START_FRAME: // Starting Menu
        StartScreenLoop();
        break;
    case PLAY_FRAME: // Gameplay
        GameplayLoop();
        break;/*
    case SCORE_FRAME: // Score screen
        ScoreScreenLoop();
        break;
    case CUTSCENE_FRAME: // Cutscene
        CutsceneLoop();
        break;*/
    default: // Exit?
        running = FALSE;
        break;
    }
}
