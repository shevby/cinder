#pragma once

#include <iostream>
#include <memory>

#include "Scene.h"

namespace Cinder
{
  class Engine
  {
  protected:
  std::shared_ptr<sf::RenderWindow> window;

  void init();


  public:
    Engine();
    virtual ~Engine();

    // Core
    void run();
  };

} // namespace Cinder
