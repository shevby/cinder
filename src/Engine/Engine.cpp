#include "Engine.h"

void Cinder::Engine::init()
{
  this->dt = 0.f;

  auto winSettings = this->initWindow();

  this->window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode(winSettings.width, winSettings.height),
      winSettings.title);

  this->window->setFramerateLimit(winSettings.fpsLimit);
  this->window->setVerticalSyncEnabled(winSettings.vsync);
}

Cinder::Engine::Engine()
{
  this->init();
}

Cinder::Engine::~Engine()
{
}

void Cinder::Engine::updateDt() {
  this->dt = this->dtClock.restart().asSeconds();
}

void Cinder::Engine::run()
{
  while (window->isOpen())
  {
    this->updateDt();
  }
}

