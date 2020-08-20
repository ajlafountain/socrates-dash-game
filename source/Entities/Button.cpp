#include "../Entity.hpp"

int Button::reference_count = 0;
TTF_Font* Button::font = NULL;
SDL_Texture *Button::texture = NULL;
SDL_Texture *Button::unchecked_box = NULL;
SDL_Texture *Button::checked_box = NULL;

void Button::Draw(SDL_Renderer* renderer) {
    int draw_result = 0;
    SDL_Rect target_rect = this->Box();
    draw_result = SDL_RenderCopy(renderer, texture, NULL, &target_rect);
    if (draw_result != 0) {
        std::cout 
            << "Error drawing: " 
            << SDL_GetError()
            << std::endl;
    }
    target_rect.x = target_rect.x + 10;
    target_rect.y = target_rect.y + 10;
    target_rect.w = target_rect.h - 30;
    target_rect.h = target_rect.h - 30;
    if (this->selected) {
        SDL_RenderCopy(renderer, checked_box, NULL, &target_rect);
    } else {
        SDL_RenderCopy(renderer, unchecked_box, NULL, &target_rect);
    }
    target_rect.x = this->x + ((this->w/2) - (this->text_natural_w/2));
    target_rect.y = this->y + ((this->h/2) - (this->text_natural_h/2)) - 15;
    target_rect.w = this->text_natural_w;
    target_rect.h = this->text_natural_h;
    draw_result = 0;
    draw_result = SDL_RenderCopy(renderer, rendered_text, NULL, &target_rect);
    if (draw_result != 0) {
        std::cout 
            << "Error drawing: " 
            << SDL_GetError()
            << std::endl;
    }
};
void Button::Tick(uint32_t time_delta) {return;};
int Button::Message(int message) {
    switch(message){
    case ASK_ENT_TYPE:
        return ENT_TYPE_BUTTON;
    case MSG_BUTTON_SELECT:
        this->selected = true;
        return 0;
    case MSG_BUTTON_UNSELECT:
        this->selected = false;
        return 0;
    case ASK_BUTTON_IS_SELECTED:
        if (this->selected)
            return 1;
        return 0;
    default:
        return -1;
    }
}