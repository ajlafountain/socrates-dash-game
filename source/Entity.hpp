#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef ENTITY_HPP
#define ENTITY_HPP

#define ENTITY_WORLD_SPEED 18
class Entity {
    protected:
        int x,y,w,h,z;
    public:
        Entity(int x, int y, int w, int h, int z){
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
            this->z = z;
        };
        virtual void Tick(uint32_t time_delta) = 0;
        virtual void Draw(SDL_Renderer* renderer) = 0;
        virtual int Message(int message) = 0;


        int Z(){return z;};
        SDL_Rect Box();
        bool Collision(SDL_Rect* tester);
};
// All entities must implement an answer for ASK_ENT_TYPE
#define ASK_ENT_TYPE -1
#define ENT_TYPE_FRAME 0
#define ENT_TYPE_TEXT 1
#define ENT_TYPE_BUTTON 2
#define ENT_TYPE_IMAGE 3
#define ENT_TYPE_PLATFORM 4
#define ENT_TYPE_SOCRATES 5
#define ENT_TYPE_RANCH 6
#define ENT_TYPE_CRATE 7

class Frame: public Entity {
    protected:
        static int reference_count;
        static SDL_Texture *texture;
    public:
        Frame(
            SDL_Renderer*   renderer, 
            int             x,
            int             y,
            int             w,
            int             h,
            int             z):
            Entity(x,y,w,h,z) {
            if (this->reference_count == 0) {
                SDL_Surface* tmp_surface = IMG_Load("assets/frame.png");
                this->texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
                SDL_FreeSurface(tmp_surface);
            }
            this->reference_count = this->reference_count + 1;
        };
        ~Frame(){
            if (this->reference_count == 1){
                SDL_DestroyTexture(texture);
            }
            this->reference_count = this->reference_count - 1;
        };
        int Message(int message) override;
        void Tick(uint32_t time_delta) override;
        void Draw(SDL_Renderer* renderer) override;
};

class Text: public Entity {
    protected:
        static int reference_count;
        static TTF_Font* font;
        SDL_Texture* rendered;
        const char* text;
        int natural_w, natural_h;
    public:
        Text(
            SDL_Renderer*   renderer,
            const char*     text,
            int             x,
            int             y,
            int             w,
            int             h,
            int             z): 
        Entity(x,y,w,h,z) {
            if (reference_count == 0) {
                std::cout << "Loading assets on first instance..." << std::endl;
                this->font = TTF_OpenFont("assets/Kenney Blocks.ttf", 80);
                if(!this->font) {
                    std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
                    exit(1);
                }
                std::cout << "Font: Kenney Pixel.ttf loaded..." << std::endl;
            }
            this->text = text;
            SDL_Surface* tmp_surface;
            SDL_Color color;
            color.r = 0;
            color.g = 0;
            color.b = 0;
            color.a = 255;
            tmp_surface = TTF_RenderUTF8_Blended(font, this->text, color);
            this->natural_w = tmp_surface->w;
            this->natural_h = tmp_surface->h;
            this->rendered = SDL_CreateTextureFromSurface(renderer, tmp_surface);
            this->reference_count = this->reference_count + 1;
        };
        ~Text() {
            if (this->reference_count == 1) {
                TTF_CloseFont(font);
            }
            SDL_DestroyTexture(rendered);
            this->reference_count = this->reference_count - 1;
        }
        int Message(int message) override;
        void Tick(uint32_t time_delta) override {return;};
        void Draw(SDL_Renderer* renderer) override;
};

class Button: public Entity {
    protected:
        static int reference_count;
        static SDL_Texture* texture;
        static SDL_Texture* unchecked_box;
        static SDL_Texture* checked_box;
        static TTF_Font* font;
        SDL_Texture* rendered_text;
        const char* text;
        int text_natural_w, text_natural_h;
        bool selected;
    public:
        Button(
            SDL_Renderer*   renderer, 
            const char*     text,
            int             x,
            int             y,
            int             w,
            int             h,
            int             z):
            Entity(x,y,w,h,z) {
            if (reference_count == 0) {
                SDL_Surface* tmp_surface_one;
                tmp_surface_one = IMG_Load("assets/button.png");
                this->texture = SDL_CreateTextureFromSurface(renderer, tmp_surface_one);
                SDL_FreeSurface(tmp_surface_one);
                tmp_surface_one = IMG_Load("assets/grey_box.png");
                this->unchecked_box = SDL_CreateTextureFromSurface(renderer, tmp_surface_one);
                SDL_FreeSurface(tmp_surface_one);
                tmp_surface_one = IMG_Load("assets/blue_boxCheckmark.png");
                this->checked_box = SDL_CreateTextureFromSurface(renderer, tmp_surface_one);
                SDL_FreeSurface(tmp_surface_one);
                
                this->font = TTF_OpenFont("assets/Kenney Pixel.ttf", 80);
            }
            SDL_Surface* tmp_surface_two;

            SDL_Color color;
            this->selected = false;
            this->text = text;
            color.r = 0;
            color.g = 0;
            color.b = 0;
            color.a = 255;
            tmp_surface_two = TTF_RenderUTF8_Blended(font, this->text, color);
            this->text_natural_w = tmp_surface_two->w;
            this->text_natural_h = tmp_surface_two->h;
            this->rendered_text = SDL_CreateTextureFromSurface(renderer, tmp_surface_two);
            SDL_FreeSurface(tmp_surface_two);
            this->reference_count = this->reference_count + 1;
        };
        ~Button(){
            if (reference_count == 1){
                SDL_DestroyTexture(texture);
                TTF_CloseFont(font);
            }
            SDL_DestroyTexture(rendered_text);
            reference_count = reference_count - 1;
        };
        int Message(int message) override;
        void Draw(SDL_Renderer* renderer) override;
        void Tick(uint32_t time_delta) override;

};
#define MSG_BUTTON_SELECT 0
#define MSG_BUTTON_UNSELECT 1
#define ASK_BUTTON_IS_SELECTED 2

class Image: public Entity {
    protected:;
        SDL_Texture* texture;
    public:
        Image(SDL_Renderer* renderer,
            const char* image_path,
            int x, int y, int w, int h, int z):
            Entity(x,y,w,h,z) {
                SDL_Surface* tmp_surface = IMG_Load(image_path);
                this->texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
                SDL_FreeSurface(tmp_surface);
        };
        ~Image(){
            SDL_DestroyTexture(this->texture);
        };
        void Draw(SDL_Renderer* renderer) {
            SDL_Rect target_rect = this->Box();
            SDL_RenderCopy(renderer, texture, NULL, &target_rect);
        }
        void Tick(uint32_t time_delta) override {return;};
        int Message(int message) override {
            switch(message) {
            case ASK_ENT_TYPE:
                    return ENT_TYPE_IMAGE;
                    break;
            default:
                return -1;
            }
        };
};

class Platform: public Entity {
    protected:
        static int reference_count;
        static SDL_Texture* texture;
    public:
        Platform(SDL_Renderer *renderer,
        int x,
        int y,
        int w,
        int h,
        int z): Entity(x,y,w,h,z) {
            this->reference_count = this->reference_count + 1;

        };
        int Message(int message) override;
        void Tick(uint32_t time_delta) override;
        void Draw(SDL_Renderer* renderer) override;
        ~Platform(){
            this->reference_count = this->reference_count - 1;
        };

};

// class Ranch: public Entity {
// };

class Socrates: public Entity {
    protected:
        static int reference_count;
        static SDL_Texture* texture;
        uint32_t dash_length; //milliseconds
        uint32_t dash_time;
        int jump_capacity;
        int dash_capacity;
        int terminal_velocity;
        int vy;
        bool floored;
    public:
        Socrates(SDL_Renderer *renderer,
        int x,
        int y,
        int w,
        int h,
        int z): Entity(x,y,w,h,z) {
            this->reference_count = this->reference_count + 1;
            this->vy = 30;
            this->terminal_velocity = -25;
            this->jump_capacity = 3;
            this->dash_length = 300;
            this->dash_capacity = 3;
            this->floored = false;
        };
        ~Socrates(){
            this->reference_count = this->reference_count - 1;
        }
        int Message(int message) override;
        void Draw(SDL_Renderer* renderer) override;
        void Tick(uint32_t time_delta) override;
};
#define MSG_SOCRATES_JUMP 0
#define MSG_SOCRATES_DASH 1
#define MSG_SOCRATES_WIN 2
#define MSG_SOCRATES_LOSE 3
#define COL_SOCRATES_FLOOR 4
#define COL_SOCRATES_RANCH 5
#define ASK_SOCRATES_VELOCITY 6
#define COL_SOCRATES_FALLING 7
#define ASK_SOCRATES_DASH 8
#define COL_SOCRATES_CRATE 9

class Ranch: public Entity {
    protected:
        static int reference_count;
        bool collided;
    public:
        Ranch(int x,int y): Entity(x,y,64,64,1) {
            this->reference_count = this->reference_count + 1;
            this->collided = false;
        };
        ~Ranch(){
            this->reference_count = this->reference_count - 1;
        };
        void Tick(uint32_t time_delta) override;
        int Message(int message) override;
        void Draw(SDL_Renderer* renderer) override;
};
#define COL_RANCH_SOCRATES 0

class Crate: public Entity {
    protected:
        static int reference_count;
        bool collided;
    public:
        Crate(int x,int y): Entity(x,y,64,64,1) {
            this->reference_count = this->reference_count + 1;
            this->collided = false;
        };
        ~Crate(){
            this->reference_count = this->reference_count - 1;
        };
        void Tick(uint32_t time_delta) override;
        int Message(int message) override;
        void Draw(SDL_Renderer* renderer) override;
};
#define COL_CRATE_SOCRATES 0
#endif