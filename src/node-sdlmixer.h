#ifndef NODE_SDLMIXER_H
#define NODE_SDLMIXER_H

#include <v8.h>
#include <node.h>

#include <deque>
#include <vector>

#include "SDL.h"
#include "SDL_mixer.h"

#include <pthread.h>
#ifdef UV_VERSION_MAJOR
#include "async_uv.h"
#else
#include "async_ev.h"
#endif

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

class SDLMixer: public ObjectWrap {
public:
	static Persistent<FunctionTemplate> constructor_template;

	static void Initialize(Handle<Object> target);

	typedef Async<playInfo, SDLMixer> AsyncPlayDone;
protected:

	static Handle<Value> Play(const Arguments& args);

	static void ChannelFinished(int channel);
	static void PlayDoneCallback(SDLMixer *sm, playInfo *pi);

	static Handle<Value> New(const Arguments& args);

	SDLMixer();
	~SDLMixer();

private:
	static AsyncPlayDone *playDoneEvent;

	static vector<playInfo *> playInfoChannelList;
};

} // namespace node_sdlmixer
#endif // NODE_SDLMIXER_H
