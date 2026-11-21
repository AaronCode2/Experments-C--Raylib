#include "hot_reload.hpp"

HotLibraryMaintainer HotReload::maintainer = HotLibraryMaintainer("libexample.dll");

bool HotReload::closeLib = false;
bool HotReload::shouldReloadLib = false;

bool HotReload::isLibClosed = false;


void (*HotReload::log)() = nullptr;

void HotReload::init() {

    // maintainer = HotLibraryMaintainer("libexample.dll");

    maintainer.addSymbol("logger");

    assert(!maintainer.loadSymbols());

    // Idkh this works. C++ querks

    log = reinterpret_cast<void (*)()>(maintainer.getSymbolPointer("logger"));

    Terminal::log("Inited DLL Maintanier, check logs for errors");
}

void HotReload::reload() {

    maintainer.reloadLibrary();

    log = reinterpret_cast<void (*)()>(maintainer.getSymbolPointer("logger"));

    Terminal::log("Library Reloaded, can't be complied now! Please Resume Processes");

    shouldReloadLib = false;
}

void HotReload::close() {

    // checks if already closed, doing muliple times causes problems

    if(isLibClosed)
        return;

    maintainer.releaseLibrary();

    Terminal::log("closing Library, can be compiled now.");

    isLibClosed = true;
}

void HotReload::updateStatus() {

    if(closeLib)
        close();
    else if(!closeLib && isLibClosed)
        isLibClosed = false;

    if(shouldReloadLib)
        reload();
}
