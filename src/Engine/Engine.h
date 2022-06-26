#pragma once

#include <iostream>

namespace Cinder
{
  class Engine
  {
  protected:
  public:
    Engine();
    virtual ~Engine();

    // Core
    void run();
  };

} // namespace Cinder
