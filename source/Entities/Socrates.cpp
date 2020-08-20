#include "../Entity.hpp"

int Socrates::reference_count = 0;
SDL_Texture* Socrates::texture = NULL;

void Socrates::Tick(uint32_t time_delta) {
    if (this->vy > this->terminal_velocity)// terminal_velocity is negative
        this->vy = this->vy - 5;
    if ((SDL_GetTicks() - this->dash_time) < this->dash_length)
        this->vy = 0;
    if (this->floored == false)
        this->y = this->y - this->vy;
    return;
}
int Socrates::Message(int message) {
    switch(message){
    case ASK_ENT_TYPE:
        return ENT_TYPE_SOCRATES;
        break;
    case MSG_SOCRATES_JUMP:
        if (this->jump_capacity > 0) {
            this->vy = 60;
            this->dash_time = 0;
            this->floored = false;
            this->dash_capacity = this->dash_capacity + 1;
            this->jump_capacity = this->jump_capacity - 1;
        }
        return 0;
        break;
    case MSG_SOCRATES_DASH:
        if (this->dash_capacity > 0) {
            dash_time = SDL_GetTicks();
            this->dash_capacity = this->dash_capacity - 1;
            this->jump_capacity = this->jump_capacity + 1;
        }
        return 0;
        break;
    case COL_SOCRATES_FLOOR:
        this->floored = true;
        this->vy = 0;
        this->y = (576 - 50) - this->h;
        this->dash_capacity = 3;
        this->jump_capacity = 3;
        return 0;
        break;
    case COL_SOCRATES_FALLING:
        this->floored = false;
        return 0;
        break;
    case ASK_SOCRATES_VELOCITY:
        return this->vy;
        break;
    default:
        return -1;
        break;
    }
}
void Socrates::Draw(SDL_Renderer* renderer) {
    SDL_Rect my_rect = this->Box();
    SDL_SetRenderDrawColor(renderer, 200,200,200,255);
    if ((SDL_GetTicks() - this->dash_time) < this->dash_length)
        SDL_SetRenderDrawColor(renderer, 190,190,255,255);
    SDL_RenderFillRect(renderer, &my_rect);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
}