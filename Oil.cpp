#include "GameScene.h"
#include "Oil.h"


Oil::Oil(int posX, int posY) : Particle(posX, posY) {
	ParticleColor = 0x35280D;
	Mass = 1.8f;
	ParticleType = PARTICLE_TYPE_OIL;
	BurnChance = 10;
}


Oil::~Oil(void)
{
}

void Oil::ParticleMove(float deltaTime) {
	Velocity.y = (PARTICLE_BASE_SPEED / Mass) * deltaTime;

	vector3 pos = Position + Velocity;

	for(int i = 0; i< pos.y - Position.y; i++) {
		if(!GScene->SpotIsFree(pos.x, Position.y + i, this)) {
			pos.y = Position.y + i;
			break;
		}
	}

	if(!GScene->SpotIsFree(pos.x, pos.y, 0)) {
		if(GScene->SpotIsFree(pos.x -1, Position.y, 0)) {
			pos.x -= 1;
			pos.y = Position.y;
			Position = pos;
		} else if(GScene->SpotIsFree(pos.x + 1, Position.y, 0)) {
			pos.x += 1;
			pos.y = Position.y;
			Position = pos;
		}

		if(GScene->SpotIsFree(pos.x, pos.y + 1, 0)) {
			Position = pos;
			Position.y++;
		}
	} else {
		Position = pos;
	}
}
