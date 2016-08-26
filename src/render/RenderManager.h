/*
 * Copyright (c) 2016 Dariusz Stojaczyk. All Rights Reserved.
 * The following source code is released under an MIT-style license,
 * that can be found in the LICENSE file.
 */

#ifndef C003_RENDER_RENDERMANAGER_H
#define C003_RENDER_RENDERMANAGER_H
#pragma once

#define GLM_FORCE_RADIANS
#define _USE_MATH_DEFINES
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <map>

#include "opengl.h"
#include "util/os.h"
#include "ApplicationContext.h"
#include "render/RenderContext.h"
#include "render/texture/Atlas.h"
#include "render/window/WindowRender.h"

#ifdef USES_SDL
#include <SDL2/SDL.h>
#endif // USES_SDL

/**
 * Main entry point of the rendering.
 * This class is only referenced in Application.
 * To control the state from within e.g. window renders, see RenderContext.
 */
class RenderManager {
public:
    /**
     * The constructor.
     * @param applicationContext context to bind to this RenderManager
     */
    RenderManager(ApplicationContext &applicationContext);
    bool init();
    void switchWindow(Window &window);
    void reload();
    void resize(uint32_t width, uint32_t height);
    void render();
    ~RenderManager();

private:
    bool initWindow();
    bool initGL();
    bool initRenders();

#ifdef USES_SDL
    SDL_Window *gWindow = nullptr;
    SDL_GLContext gContext;
#endif // USES_SDL

    Window *m_currentWindow = nullptr;
    WindowRender *m_windowRender = nullptr;

    ApplicationContext &m_applicationContext;
    RenderContext m_renderContext;

    std::vector<std::unique_ptr<WindowRender>> windowRenders;
};

#endif //C003_RENDER_RENDERMANAGER_H
