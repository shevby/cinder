#include "Engine.h"



void Cinder::Engine::init()
{
  this->window = std::make_shared<sf::RenderWindow>();
}

Cinder::Engine::Engine()
{
  this->init();
}

Cinder::Engine::~Engine()
{
}

void Cinder::Engine::run()
{
  std::cout << "Running...\n";
}
