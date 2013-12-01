#include "Assets.h"
#include "Helper.h"
#include "GameScene.h"
#include "Sand.h"


Sand::Sand(int posX, int posY) : Particle(posX, posY) {
	ParticleColor = 0xFFCE30;
	ParticleType = PARTICLE_TYPE_SAND;
}


Sand::~Sand(void)
{
}

void Sand::ParticleMove(float deltaTime) {	
	if(GScene->HasNeighbourOfType(this, PARTICLE_TYPE_OIL)) {
		Mass = 8.0f;
	} else if(GScene->HasNeighbourOfType(this, PARTICLE_TYPE_WATER)) {
		Mass = 3.0f;
	} else {
		Mass = 1.0f;
	}

	Velocity.y = (PARTICLE_BASE_SPEED / Mass) * deltaTime;

	vector3 pos = Position + Velocity;

	for(int i = 0; i< pos.y - Position.y; i++) {
		if(!GScene->SpotIsFree(pos.x, Position.y + i, this)) {
			pos.y = Position.y + i;
			break;
		}
	}

	if(GScene->GetParticleType(pos.x, pos.y) == PARTICLE_TYPE_WATER || GScene->GetParticleType(pos.x, pos.y) == PARTICLE_TYPE_OIL) {
		Particle* water = GScene->GetParticle(pos.x, pos.y);
		water->MoveTo(Position.x, Position.y);			

		Position = pos;
	} else if(!GScene->SpotIsFree(pos.x, pos.y, this)) {		
		int change = 0;
		if(Direction == 0) {
			if(Helper::GetRandomInt(0, 2) > 0) {
				change = 1;
			} else {
				change = -1;
			}
		} else {
			change = Direction;
		}

		if(GScene->Particles[(int)pos.x + change][(int)pos.y] == 0) {				
			pos.x += change;
			Position = pos;
			Direction = change;
		} else {
			change *= -1;
			if(GScene->Particles[(int)pos.x + change][(int)pos.y] == 0) {
				pos.x += change;
				Position = pos;
				Direction = change;
			}
		}
	} else {		
		Position = pos;
	}
}
