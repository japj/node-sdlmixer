#include <v8.h>
#include "SDL.h"
#include "SDL_mixer.h"

using namespace v8;


#define NODE_SET_METHOD(obj, name, callback)                              \
  obj->Set(v8::String::NewSymbol(name),                                   \
           v8::FunctionTemplate::New(callback)->GetFunction())

static int still_playing(void)
{
  return(Mix_Playing(0));
}

static Handle<Value> Play(const Arguments& args) {
  HandleScope scope;
  
  Mix_Chunk *wave = NULL;

  if (args.Length() < 1) {
    return ThrowException(Exception::TypeError(String::New("Bad argument")));
  }

  /* Load the requested wave file */
  String::AsciiValue fileName(args[0]->ToString());
  printf("Loading %s\n",*fileName);
  wave = Mix_LoadWAV(*fileName);

  printf("Playing\n");
  /* Play and then exit */
  Mix_PlayChannel(0, wave, 0);

  while (still_playing()) {
    SDL_Delay(1);

  } /* while still_playing() loop... */
  printf("Done\n");
  return scope.Close(args[0]);
}


extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("hello"), String::New("world"));
  NODE_SET_METHOD(target, "play", Play);

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
}
