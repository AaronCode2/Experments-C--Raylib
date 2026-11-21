#include "App.hpp"

#if DEBUG_ENABLED

#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"

#endif

// I love Programing! Yeah 

void App::launch() {

    setup();

    Game game;
    game.run();
}

void App::setup() {

// NEVER uses const chars *. those can create bad excepts.

#if ENABLE_RENDERDOC

    RendererDebugger::loadRenderDoc();

#endif

    SetTraceLogLevel(LOG_ERROR);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "Unamed Game");
    Image favicon = LoadImage("../assets/icon/favicon.png");

    // Sometimes it doesn't work don't know why?
    SetWindowIcon(favicon); 
    
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    
    SetTargetFPS(60);
    InitAudioDevice();
    
    UnloadImage(favicon);

    AssetsLoader::load();
    UI::init();
}

