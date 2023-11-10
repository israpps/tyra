/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Wellington Carvalho <wellcoj@gmail.com>
*/

#pragma once

#include <stddef.h>
#include "time/timer.hpp"
#include "./version.hpp"

#define LOGGING_STDOUT (0)
#define LOGGING_FILE   (1)
#define LOGGING_EESIO  (3)

namespace Tyra {

class Info {
 public:
  Info();
  ~Info();

  Version version;

  static int loggingMode;

  /** Called by engine */
  void update();

  const unsigned int& getFps() const { return fps; };

  /** @return Available RAM in MB */
  float getAvailableRAM();

 private:
  float calcFps();
  void* allocateLargestFreeRAMBlock(size_t* size);
  size_t getFreeRAMSize();

  unsigned char fpsDelayer;
  unsigned int fps;
  Timer timer;
};

}  // namespace Tyra
