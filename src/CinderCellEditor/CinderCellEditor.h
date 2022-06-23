#ifndef CINDERCELLEDITOR_H
#define CINDERCELLEDITOR_H

#include <vector>
#include <string>
#include <memory>

#include <SFML/Window.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include "Item.h"
#include "CinderMap.h"
#include "Controls.h"
#include "Cursor.h"
#include "Overlay.h"
#include "ResourceManager.h"

#include "constants.h"


#define DRAW_CURSOR_SETTER(TEXTURE) \
    if(ImGui::ImageButton(_resources->textures()[static_cast<int>(TEXTURE)], sf::Vector2f{64, 64})) {\
        _cursor->setCurrentTexture(static_cast<int>(TEXTURE));\
    }\
    ImGui::SameLine();

const uint32_t WIDTH = 1960;
const uint32_t HEIGHT = 1080;

enum class Modes {
    VIEW = 0,
    TO_PNG,
    EDIT
};

const float CAMERA_MOVE_SPEED = 1000;

/*!
 * \brief The CinderCellEditor class
 * entry of the application, which instantiates all modules and connects them
 */
class CinderCellEditor
{
    Modes _mode;
    sf::RenderWindow _window{sf::VideoMode(WIDTH, HEIGHT), "Cinder Cell Editor"};
    sf::View _camera{sf::FloatRect{0.f, 0.f, WIDTH, HEIGHT}};

    Controls _input;
    std::vector<std::shared_ptr<Item>> _items;
    std::vector<sf::Texture> _textures;

    std::shared_ptr<ResourceManager> _resources;

    std::shared_ptr<Cursor> _cursor;
    char * _outputFile;

    float _zoom = 1;

public:

    CinderCellEditor();
    ~CinderCellEditor();

    float deltaTime;

    /*!
     * \brief edit
     * Sets application to the EDIT Mode
     * \param filepath
     * path to the raw map
     */
    void edit(std::string filepath);
    /*!
     * \brief view
     * Sets application to the VIEW Mode
     * \param filepath
     * path to the raw map
     */
    void view(std::string filepath);
    /*!
     * \brief toPng
     * Sets application to the TO_PNG Mode
     * \param filepath
     * path to the raw map
     */
    void toPng(std::string filepath);

    void drawGui();

    /*!
     * \brief exec
     * Starts the main loop and executes it 'till the main window is opened
     * \return
     */
    int exec();

    //controls
    /*!
      * \brief moveUp
      * moves the main view up
      */
     void moveUp();
     /*!
      * \brief moveDown
      * moves the main view down
      */
     void moveDown();
     /*!
      * \brief moveLeft
      * moves the main view left
      */
     void moveLeft();
     /*!
      * \brief moveRight
      * moves the main view right
      */
     void moveRight();
     /*!
      * \brief resetPosition
      * resets position of the main view to {0, 0}
      */
     void resetPosition();
     /*!
      * \brief zoomIn
      * zoom in the map
      */
     void zoomIn();
     /*!
      * \brief zoomOut
      * zoom out the map
      */
     void zoomOut();
     /*!
      * \brief handleMouse
      * Handles and redirects mouse events to the _cursor
      * \param event
      * structure which represents mouse actions
      */
     void handleMouse(MouseEvent event);
     void addOverlay();
     void save();
};

#endif // CINDERCELLEDITOR_H
