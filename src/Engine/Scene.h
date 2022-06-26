#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

namespace Cinder
{
  class Scene
  {
  protected:
  public:
    Scene();
    virtual ~Scene();
  };
}