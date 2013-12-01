#pragma once
#include "particle.h"
class Oil :	public Particle {
public:
	Oil(int posX, int posY);
	~Oil(void);

	void ParticleMove(float deltaTime);
};