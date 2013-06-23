#include "inputhandler.hpp"

InputHandler* InputHandler::instance = 0;

InputHandler::InputHandler(){
    lastUpdateTime = 0;
    instance = this;
}

InputHandler* InputHandler::I(){
    return instance;
}

void InputHandler::update(unsigned int time){
    lastUpdateTime = time;

    keyState = SDL_GetKeyboardState(0);
    Uint32 buttonState = SDL_GetMouseState(&mouseX, &mouseY);

    if(buttonState&SDL_BUTTON(1)){
        if(!leftDown){
            leftPressed = true;
            if(lastLeftReleasedTime < doubleClickSpeed){
                doubleClick = true;
            }
        }else{
            leftPressed = false;
        }
        leftDown = true;
        lastLeftPressedTime = time;
    }else{
        if(leftDown){
            leftReleased = true;
        }else{
            leftReleased = false;
        }
        leftDown = false;
        lastLeftReleasedTime = time;
    }

    if(buttonState&SDL_BUTTON(3)){
        if(!rightDown){
            rightPressed = true;
        }else{
            rightPressed = false;
        }
        rightDown = true;
        lastRightPressedTime = time;
    }else{
        if(rightDown){
            rightReleased = true;
        }else{
            rightReleased = false;
        }
        rightDown = false;
        lastRightReleasedTime = time;
    }
}

bool InputHandler::isKeyPressed(Uint8 key){
    return keyState[key];
}
