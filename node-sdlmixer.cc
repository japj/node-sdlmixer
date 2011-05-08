#include <v8.h>
#include "SDL.h"
#include "SDL_mixer.h"

using namespace v8;

static int still_playing(void)
{
  return(Mix_Playing(0));
}


extern "C" void
init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("hello"), String::New("world"));

  /* Initialize the SDL library */
  if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n",SDL_GetError());
    return ;
  }

  int audio_rate;
  Uint16 audio_format;
  int audio_channels;
  Mix_Chunk *wave = NULL;


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

    /* Load the requested wave file */
    wave = Mix_LoadWAV("./wavs/alarm.wav");

    /* Play and then exit */
    Mix_PlayChannel(0, wave, 0);

    while (still_playing()) {
      SDL_Delay(1);

    } /* while still_playing() loop... */


  }
}
