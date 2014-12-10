#pragma once
#include "GeKo_Graphics/Defs.h"
#include <fstream>

class Debugger{
public:
  Debugger();
  ~Debugger();
  void setDebugCallback();
  void setDebugCallback(GLDEBUGPROC debugCallback);
protected:
  void checkDebugMode();
};
