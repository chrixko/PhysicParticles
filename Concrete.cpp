#include "Concrete.h"


Concrete::Concrete(int posX, int posY) : Particle(posX, posY) {
	ParticleType = PARTICLE_TYPE_CONCRETE;
	ParticleColor = 0xAACCEE;
}


Concrete::~Concrete(void)
{
}
