# node-sdlmixer

This node addon was originally started due the
"Low-Latency Cross-Platform Audio Playback" thread on the node mailinglist at
http://groups.google.com/group/nodejs/browse_thread/thread/5b62789562697956

## Requirements for compilation:
- node
- node-waf
- SDL-dev
- SDL_mixer-dev

tested on ubuntu 11.04 (64bit) with:

- installing nodejs
- sudo apt-get install libsdl1.2-dev
- sudo apt-get install libsdlmixer1.2-dev

tested on osx 10.6.7 + brew

- install nodejs
- brew install sdl
- brew install sdl_mixer

## Install with npm 

npm install sdlmixer

## Build from source

git clone git://github.com/japj/node-sdlmixer.git
cd node-sdlmixer
node-waf configure build

## Simple usage example

    $ node
    > var p = require("sdlmixer");
    Opened audio at 22050 Hz 16 bit stereo
    numChannels[32]
    > p.play("github/node-sdlmixer/wavs/alarm.wav");
    Loading github/node-sdlmixer/wavs/alarm.wav
    'github/node-sdlmixer/wavs/alarm.wav'
    > Playing on channel[1]
    Done
