#include "../AppClass.hpp"


/*
    GAMEPLAY LOOP
*/
void
App::GameplayLoop(void)
{
    static bool first_run = true;
    static bool pause = true;
    bool socrates_on_floor = false;
    if (first_run) {
        this->last_tick = SDL_GetTicks();
        first_run = false;
    }
    /* Input */
    while (SDL_PollEvent(&event)) {
        switch(event.type)
        {
        case SDL_QUIT:
            running = FALSE;
            break;
        case SDL_KEYDOWN:
            pause = false;

            /*
                notes to help looking through the SDL2 API:

                SDL_Event.SDL_KeyboardEvent.SDL_Keysym.SDL_Keycode
                event     key               keysym     sym
            */
            switch(event.key.keysym.sym)
            {
            case SDLK_UP:
                std::cout << "UP input recieved!" << std::endl;
                game_scene[3]->Message(MSG_SOCRATES_JUMP);
                break;
            case SDLK_DOWN:
                std::cout << "DOWN input recieved!" << std::endl;
                game_scene[3]->Message(MSG_SOCRATES_DASH);
                break;
            case SDLK_RETURN:
                std::cout << "RETURN input recieved!" << std::endl;
                pause = true;
                break;
            case SDLK_ESCAPE:
                std::cout 
                    << "ESCAPE input recieved!" << std::endl
                    << "Goodbye!" << std::endl;
                current_frame = START_FRAME;
                break;
            }
        default:
            //Ignore unhandled events
            break;
        }
    }
    // Tick the elements and then draw them.
    if ((SDL_GetTicks() - last_tick > tick_rate) && !pause) {
        SDL_Rect socs = game_scene[3]->Box();
        socs.h = socs.h - game_scene[3]->Message(ASK_SOCRATES_VELOCITY);

        //Tick the objects
        uint32_t time_delta = SDL_GetTicks() - this->last_tick;
        for (auto& entity_ptr: game_scene) {
            entity_ptr->Tick(time_delta);
        }
        //Collision Check
        for (auto& entity_ptr: game_scene) {
            switch(entity_ptr->Message(ASK_ENT_TYPE)) {
                case ENT_TYPE_PLATFORM:
                    if (entity_ptr->Collision(&socs) == true){
#ifdef DEBUG_COLLISION
                        std::cout << "*!Platform collision" << std::endl;
#endif
                        game_scene[3]->Message(COL_SOCRATES_FLOOR);
                        socrates_on_floor = true;
                    }
                    break;
                case ENT_TYPE_CRATE:
                    if (entity_ptr->Collision(&socs) == true) {
#ifdef DEBUG_COLLISION
                        std::cout << "*!Crate collision" << std::endl;
#endif
                        game_scene[3]->Message(COL_SOCRATES_CRATE);
                        entity_ptr->Message(COL_CRATE_SOCRATES);
                    }
                    break;
                case ENT_TYPE_RANCH:
                    if (entity_ptr->Collision(&socs) == true) {
#ifdef DEBUG_COLLISION
                        std::cout << "*!Ranch collision" << std::endl;
#endif
                        game_scene[3]->Message(COL_SOCRATES_RANCH);
                        entity_ptr->Message(COL_RANCH_SOCRATES);
                    }
                    break;
                default:
                    break;
            }
        }
        if (!socrates_on_floor) {
            game_scene[3]->Message(COL_SOCRATES_FALLING);
        }

        this->last_tick = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer,0,0,120,255);
        SDL_RenderClear(renderer);
        for (auto& entity_ptr: game_scene) {
            entity_ptr->Draw(renderer);
        }
        SDL_RenderPresent(renderer);
    }
    if ((SDL_GetTicks() - last_tick > tick_rate) && pause) {
        SDL_SetRenderDrawColor(renderer,0,0,120,255);
        SDL_RenderClear(renderer);
        for (auto& entity_ptr: game_scene) {
            entity_ptr->Draw(renderer);
        }
        SDL_RenderPresent(renderer);
    }
}