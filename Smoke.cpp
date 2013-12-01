#include "GameScene.h"
#include "Smoke.h"

Smoke::Smoke(int posX, int posY) : Particle(posX, posY) {
	ParticleColor = 0x6D6A60;
}


Smoke::~Smoke(void)
{
}

void Smoke::ParticleMove(float deltaTime) {
	Velocity.y = -(PARTICLE_BASE_SPEED / Mass) * deltaTime;
	vector3 pos = Position + Velocity;

	if(!GScene->SpotIsFree(pos.x, pos.y, this)) {
		Particle* p = GScene->GetParticle(pos.x, pos.y);
		p->MoveTo(Position.x, Position.y);
		Position.x = pos.x;
		Position.y = pos.y;
	} else {
		Position = pos;
	}
}
