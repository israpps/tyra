/*
# _____        ____   ___
#   |     \/   ____| |___|
#   |     |   |   \  |   |
#-----------------------------------------------------------------------
# Copyright 2022, tyra - https://github.com/h4570/tyra
# Licensed under Apache License 2.0
# Wellington Carvalho <wellcoj@gmail.com>
*/

#include "debug/debug.hpp"


#ifdef EESIO_UART_USE_SIOCOOKIE //alternative wrapper that initializes ee_sio and hooks STDOUT & STDERR into it.
#include <SIOCookie.h>
#define EE_SIO_INITIALIZE() \
  ee_sio_start(38400, 0, 0, 0, 0, 1); \
  printf("TYRA: EE_SIO Enabled & STDOUT/STDERR hooked\n")
#else
#include <sio.h>
#define EE_SIO_INITIALIZE() \
  sio_init(38400, 0, 0, 0, 0); \
  sio_putsn("TYRA: EE_SIO Enabled\n")
#endif

void TyraDebug::writeInLogFile(std::stringstream* ss) {
  std::ofstream logFile;
  logFile.open(Tyra::FileUtils::fromCwd("log.txt"),
               std::ofstream::out | std::ofstream::app);
  logFile << ss->str();
  logFile.flush();
  // logFile.close();
}

static bool isEESIO_inited = false;
void TyraDebug::writeInEESIO(std::stringstream* ss) {
  if (!isEESIO_inited) {
    EE_SIO_INITIALIZE();
    isEESIO_inited = true;
  }
  sio_putsn(ss->str().c_str());
}
