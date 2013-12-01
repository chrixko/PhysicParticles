#pragma once
#include "particle.h"

class Sand : public Particle {
public:
	Sand(int posX, int posY);
	~Sand(void);	
	
	void ParticleMove(float deltaTime);	
};