var sdlmixer = require("./build/default/node-sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

sdlmixer.play("./wavs/alarm.wav", function () {
  sdlmixer.play("./wavs/alarm.wav");
});

