#include "../Entity.hpp"
int Crate::reference_count = 0;
void Crate::Tick(uint32_t time_delta) {
    this->x = this->x - ENTITY_WORLD_SPEED;
    if ((this->x + this->w) < 0) {
        this->x = 1024 + (rand() % 500);
        this->y = (576 - 114) - rand() % 256;
        this->collided = false;
    }
}
int Crate::Message(int message) {
    switch(message) {
    case ASK_ENT_TYPE:
        return ENT_TYPE_CRATE;
        break;
    case COL_CRATE_SOCRATES:
        if (!this->collided) {
            std::cout << "Crate collision message." << std::endl;
            this->collided = true;
        }
        return 0;
        break;
    default:
        return -1;
        break;
    }
}
void Crate::Draw(SDL_Renderer* renderer) {
    if (this->collided) {
        return;
    }
    SDL_SetRenderDrawColor(renderer, 185,115,45,255);
    SDL_Rect my_rect = this->Box();
    SDL_RenderFillRect(renderer, &my_rect);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}