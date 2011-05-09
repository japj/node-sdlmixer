var sdlmixer = require("./build/default/node-sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

// play with a callback

sdlmixer.play("./wavs/alarm.wav", function () {
  puts("callback'ed");
});

// these are all "fire and forget", no callback
sdlmixer.play('./wavs/kick.wav');
sdlmixer.play('./wavs/phazed.wav');
sdlmixer.play('./wavs/flush.wav');
sdlmixer.play('./wavs/ding.wav');
sdlmixer.play('./wavs/intro.wav');


