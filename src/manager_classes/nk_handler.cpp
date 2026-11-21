#include "nk_handler.hpp"

NKHandler::~NKHandler() {

    UnloadNuklear(nk);
}

void NKHandler::draw()
{

    DrawNuklear(nk);
}

void NKHandler::update() {

    UpdateNuklear(nk);

    nk_begin(
        nk, "Utils", 
        nk_rect(100, 100, 420, 720), 
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE
    );
    {   
        updateElements();
    }
    nk_end(nk);
}

void NKHandler::updateElements() {

    nk_layout_row_static(nk, 50, 150, 1);

    const char *fpsTypes[] = {

        GET_VAR_NAME(THIRTY_FPS),
        GET_VAR_NAME(SIXTY_FPS),
        GET_VAR_NAME(HUNDRED_AND_TWENTY_FPS),
        GET_VAR_NAME(MAXFPS),
    };

    nk_label(nk, ("FPS: " + Utils::toString(GetFPS())).c_str(), NK_TEXT_CENTERED);

    int temp = (int) Utils::fpsType;
    
    nk_combobox(nk, fpsTypes, 4, &temp, 20, {100, 100});

    if(Utils::fpsType != (FPSTYPE) temp) {
        
        Utils::fpsType = (FPSTYPE) temp;

        switch(Utils::fpsType) {

            case FPSTYPE::THIRTY_FPS:

                SetTargetFPS(30);
                break;

            case FPSTYPE::SIXTY_FPS:
            
                SetTargetFPS(60);
                break;

            case FPSTYPE::HUNDRED_AND_TWENTY_FPS:
            
                SetTargetFPS(120);
                break;

            case FPSTYPE::MAXFPS:
            
                SetTargetFPS(0);
                break;
        }
    }

    nk_label(nk, "RECT", NK_TEXT_LEFT);
    Utils::THE_DEBUG_RECT.x = nk_slide_float(nk, -400, Utils::THE_DEBUG_RECT.x, 400.0f, 1.0f);
    Utils::THE_DEBUG_RECT.y = nk_slide_float(nk, -400, Utils::THE_DEBUG_RECT.y, 400.0f, 1.0f);
    Utils::THE_DEBUG_RECT.width = nk_slide_float(nk, -400, Utils::THE_DEBUG_RECT.width, 400.0f, 1.0f);
    Utils::THE_DEBUG_RECT.height = nk_slide_float(nk, 0, Utils::THE_DEBUG_RECT.height, 400.0f, 1.0f);
    

    nk_label(nk, "VECTOR", NK_TEXT_LEFT);
    Utils::THE_DEBUG_VECTOR.x = nk_slide_float(nk, -400, Utils::THE_DEBUG_VECTOR.x, 400.0f, 1.0f);
    Utils::THE_DEBUG_VECTOR.y = nk_slide_float(nk, -400, Utils::THE_DEBUG_VECTOR.y, 400.0f, 1.0f);

    const char *tileItems[] = {"WALL", "CLOCK", "COUCH", "STAND"};

    nk_combobox(nk, tileItems, 4, &Utils::selectedtileTypeIndex, 20, {100, 100});

    nk_label(nk, "Shaders", NK_TEXT_LEFT);
    Utils::shaderIndex = nk_slide_int(nk, 0, Utils::shaderIndex, sizeof(ShaderIndex), 1);

    // Hacker mode, enables for player to go flying

    nk_checkbox_label(nk, "Hacker Mode", &Utils::hackerMode);


}
