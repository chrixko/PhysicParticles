#pragma once
#include "particle.h"
class Water : public Particle {
public:
	Water(int posX, int posY);
	~Water(void);

	void ParticleMove(float deltaTime);
};