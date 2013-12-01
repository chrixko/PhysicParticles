#include "Wood.h"


Wood::Wood(int posX, int posY) : Particle(posX, posY) {
	ParticleColor = 0x705400;
	ParticleType = PARTICLE_TYPE_WOOD;
	BurnChance = 2;
}


Wood::~Wood(void)
{
}
