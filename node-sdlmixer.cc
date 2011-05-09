#include <v8.h>
#include <node.h>
#include "SDL.h"
#include "SDL_mixer.h"

using namespace v8;
using namespace node;

struct playInfo {
  Persistent<Function> cb;
  int doCallback;
  int channel;
  Mix_Chunk *wave;
  char name[1]; // should be last one in the struct
};

static int numChannels = 0;
static int curChannel = 0;

static int still_playing(int channel)
{
  return(Mix_Playing(channel));
}

static int getNextChannel()
{
  int channel = curChannel + 1;
  if (channel == numChannels)
  {
    channel = 0;
  }
  curChannel = channel;
  return channel;
}

static int DoPlay(eio_req *req)
{
  struct playInfo * pi = (struct playInfo *) req->data;

  /* Load the requested wave file */
  printf("Loading %s\n",pi->name);
  pi->wave = Mix_LoadWAV(pi->name);

  printf("Playing on channel[%d]\n", pi->channel);
  /* Play and then exit */
  Mix_PlayChannel(pi->channel, pi->wave, 0);

  while (still_playing(pi->channel)) {
    SDL_Delay(1);

  } /* while still_playing() loop... */
  printf("Done\n");

  Mix_FreeChunk(pi->wave);
  pi->wave = NULL;
  return 0;
}

static int NotifyPlayed(eio_req *req)
{
  HandleScope scope;
  ev_unref(EV_DEFAULT_UC);
  struct playInfo * pi = (struct playInfo *) req->data;

  Local<Value> argv[1];
  argv[0] = Local<Value>::New(Null());

  if (pi->doCallback) {
    TryCatch try_catch;
    pi->cb->Call(Context::GetCurrent()->Global(),1,argv);
    if (try_catch.HasCaught()) {
      FatalException(try_catch);
    }
  }

  pi->cb.Dispose();
  free(pi);
  return 0;
}

static Handle<Value> Play(const Arguments& args) {
  HandleScope scope;

  const char *usage = "usage: play(fileName, <callbackFunc>)";
  // TODO: optional 2nd callbackFunc parameter?
  if (args.Length() < 1) {
    return ThrowException(Exception::Error(String::New(usage)));
  }

  String::Utf8Value fileName(args[0]);
  Local<Function> cb = Local<Function>::Cast(args[1]);

  playInfo *pi = (playInfo *)
    malloc(sizeof(struct playInfo) + fileName.length()+1);

  pi->cb = Persistent<Function>::New(cb);
  pi->doCallback = args[1]->IsFunction();
  pi->channel = getNextChannel();
  pi->wave = NULL;
  strncpy(pi->name, *fileName, fileName.length() +1);

  eio_custom(DoPlay, EIO_PRI_DEFAULT, NotifyPlayed, pi);
  ev_ref(EV_DEFAULT_UC);

  return scope.Close(args[0]);
}

static void initSDL(void)
{
  /* Initialize the SDL library */
  if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
    return ;
  }

  int audio_rate;
  Uint16 audio_format;
  int audio_channels;

  /* Initialize variables */
  audio_rate = MIX_DEFAULT_FREQUENCY;
  audio_format = MIX_DEFAULT_FORMAT;
  audio_channels = 2;

  /* Open the audio device */
  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, 4096) < 0) {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
  }
  else {
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
    printf("Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format&0xFF),
			(audio_channels > 2) ? "surround" :
			(audio_channels > 1) ? "stereo" : "mono");

  }
  numChannels = Mix_AllocateChannels(32);
  printf("numChannels[%d]\n", numChannels);
}

extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;

  initSDL();

  NODE_SET_METHOD(target, "play", Play);
}
