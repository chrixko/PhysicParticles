#include "Input.h"
#include "ParticleSelector.h"


ParticleSelector::ParticleSelector(int posX, int posY) {
	Position.x = posX;
	Position.y = posY;
	ZOrder = 10;

	CurrentType = 1;
}


ParticleSelector::~ParticleSelector(void)
{
}

void ParticleSelector::Update(float deltaTime) {	
	if(Input::IsKeyJustPressed(SDLK_LEFT)) {
		if(CurrentType > 1) {
			CurrentType--;
		}
	}

	if(Input::IsKeyJustPressed(SDLK_RIGHT)) {
		if(CurrentType < PARTICLE_TYPE_COUNT - 1) {
			CurrentType++;
		}
	}
}

void ParticleSelector::Draw(Surface* screen, float deltaTime) {
	for(int i = 0; i < PARTICLE_TYPE_COUNT; i++) {
		int color = 0;
		std::string text = "";

		if(i == PARTICLE_TYPE_SAND) {
			text = "Sand";
			color = 0xFFCE30;
		} else if(i == PARTICLE_TYPE_WATER) {
			text = "water";
			color = 0x0000FF;
		} else if(i == PARTICLE_TYPE_CONCRETE) {
			text = "concrete";
			color = 0xAACCEE;
		} else if(i == PARTICLE_TYPE_OIL) {
			text = "oil";
			color = 0x35280D;
		} else if(i == PARTICLE_TYPE_FIRE) {
			text = "fire";
			color = 0xFF0000;
		} else if(i == PARTICLE_TYPE_WOOD) {
			text = "wood";
			color = 0x705400;
		}

		int posX = Position.x + ((i - 1) * 55);
		int posY = Position.y;

		if(i == CurrentType) {
			screen->Bar(posX - 3, posY - 3, posX + 18, posY + 18, 0x556677);
		}
		
		screen->Print(&text[0], posX - 5, posY + 20, 0xFFFFFF);
		screen->Bar(posX, posY, posX + 15, posY + 15, color);
	}
}
