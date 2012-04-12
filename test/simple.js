var sdlmixer = require("../sdlmixer"),
        util = require("util"),
        puts = util.puts;

puts("Opened audio at " + sdlmixer.audioRate + " Hz " + sdlmixer.audioFormat + " bit " + 
		sdlmixer.audioChannels + " and " + sdlmixer.numberOfAudioChannels + " channels.")

// play with a callback

sdlmixer.play(__dirname + "/../wavs/sfx/alarm.wav", function () {
  puts("done")
});
