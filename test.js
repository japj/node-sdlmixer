var sdlmixer = require("./sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

// play with a callback

sdlmixer.play("./wavs/sfx/alarm.wav", function () {
  puts("callback'ed");
});

// these are all "fire and forget", no callback
var i=0;
for (i=0;i<20;i++) {
  sdlmixer.play('./wavs/drums/kick.wav', function() {
    puts("done");
  });
}
sdlmixer.play('./wavs/drums/phazed.wav');
sdlmixer.play('./wavs/sfx/flush.wav', function() {
  sdlmixer.play('./wavs/drums/snare.wav');
});
sdlmixer.play('./wavs/sfx/ding.wav');
sdlmixer.play('./wavs/sfx/intro.wav', function() {
  sdlmixer.play('./wavs/sfx/ding.wav');
  for (i=0;i<20;i++) {
    sdlmixer.play('./wavs/drums/kick.wav', function() {
      puts("done");
    });
  }
});


