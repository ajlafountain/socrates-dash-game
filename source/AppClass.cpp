#include "AppClass.hpp"
#include "Entity.hpp"

App::App() 
{
    tick_rate = 24;
    last_tick = 0;
    // running:
    //  0 = quit
    //  1 = run
    running = TRUE;

    // current_frame
    //  0 start screen
    //  1 play game
    //  2 score screen
    //  3 cutscene
    current_frame = START_FRAME;

    /* SDL setup */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }    
    // SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    // SDL_GL_SetAttribute (SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    // SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_VideoInit(NULL);
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        std::cout 
            << "IMG_Init: Failed to init required jpg and png support!\n" 
            << std::endl
            << "IMG_Init:" << IMG_GetError() 
            << std::endl;
        exit(1);
    }
    if (TTF_Init() < 0) {
        std::cout << "TTF_Init: Failed to init fonts!\n" << std::endl;
        return;
    }

    window = SDL_CreateWindow("Socrates",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
    renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
    /* Renderer? setup */
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_GetRendererOutputSize(renderer, &window_width, &window_height);
    float tmp_eighty_width = static_cast< float >(window_width) * 0.8;
    window_eighty_width = static_cast< int >(floor(tmp_eighty_width + 0.4));
    window_ten_width = static_cast< int >(floor((window_width - window_eighty_width)/ 2));
    
    float tmp_eighty_height = static_cast< float >(window_height) * 0.8;
    window_eighty_height = static_cast< int >(floor(tmp_eighty_height + 0.4));
    window_ten_height = static_cast< int >(floor((window_height - window_eighty_height)/ 2));


    //Set up start screen scene
    std::cout 
        << "Loading scenes..." << std::endl
        << "Loading frame..." << std::endl;
    start_scene.emplace_back(std::unique_ptr<Entity>(
        new Frame(renderer, 
        window_ten_width, 
        window_ten_height, 
        window_eighty_width, 
        window_eighty_height,
        0)));
    std::cout << "Loading text..." << std::endl;
    start_scene.emplace_back(std::unique_ptr<Entity>(
        new Text(renderer,
        "Socrates!",
        window_ten_width + 140,
        window_ten_height + 10,
        window_eighty_width - 160,
        18, 2)));
    std::cout << "Loading button 1..." << std::endl;
    start_scene.emplace_back(std::unique_ptr<Entity>(
        new Button(renderer,
        "Start Game",
        window_ten_width + 60,
        window_ten_height + 120,
        window_eighty_width - 120,
        120,
        1)));
    std::cout << "Loading button 2..." << std::endl;
    start_scene.emplace_back(std::unique_ptr<Entity>(
        new Button(renderer,
        "High Scores",
        window_ten_width + 60,
        window_ten_height + 270,
        window_eighty_width - 120,
        120,
        1)));

    // Set up the game scene
    std::cout << "Loading platform 1..." << std::endl;
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Platform(renderer,
        0,
        this->window_height - 50,
        500,
        50,
        1)));
    std::cout << "Loading platform 2..." << std::endl;
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Platform(renderer,
        600,
        this->window_height - 50,
        450,
        50,
        1)));
    std::cout << "Loading platform 3..." << std::endl;
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Platform(renderer,
        1200,
        this->window_height - 50,
        300,
        50,
        1)));
    std::cout << "Loading Socrates..." << std::endl;
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Socrates(renderer,
        128,
        30,
        64,
        64,
        1)));
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Ranch(20, this->window_height - 128)));
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Ranch(400, this->window_height - 128)));
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Crate(this->window_width + (rand() % 220), this->window_height - 114)));
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Crate(this->window_width + (rand() % 500) + 200, this->window_height - 114)));
    game_scene.emplace_back(std::unique_ptr<Entity>(
        new Crate(this->window_width + (rand() % 600) + 300, this->window_height - 114)));
}

App::~App()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

void
App::Run(void)
{
    while (running != 0) MainLoop();
}