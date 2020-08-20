#include "../Entity.hpp"

int Platform::reference_count = 0;
SDL_Texture* Platform::texture = NULL;
int Platform::Message(int message) {
    switch(message){
    case ASK_ENT_TYPE:
        return ENT_TYPE_PLATFORM;
        break;
    default:
        return -1;
    }
}
void Platform::Tick(uint32_t time_delta) {
    this->x = this->x - ENTITY_WORLD_SPEED;
    if ((this->x + this->w) < 0) {
        this->x = 1024;
    }
}
void Platform::Draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 200,20,20,255);
    SDL_Rect my_rect = this->Box();
    SDL_RenderFillRect(renderer, &my_rect);
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
}