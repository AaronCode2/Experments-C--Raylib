#pragma once
#include "../utility/utils.hpp"
#include "raylib-nuklear.h"
#include "../utility/assets.hpp"

// thirdparty lib

class NKHandler {

    public:

        ~NKHandler();

        void draw();
        void update();
    private:

        nk_context *nk = InitNuklear(FONT_SIZE_FOR_NUK);

        void updateElements();
};