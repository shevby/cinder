#include "Controls.h"

Controls::Controls(sf::Window &w) : window{w}
{

}

void Controls::listenKeys(sf::Keyboard::Key key, std::function<void()> callback)
{
    this->keyListeners.push_back(KeyListener{key, callback});
}

void Controls::listenMouse(std::function<void(MouseEvent)> callback)
{
    this->mouseListeners.push_back(MouseListener{callback});
}

void Controls::handleImgui() 
{
    _handleImgui = true;
}

void Controls::exec()
{
    sf::Event event{};
    MouseEvent mouseEvent{};

    mouseEvent.wheelDelta = 0;

    if (window.pollEvent(event)) {

        if(_handleImgui) {
            ImGui::SFML::ProcessEvent(event);

            if(ImGui::GetIO().WantCaptureMouse) {
                return;
            }
        }

        if(event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        if(event.type == sf::Event::MouseWheelMoved)
        {
            mouseEvent.wheelDelta = event.mouseWheel.delta;
        }

        if(event.type == sf::Event::MouseButtonReleased) {
            mouseEvent.left = leftButtonPressed;
            mouseEvent.right = rightButtonPressed;
            leftButtonPressed = false;
            rightButtonPressed = false;
        }

    }

    if(_handleImgui && ImGui::GetIO().WantCaptureMouse) {
        return;
    }

    leftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    rightButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Right);

    mouseEvent.pos = sf::Mouse::getPosition(window);

    for(auto & listener : keyListeners) {
        if(sf::Keyboard::isKeyPressed(listener.key)) {
            listener.callback();
        }
    }

    for(auto & listener : mouseListeners) {
        listener.callback(mouseEvent);
    }
}

