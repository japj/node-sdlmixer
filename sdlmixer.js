var sdlmixer_lib;
var node_version = process.version.split('.');
if ((node_version[0] == "v0") && (node_version[1] == "4"))
{
// console.log("v0.4.x");
 sdlmixer_lib = require('./build/default/node-sdlmixer');
}
else
{
// console.log("!v0.4.x");
 sdlmixer_lib = require('./build/Release/node-sdlmixer');  
}

module.exports = new sdlmixer_lib.SDLMixer();
