var sdlmixer = require("../sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

// play with a callback

sdlmixer.play("../wavs/sfx/alarm.wav", function () {
  puts("done")
});

// these are all "fire and forget", no callback
var i=0;
for (i=0;i<20;i++) {
  sdlmixer.play('../wavs/drums/kick.wav', function(fileName, channel) {
	puts(channel +": "+fileName + " done")
  });
}
sdlmixer.play('../wavs/drums/phazed.wav');
sdlmixer.play('../wavs/sfx/flush.wav', function(fileName, channel) {
  puts(channel +": "+fileName + " done")
  sdlmixer.play('../wavs/drums/snare.wav');
});
sdlmixer.play('../wavs/sfx/ding.wav');
sdlmixer.play('../wavs/sfx/intro.wav', function(fileName, channel) {
  puts(channel +": "+fileName + " done")
  sdlmixer.play('../wavs/sfx/ding.wav');
  for (i=0;i<20;i++) {
    sdlmixer.play('../wavs/drums/kick.wav', function(fileName, channel) {
    	puts(channel +": "+fileName + " done")
    });
  }
});


