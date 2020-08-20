#include "../Entity.hpp"

int Text::reference_count = 0;
TTF_Font* Text::font = NULL;
int Text::Message(int message){
    switch(message){
        case ASK_ENT_TYPE:
            return ENT_TYPE_TEXT;
            break;
        default:
            return -1;
            break;
    }
}
void Text::Draw(SDL_Renderer* renderer) {
    SDL_Rect target;
    target.x = this->x;
    target.y = this->y;
    target.w = this->natural_w;
    target.h = this->natural_h;
    SDL_RenderCopy(renderer, rendered, NULL, &target);
}