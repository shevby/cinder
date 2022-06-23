#ifndef CONTROLS_H
#define CONTROLS_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <functional>
#include <vector>

struct KeyListener
{
    sf::Keyboard::Key key;
    std::function<void()> callback;
};

struct MouseEvent {
    sf::Vector2i pos;
    bool left = false;
    bool right = false;
    float wheelDelta = 0;
};

struct MouseListener
{
    std::function<void(MouseEvent)> callback;
};

/*!
 * \brief The Controls class
 * provides Observer interface to handle the user input
 */
class Controls
{

sf::Window & window;
std::vector<KeyListener> keyListeners;
std::vector<MouseListener> mouseListeners;

bool leftButtonPressed = false;
bool rightButtonPressed = false;

bool _handleImgui = false;


public:

Controls(sf::Window & w);
/*!
 * \brief listenKeys
 * subscribe to keyboard actions
 * \param key
 * \param callback
 */
void listenKeys(sf::Keyboard::Key key, std::function<void()> callback);
/*!
 * \brief listenMouse
 * subscribe to mouse events
 * \param callback
 */
void listenMouse(std::function<void(MouseEvent)> callback);
void handleImgui();
void exec();


};

#endif // CONTROLS_H
