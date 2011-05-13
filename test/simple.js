var sdlmixer = require("../sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

puts("Opened audio at " + sdlmixer.audioRate + " Hz " + sdlmixer.audioFormat + " bit " + 
		sdlmixer.audioChannels + " and " + sdlmixer.numberOfAudioChannels + " channels.")

// play with a callback

sdlmixer.play(__dirname + "/../wavs/sfx/alarm.wav", function () {
  puts("done")
});