# node-sdlmixer experiment

This is an experiment to get sdlmixer working together with nodejs.

Note: since I am completely new to nodejs addon development, this
is currently a very bad example of coding it.


## Requirements for compilation:
- nodejs
- node-waf
- SDL-dev
- SDL_mixer-dev

tested on ubuntu 11.04 (64bit) with:
* installing nodejs
* sudo apt-get install libsdl1.2-dev
* sudo apt-get install libsdlmixer1.2-dev

tested on osx 10.6.7 + brew
* install nodejs
* brew install sdl
* brew install sdl_mixer

## Install with npm 

npm install node-sdlmixer

## Simple usage example

  $ node
  > var p = require("node-sdlmixer");
  Opened audio at 22050 Hz 16 bit stereo
  numChannels[32]
  > p.play("github/node-sdlmixer/wavs/alarm.wav");
  Loading github/node-sdlmixer/wavs/alarm.wav
  'github/node-sdlmixer/wavs/alarm.wav'
  > Playing on channel[1]
  Done

