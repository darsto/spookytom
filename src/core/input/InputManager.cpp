//
// Created by dar on 1/28/16.
//

#include "InputManager.h"
#include "window/Window.h"
#include "os.h"
#include "logging.h"

using namespace Input;

InputManager::InputManager() {
    reload();
}

void InputManager::handleClick(int i, TouchPoint::State state, float x, float y) {
    TouchPoint *p = m_touchPoints[i];
    if (p != nullptr && p->m_state == TouchPoint::State::PRESS) {
        if (state == TouchPoint::State::REPEAT) return;
    }
    if (p == nullptr) m_touchPoints[i] = p = new TouchPoint((char) i);
    p->m_x = x;
    p->m_y = y;
    p->m_state = state;
}

#ifdef USES_SDL

void InputManager::handleKeypress(SDL_Event *e) {
    if (e->key.keysym.scancode >= 0 && e->key.keysym.scancode < SDL_NUM_SCANCODES && e->key.repeat == 0) {
        Keypress *key = &m_keypresses[e->key.keysym.scancode];
        key->m_state = (e->type == SDL_KEYDOWN ? Keypress::State::PRESS : Keypress::State::RELEASE);
        if (key->m_state == Keypress::State::PRESS) key->m_pressDelay = 255;
        if (key->m_pressDelay > 0 && e->type == SDL_KEYUP)
            key->m_pressCounter++;
    }
}

#endif // !IS_MOBILE

void InputManager::tick(Window &window) {
    handleTouch(window);

#ifdef USES_KEYBOARD
    handleKeyboard(window);
#endif
}

void InputManager::handleKeyboard(Window &window) {
#ifdef USES_KEYBOARD
    window.handleKeypress(m_keypresses);

    for (int i = 0; i < m_keypresses.size(); i++) {
        if (m_keypresses[i].m_state == Keypress::State::PRESS) {
            m_keypresses[i].m_state = Keypress::State::REPEAT;
        }
    }
#else //USES_KEYBOARD
    Log::warning("Keyboard support is not implemented on your platform");
#endif //__DEFMOBILE__
}

void InputManager::handleTouch(Window &window) {
    for (auto it = m_touchPoints.begin(); it != m_touchPoints.end(); it++) {
        TouchPoint *p = it->second;
        if (p != nullptr) {
            window.handleClick(*p);
        }
    }
}

void InputManager::reload() {
    m_touchPoints.clear();
    for (int i = 0; i < m_keypresses.size(); i++) {
        Keypress *key = &m_keypresses[i];
        key->m_state = Keypress::State::NONE;
        key->m_pressDelay = key->m_pressCounter = 0;
    }
}