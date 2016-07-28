//
// Created by dar on 1/23/16.
//

#ifndef C003_APPLICATION_H
#define C003_APPLICATION_H

#include <memory>
#include <window/Window.h>
#include "core/Timer.h"
#include "core/input/InputManager.h"
#include "os.h"
#include "render/RenderManager.h"
#include "ApplicationContext.h"

class Application {

public:
    Application();
    void reinit();
    void run();
    void update(bool dynamic);
    void resize(int width, int height);
    void handleClick(int i, int action, float x, float y);
    bool isRunning() const;

private:
    bool m_running = true;
    ApplicationContext m_context;
    std::unique_ptr<Window> m_window;
    RenderManager m_renderer;
    Input::InputManager m_inputManager;
    Timer m_timer;
    double m_deltaTimeHistory[15];
    double m_averageDeltaTime = 0;
    unsigned long long m_ticks = 0;
    std::unique_ptr<Window> m_newWindow;

#ifndef __DEFMOBILE__
    SDL_Event m_sdlEvent;
#endif //__DEFMOBILE__

    void handleEvents();
    void switchWindow();

    friend class ApplicationContext;

    void onQuit();
};

#endif //C003_APPLICATION_H
