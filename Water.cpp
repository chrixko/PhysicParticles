#include "GameScene.h"
#include "Helper.h"
#include "Water.h"


Water::Water(int posX, int posY) : Particle(posX, posY) {
	ParticleType = PARTICLE_TYPE_WATER;
	ParticleColor = 0x0000FF;
	Mass = 1.5f;
}


Water::~Water(void)
{
}

void Water::ParticleMove(float deltaTime) {
	if(GScene->HasNeighbourOfType(this, PARTICLE_TYPE_OIL)) {
		Mass = 8.0f;
	} else {
		Mass = 1.5f;
	}

	Velocity.y = (PARTICLE_BASE_SPEED / Mass) * deltaTime;

	vector3 pos = Position + Velocity;

	for(int i = 0; i< pos.y - Position.y; i++) {
		if(!GScene->SpotIsFree(pos.x, Position.y + i, this)) {
			pos.y = Position.y + i;
			break;
		}
	}

	if(GScene->GetParticleType(pos.x, pos.y) == PARTICLE_TYPE_FIRE) {
		Particle* fire = GScene->GetParticle(pos.x, pos.y);
		GScene->RemoveEntity(fire);
		Position = fire->Position;
	} else if(GScene->GetParticleType(pos.x, pos.y) == PARTICLE_TYPE_OIL) {
		Particle* oil = GScene->GetParticle(pos.x, pos.y);
		oil->MoveTo(Position.x, Position.y);			

		Position = pos;
	} else if(!GScene->SpotIsFree(pos.x, pos.y, 0)) {
		if(GScene->SpotIsFree(pos.x -1, Position.y, 0)) {
			pos.x -= 1;
			pos.y = Position.y;
			Position = pos;
		} else if(GScene->SpotIsFree(pos.x + 1, Position.y, 0)) {
			pos.x += 1;
			pos.y = Position.y;
			Position = pos;
		} else if(GScene->GetParticleType(pos.x + 1, Position.y) == PARTICLE_TYPE_OIL) {
			Particle* oil = GScene->GetParticle(pos.x + 1, Position.y);
			oil->MoveTo(Position.x, Position.y);
			Position.x = pos.x + 1;
			Position.y = Position.y;
		} else if(GScene->GetParticleType(pos.x - 1, Position.y) == PARTICLE_TYPE_OIL) {
			Particle* oil = GScene->GetParticle(pos.x - 1, Position.y);
			oil->MoveTo(Position.x, Position.y);
			Position.x = pos.x - 1;
			Position.y = Position.y;
		}

		if(GScene->SpotIsFree(pos.x, pos.y + 1, 0)) {
			Position = pos;
			Position.y++;
		}
	} else {
		Position = pos;
	}
}