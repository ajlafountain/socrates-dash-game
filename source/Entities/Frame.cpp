#include "../Entity.hpp"

int Frame::reference_count = 0;
SDL_Texture *Frame::texture = NULL;


void Frame::Tick(uint32_t time_delta) {return;};
int Frame::Message(int message){
    switch(message){
    case ASK_ENT_TYPE:
        return ENT_TYPE_FRAME;
        break;
    default:
        return -1;
    }
}
void Frame::Draw(SDL_Renderer* renderer) {
    SDL_Rect target_rect = this->Box();
    SDL_RenderCopy(renderer, texture, NULL, &target_rect);
};
