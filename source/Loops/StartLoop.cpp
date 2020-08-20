#include "../AppClass.hpp"


/*
    START SCREEN LOOP
*/
void
App::StartScreenLoop(void)
{
    static int current_button = 0;

    /* Input */
    while (SDL_PollEvent(&event)) {
        switch(event.type)
        {
        case SDL_QUIT:
            running = FALSE;
            break;
        case SDL_KEYDOWN:
            /*
                notes to help looking through the SDL2 API:

                SDL_Event.SDL_KeyboardEvent.SDL_Keysym.SDL_Keycode
                event     key               keysym     sym
            */
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                std::cout << "UP input recieved!" << std::endl;
                current_button = (current_button + 1) % 2;
                break;
            case SDLK_DOWN:
                std::cout << "DOWN input recieved!" << std::endl;
                current_button = (current_button - 1) % 2;
                if (current_button < 0) {
                    current_button = 0 - current_button;
                } 
                break;
            case SDLK_RETURN:
                std::cout << "RETURN input recieved: " << current_button << std::endl;
                switch(current_button){
                case 0: //Start Game
                    std::cout << "Switch to PLAY_FRAME" << std::endl;
                    current_frame = PLAY_FRAME;
                    break;
                case 1:
                    std::cout << "Switch to SCORE_FRAME" << std::endl;
                    current_frame = SCORE_FRAME;
                    break;
                default:
                    std::cout << "Switch to START_FRAME" << std::endl;
                    current_frame = START_FRAME;
                    break;
                }
                break;
            case SDLK_ESCAPE:
                std::cout 
                    << "ESCAPE input recieved!" << std::endl
                    << "Goodbye!" << std::endl;
                running = FALSE;
                break;
            }
        default:
            //Ignore unhandled events
            break;
        }
    }
    if (current_button == 0) {
        // Select start game
        start_scene[2]->Message(MSG_BUTTON_SELECT);
        start_scene[3]->Message(MSG_BUTTON_UNSELECT);
    } else {
        // Select high score
        start_scene[2]->Message(MSG_BUTTON_UNSELECT);
        start_scene[3]->Message(MSG_BUTTON_SELECT);
    }
    if ((SDL_GetTicks() - last_tick > tick_rate) || (SDL_GetTicks() < tick_rate)) {
        uint32_t time_delta = SDL_GetTicks() - this->last_tick;
        for (auto& entity_ptr: start_scene) {
            entity_ptr->Tick(time_delta);
        }
        this->last_tick = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer,0,180,0,255);
        SDL_RenderClear(renderer);
        for (auto& entity_ptr: start_scene) {
            entity_ptr->Draw(renderer);
        }
        SDL_RenderPresent(renderer);
    }
    // Tick the objects so they know the time_delta...
    // First draw the background elements

}