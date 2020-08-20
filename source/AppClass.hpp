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
#include <memory>

#include <SDL2/SDL.h>
// #include <SDL2/SDL_opengles2.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Entity.hpp"

// The include guard make sure we only include this header once.
#ifndef APPCLASS_HPP
#define APPCLASS_HPP

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

// Defined by Nuklear files I started working with, keeping for safety
#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

#define FALSE 0
#define TRUE 1

#define START_FRAME 0
#define PLAY_FRAME 1
#define SCORE_FRAME 2
#define CUTSCENE_FRAME 3



class App {
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event event;
        uint32_t last_tick, tick_rate;
        int window_width, window_height,
            window_eighty_width, window_eighty_height,
            window_ten_width, window_ten_height,
            running, current_frame;
        // running: Initialized to 1
        //  0 = quit
        //  1 = run
        // current_frame
        //  0 start screen
        //  1 play game
        //  2 score screen
        //  3 cutscene

        std::vector<std::unique_ptr<Entity>> 
            start_scene,
            game_scene,
            score_scene;
        void StartScreenLoop(void);
        void GameplayLoop(void);
        // void CutsceneLoop(void);
        // void ScoreScreenLoop(void);

        void MainLoop(void);
    public:
        App();
        ~App();
        void Run(void);
};

#endif