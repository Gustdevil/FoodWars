#include <memory>

#include "../../Headers/Input/InputFacade.h"

InputFacade::InputFacade() {
    init();
}

InputFacade::~InputFacade() = default;

void InputFacade::setWindowResolutionCalculator(const WindowResolutionCalculator& windowResCalc) {
    _windowResCalc = &windowResCalc;
}

void InputFacade::init() {
    _keyEventObservable = KeyEventObservable();
    _mouseEventObservable = MouseEventObservable();
    _windowEventObservable = WindowEventObservable();
}

// Polls the key input events
void InputFacade::pollEvents() {
    SDL_Event event;
    //SDL_SetEventFilter(eventFilter);

    SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
    SDL_EventState(SDL_KEYUP, SDL_IGNORE);

    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_MOUSEBUTTONDOWN: { // When a click is registered
                // check if left or right is clicked
                //
                //
                if (event.button.button == SDL_BUTTON_LEFT) {
                    MouseEvent mouseEvent = MouseEvent(
                            _windowResCalc->getConvertedxPosClick(event.motion.x),
                            _windowResCalc->getConvertedyPosClick(event.motion.y), MouseEventType::Down, MouseClickType::Left);
                    _mouseEventObservable.notify(mouseEvent);
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    MouseEvent mouseEvent = MouseEvent(
                            _windowResCalc->getConvertedxPosClick(event.motion.x),
                            _windowResCalc->getConvertedyPosClick(event.motion.y), MouseEventType::Down, MouseClickType::Right);
                    _mouseEventObservable.notify(mouseEvent);
                }
                break;
            }
            case SDL_MOUSEMOTION: {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    MouseEvent mouseEvent = MouseEvent(
                            _windowResCalc->getConvertedxPosClick(event.motion.x),
                            _windowResCalc->getConvertedyPosClick(event.motion.y), MouseEventType::Drag, MouseClickType::Left);
                    _mouseEventObservable.notify(mouseEvent);
                }
                break;
            }
            case SDL_MOUSEBUTTONUP: { // When a click is released
                if (event.button.button == SDL_BUTTON_LEFT) {
                    MouseEvent mouseEvent = MouseEvent(
                            _windowResCalc->getConvertedxPosClick(event.motion.x),
                            _windowResCalc->getConvertedyPosClick(event.motion.y), MouseEventType::Up, MouseClickType::Left);
                    _mouseEventObservable.notify(mouseEvent);
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    MouseEvent mouseEvent = MouseEvent(
                            _windowResCalc->getConvertedxPosClick(event.motion.x),
                            _windowResCalc->getConvertedyPosClick(event.motion.y), MouseEventType::Up, MouseClickType::Right);
                    _mouseEventObservable.notify(mouseEvent);
                }
                break;
            }
            case SDL_QUIT: { // When the window is closed
                WindowEvent windowQuitEvent = WindowEvent(0,0,WindowEventType::Quit);
                _windowEventObservable.notify(windowQuitEvent);
                break;
            }
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED: { // When the window is resized
                        WindowEvent windowResizeEvent = WindowEvent(event.window.data1, event.window.data2, WindowEventType::Resize);
                        _windowEventObservable.notify(windowResizeEvent);
                        break;
                    }
                    default:
                        break;
                }
            default:
                break;
        }
    }
    _keyEventObservable.update();
}

const KeyEventObservable& InputFacade::getKeyEventObservable() const {
    return _keyEventObservable;
}

const MouseEventObservable& InputFacade::getMouseEventObservable() const {
    return _mouseEventObservable;
}

const WindowEventObservable& InputFacade::getWindowEventObservable() const {
    return _windowEventObservable;
}

WindowEventObservable& InputFacade::getWindowEventObservable() {
    return _windowEventObservable;
}

MouseEventObservable& InputFacade::getMouseEventObservable() {
    return _mouseEventObservable;
}

KeyEventObservable& InputFacade::getKeyEventObservable() {
    return _keyEventObservable;
}

int InputFacade::eventFilter(const SDL_Event *event) {
    if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
        return 0;
    return 1;
}
