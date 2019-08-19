#include "common/windowmanager.h"

#ifdef _WIN32
    HWND windowsHandler;
#else
    SDL_Window* unixWindow;
#endif

#ifdef _WIN32
    void SetWindowsWindow(HWND w) {
        windowsHandler = w;
    }
#else
    void SetSDLWindow(SDL_Window* w) {
        unixWindow = w;
    }
#endif

void RaiseWindow() {
    // Below code is disabled to prevent any bugs from popping up.
    // This is part of the overlay and has not been tested very well yet...
    #ifdef _WIN32
        // This is Windows
        // SetForegroundWindow(windowsHandler);
    #else
        // Unix (like) system which uses SDL
        // SDL_RaiseWindow(unixWindow);
    #endif
}