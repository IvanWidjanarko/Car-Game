#ifndef GBPS_MOBIL_H
#define GBPS_MOBIL_H

#include "Common.h"

#define MAX_CAR_ROT 15
#define MAX_CAR_SIDE_POS 3

typedef struct
{
    float x,y;
    GLMmodel *CarModel,*TyreModel;
    int CarTexture;
    float vel,acc;
    float rot;
    float TyreRot;
    int state1,state2,state3;
    int type;

} Gbps_Car;

enum CarTypes
{
    CAR_CONSTANT_VEL,CAR_CONSTANT_VEL_MOVING
};

void RenderCar(Gbps_Car Car);

#endif
