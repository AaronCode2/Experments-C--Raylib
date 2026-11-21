#pragma once



#define HOT_LOGGING_ENABLE
#include "../../libs/reloader/hot_reload.hpp"
#include <assert.h>
#include <iostream>
#include "../utility/utils.hpp"



// Static Struct

struct HotReload {

    public:

        static void init();

        static void reload();
        static void close();

        static void updateStatus();

        static void (*log)();

        static bool closeLib;
        static bool shouldReloadLib;

        static bool isLibClosed;

    private:

        static HotLibraryMaintainer maintainer;


};