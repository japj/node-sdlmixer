{
  "targets": [
    {
      "target_name": "node-sdlmixer",
      "include_dirs": ["/usr/local/include/SDL"],
      "libraries": ["-lSDL", "-lSDL_mixer"],
      "sources": [ "src/node-sdlmixer.cc" ],
     }
    ]
}
