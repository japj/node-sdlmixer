var sdlmixer = require("./build/default/node-sdlmixer"),
         sys = require("sys"),
        puts = sys.puts;

puts(sdlmixer.hello);
sdlmixer.play("./wavs/alarm.wav");
sdlmixer.play("./wavs/alarm.wav");

