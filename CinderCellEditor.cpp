#include "CinderCellEditor.h"



CinderCellEditor::CinderCellEditor() : _input{_window}
{
    _outputFile = new char[255];

    _resources = ResourceManager::getInstance();

}

CinderCellEditor::~CinderCellEditor()
{
    delete[] _outputFile;
}

void CinderCellEditor::edit(std::string filepath)
{
    _mode = Modes::EDIT;

    for(int i = 0; i < filepath.size(); i++) {
        _outputFile[i] = filepath[i];
    }

    _outputFile[filepath.size()] = '\0';

    _input.handleImgui();

    _items.push_back(std::make_shared<CinderMap>(_window, _textures, filepath));

    _cursor = std::make_shared<Cursor>(_window);
    _cursor->onDrawAreaSelected(std::bind(&CinderCellEditor::addOverlay, this));
    _cursor->mapHeight = dynamic_cast<CinderMap*>(_items[0].get())->height;
    _cursor->mapWidth = dynamic_cast<CinderMap*>(_items[0].get())->width;

    _input.listenKeys(sf::Keyboard::W, std::bind(&CinderCellEditor::moveUp, this));
    _input.listenKeys(sf::Keyboard::S, std::bind(&CinderCellEditor::moveDown, this));
    _input.listenKeys(sf::Keyboard::A, std::bind(&CinderCellEditor::moveLeft, this));
    _input.listenKeys(sf::Keyboard::D, std::bind(&CinderCellEditor::moveRight, this));
    _input.listenKeys(sf::Keyboard::R, std::bind(&CinderCellEditor::resetPosition, this));
    _input.listenKeys(sf::Keyboard::E, std::bind(&CinderCellEditor::zoomIn, this));
    _input.listenKeys(sf::Keyboard::Q, std::bind(&CinderCellEditor::zoomOut, this));
    _input.listenMouse(std::bind(&CinderCellEditor::handleMouse, this, std::placeholders::_1));

}

void CinderCellEditor::view(std::string filepath)
{
    _mode = Modes::VIEW;

    _items.push_back(std::make_shared<CinderMap>(_window, _textures, filepath));

    _input.listenKeys(sf::Keyboard::W, std::bind(&CinderCellEditor::moveUp, this));
    _input.listenKeys(sf::Keyboard::S, std::bind(&CinderCellEditor::moveDown, this));
    _input.listenKeys(sf::Keyboard::A, std::bind(&CinderCellEditor::moveLeft, this));
    _input.listenKeys(sf::Keyboard::D, std::bind(&CinderCellEditor::moveRight, this));
    _input.listenKeys(sf::Keyboard::R, std::bind(&CinderCellEditor::resetPosition, this));
    _input.listenKeys(sf::Keyboard::E, std::bind(&CinderCellEditor::zoomIn, this));
    _input.listenKeys(sf::Keyboard::Q, std::bind(&CinderCellEditor::zoomOut, this));

}

void CinderCellEditor::toPng(std::string filepath)
{
    _mode = Modes::TO_PNG;

    _items.push_back(std::make_shared<CinderMap>(_window, _textures, filepath));

}


int CinderCellEditor::exec()
{
    sf::Clock clock;

    if(_mode == Modes::TO_PNG) {
        return dynamic_cast<CinderMap*>(_items[0].get())->toPng();
    }

    auto avarageFrameRenderTime = 0.f;

    if(_mode == Modes::EDIT) {
        ImGui::SFML::Init(_window);
        ImGui::GetIO().FontGlobalScale = 2;
    }

    while (_window.isOpen()) {
        deltaTime = clock.getElapsedTime().asSeconds();

        _input.exec();

        if(_mode == Modes::EDIT) {
            ImGui::SFML::Update(_window, clock.restart());
        }
        else {
            clock.restart();
        }

        _window.clear();

        for(auto r : _items) {
            r->render();
        }

        if(_mode == Modes::EDIT) {
            _cursor->render();
        }

        _window.setView(_camera);

        if(_mode == Modes::EDIT) {
            drawGui();
            ImGui::SFML::Render(_window);
        }


        _window.display();




//        std::cout << clock.getElapsedTime().asSeconds() << std::endl;

    }

    if(_mode == Modes::EDIT) {
        ImGui::SFML::Shutdown();
    }

    return 0;
}






void CinderCellEditor::drawGui()
{

    ImGui::Begin("Edit");

    DRAW_CURSOR_SETTER(Cinder::Biomes::WATER);
    DRAW_CURSOR_SETTER(Cinder::Biomes::FIELD);
    DRAW_CURSOR_SETTER(Cinder::Biomes::FOREST);
    DRAW_CURSOR_SETTER(Cinder::Biomes::ROCK);
    DRAW_CURSOR_SETTER(Cinder::Biomes::HIGH_ROCK);
    DRAW_CURSOR_SETTER(Cinder::Biomes::GLACIER);
    DRAW_CURSOR_SETTER(Cinder::Biomes::SWAMP);
    DRAW_CURSOR_SETTER(Cinder::Biomes::DESERT);
    DRAW_CURSOR_SETTER(Cinder::Biomes::SAVANNA);

    ImGui::NewLine();

    ImGui::Text("Current:");
    ImGui::SameLine();
    DRAW_CURSOR_SETTER(_cursor->getCurrentTexture());
    ImGui::NewLine();
    
    ImGui::InputText("->output file", _outputFile, 255);
        
    

    if(ImGui::Button("Save")) {
        this->save();
    }

    ImGui::End();
}

void CinderCellEditor::moveUp()
{
    _camera.move(sf::Vector2f(0, -1) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::moveDown()
{
    _camera.move(sf::Vector2f(0, 1) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::moveLeft()
{
    _camera.move(sf::Vector2f(-1, 0) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::moveRight()
{
    _camera.move(sf::Vector2f(1, 0) * deltaTime * CAMERA_MOVE_SPEED * _zoom);
}

void CinderCellEditor::resetPosition()
{
    _camera.setCenter(0, 0);
}

void CinderCellEditor::zoomIn()
{
    if(_zoom < 0.1) {
        return;
    }

    if(_zoom < 0.5) {
        _zoom -= 0.0001;
    }
    else {
        _zoom -= 0.01;
    }

    _camera.setSize(sf::Vector2f(WIDTH, HEIGHT) * _zoom);
}

void CinderCellEditor::zoomOut()
{

    if(_zoom > TILE_HEIGHT) {
        return;
    }

    _zoom += 0.01;
    _camera.setSize(sf::Vector2f(WIDTH, HEIGHT) * _zoom);
}

void CinderCellEditor::handleMouse(MouseEvent event)
{
    if(event.wheelDelta > 0) {
        this->zoomIn();
    }
    else if(event.wheelDelta < 0) {
        this->zoomOut();
    }
    _cursor->handleMouse(event);
}

void CinderCellEditor::addOverlay()
{
    _items.push_back(std::make_shared<Overlay>(*(_cursor.get())));
}

void CinderCellEditor::save()
{
    Cinder::Map map;

    CinderMap* cinderMap = dynamic_cast<CinderMap*>(_items[0].get());

    map.mapType = cinderMap->mapType;
    map.width = cinderMap->width;
    map.height = cinderMap->height;

    map.map.resize(cinderMap->height);

    for(auto & r : map.map) {
        r.resize(cinderMap->width);
    }

    for(auto & item : _items) {
        SaveMap saveMap = item.get()->saveBiom();
        std::cout << saveMap << std::endl;

        for(int y = 0; y < saveMap.height; y++) {
            for(int x = 0; x < saveMap.width; x++) {
                map.map[saveMap.y + y][saveMap.x + x] = saveMap.complex ? saveMap.complexMap[y][x] : saveMap.tile;
            }
        }

    }

    map.save(_outputFile);


}






