var sdlmixer = require("../sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

puts("Opened audio at " + sdlmixer.audioRate + " Hz " + sdlmixer.audioFormat + " bit " + 
		sdlmixer.audioChannels + " and " + sdlmixer.numberOfAudioChannels + " channels.")

// play with a callback

sdlmixer.play(__dirname + "/../wavs/sfx/alarm.wav", function () {
  puts("done")
});

// these are all "fire and forget", no callback
var i=0;
for (i=0;i<20;i++) {
  sdlmixer.play(__dirname + '/../wavs/drums/kick.wav', function(fileName, channel) {
	puts(channel +": "+fileName + " done")
  });
}
sdlmixer.play(__dirname + '/../wavs/drums/phazed.wav');
sdlmixer.play(__dirname + '/../wavs/sfx/flush.wav', function(fileName, channel) {
  puts(channel +": "+fileName + " done")
  sdlmixer.play(__dirname + '/../wavs/drums/snare.wav');
});
sdlmixer.play(__dirname + '/../wavs/sfx/ding.wav');
sdlmixer.play(__dirname + '/../wavs/sfx/intro.wav', function(fileName, channel) {
  puts(channel +": "+fileName + " done")
  sdlmixer.play(__dirname + '/../wavs/sfx/ding.wav');
  for (i=0;i<20;i++) {
    sdlmixer.play(__dirname + '/../wavs/drums/kick.wav', function(fileName, channel) {
    	puts(channel +": "+fileName + " done")
    });
  }
});


