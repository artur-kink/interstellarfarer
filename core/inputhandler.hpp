#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include <SDL_mouse.h>
#include <SDL_keyboard.h>

/**
 * Mouse and keyboard input handler.
 */
class InputHandler{
private:
    unsigned int lastUpdateTime;
    const Uint8* keyState;
    static InputHandler* instance;
public:

    bool leftPressed;
    bool rightPressed;

    bool leftDown;
    bool rightDown;

    bool leftReleased;
    bool rightReleased;

    unsigned int lastLeftPressedTime;
    unsigned int lastRightPressedTime;

    unsigned int lastLeftReleasedTime;
    unsigned int lastRightReleasedTime;

    bool doubleClick;
    unsigned int doubleClickSpeed;

    int mouseX;
    int mouseY;

    int mouseWorldX;
    int mouseWorldY;

    InputHandler();

    static InputHandler* I();

    void update(unsigned int time);
    bool isKeyPressed(Uint8 key);
};

#endif
