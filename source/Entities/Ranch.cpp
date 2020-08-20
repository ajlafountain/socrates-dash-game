#include "../Entity.hpp"
int Ranch::reference_count = 0;
int Ranch::Message(int message) {
    switch(message){
    case ASK_ENT_TYPE:
        return ENT_TYPE_RANCH;
        break;
    case COL_RANCH_SOCRATES:
        if (!this->collided) {
            std::cout << "Ranch collision message" << std::endl;
            this->collided = true;
        }
        return 0;
        break;
    default:
        return -1;
        break;
    }
}
void Ranch::Tick(uint32_t time_delta) {
    this->x = this->x - ENTITY_WORLD_SPEED;
    if ((this->x + this->w) < 0) {
        this->x = 1024 + (rand() % 500);
        this->collided = false;
    }
    return;
}
void Ranch::Draw(SDL_Renderer* renderer) {
    if (this->collided == true) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 115,115,255,255);
    SDL_Rect my_rect = this->Box();
    SDL_RenderFillRect(renderer, &my_rect);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}