#pragma once
#include <raylib.h>
#include <iostream>
#include "game.hpp"
#include "utility/assets.hpp"
#include "ui/ui.hpp"
#include "manager_classes/renderer.hpp"
#include "manager_classes/hot_reload.hpp"


// Using ENG-US for stuff
// Use snake_case for files and camelCase for general stuff

namespace App {

    void launch();
    void setup();
    void logInfo();
}