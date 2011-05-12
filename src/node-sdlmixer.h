#ifndef NODE_SDLMIXER_H
#define NODE_SDLMIXER_H

#include <v8.h>
#include <node.h>

#include <deque>

#include "SDL.h"
#include "SDL_mixer.h"

using namespace v8;
using namespace node;
using namespace std;

namespace node_sdlmixer {

struct playInfo {
  Persistent<Function> cb;
  int doCallback;
  int channel;
  Mix_Chunk *wave;
  char name[1]; // should be last one in the struct
};


};

#endif
