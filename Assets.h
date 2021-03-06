#pragma once

#include <string>
#include <map>

#include "lib\SDL_mixer\include\SDL_mixer.h"

#include "surface.h"
#include "Animation.h"

class Assets {
	public:
		static std::map<std::string, Surface*> Graphics;
		static std::map<std::string, Animation*> Animations;
		static std::map<std::string, Mix_Chunk*> Sounds;

		static void Load();
};