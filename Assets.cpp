#include <string>

#include "Assets.h"

std::map<std::string, Surface*> Assets::Graphics;
std::map<std::string, Animation*> Assets::Animations;
std::map<std::string, Mix_Chunk*> Assets::Sounds;

void Assets::Load() {            
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
	
	Graphics["sand"] = new Surface("assets/graphics/sand.png");
	Graphics["sand_skipped"] = new Surface("assets/graphics/sand_skipped.png");
}