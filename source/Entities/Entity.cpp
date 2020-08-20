#include "../Entity.hpp"

//define DEBUG_COLLISION true

bool Entity::Collision(SDL_Rect* tester) {
    int tester_off_x = tester->x + tester->w;
    int tester_off_y = tester->y + tester->h;
    int this_off_x = this->x + this->w;
    int this_off_y = this->y + this->h;
#ifdef DEBUG_COLLISION
    int type_int = this->Message(ASK_ENT_TYPE);
    const char *type_name;
    switch(type_int) {
        case ENT_TYPE_PLATFORM:
            type_name = "Platform";
            break;
        case ENT_TYPE_RANCH:
            type_name = "Ranch";
            break;
        case ENT_TYPE_CRATE:
            type_name = "Crate";
            break;
        default:
            type_name = "Default";
            break;
    }
    std::cout << std::endl << 
        "Collision test debug message: " << 
        std::endl << 
        "Tester:" << 
        std::endl << 
        "\t" << "X:" << tester->x << " Y:" << tester->y << 
        std::endl << 
        "\t" << "XO:" << tester_off_x << " YO:" << tester_off_y << 
        std::endl << 
        type_name << std::endl << 
        "\t" << "X:" << this->x << " Y:" << this->y << 
        std::endl << 
        "\t" << "XO:" << this_off_x << " YO:" << this_off_y << 
        std::endl;
#endif
    if ((this->x < tester_off_x && this_off_x > tester->x) && 
    (this->y < tester_off_y && this_off_y > tester->y)) 
    {
#ifdef DEBUG_COLLISION
        std::cout << ">**BANG**<" << std::endl;
#endif
        return true;
    } else {
#ifdef DEBUG_COLLISION
        std::cout << "--~whif~--" << std::endl;
#endif
        return false;
    };
}

SDL_Rect Entity::Box(){
    SDL_Rect value;
    value.x = this->x;
    value.y = this->y;
    value.w = this->w;
    value.h = this->h;
    return value;
}