#pragma once

#include "entity.h"
#include "Particle.h"

class ParticleSelector : public Entity {
public:
	ParticleSelector(int posX, int posY);
	~ParticleSelector(void);
	
	int CurrentType;


	void Update(float deltaTime);
	void Draw(Surface* screen, float deltaTime);
};