var sdlmixer = require("./build/default/node-sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

// play with a callback

sdlmixer.play("./wavs/alarm.wav", function () {
  puts("callback'ed");
});

// these are all "fire and forget", no callback
var i=0;
for (i=0;i<20;i++) {
  sdlmixer.play('./wavs/kick.wav', function() {
    puts("done");
  });
}
sdlmixer.play('./wavs/phazed.wav');
sdlmixer.play('./wavs/flush.wav', function() {
  sdlmixer.play('./wavs/kick.wav');
});
sdlmixer.play('./wavs/ding.wav');
sdlmixer.play('./wavs/intro.wav', function() {
  sdlmixer.play('./wavs/ding.wav');
  for (i=0;i<20;i++) {
    sdlmixer.play('./wavs/kick.wav', function() {
      puts("done");
    });
  }
});


