#include "Mobil.h"
extern float car_crash_angle=0.0;

Gbps_Car* CreateCar(GLuint* cartexture)
{
    Gbps_Car* c=malloc(sizeof(Gbps_Car));
    return c;
}

void RenderCar(Gbps_Car Car)
{
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glRotatef(car_crash_angle,1.0,0,0);
    glTranslatef(Car.x,0.6,-Car.y);
    glRotatef(-Car.rot,0,1,0);
    glBindTexture(GL_TEXTURE_2D, GBPS_texArr[GBPS_TEXTURE_CAR1]);
    glmDraw(car1, GLM_SMOOTH | GLM_TEXTURE);

    glRotated(-90,0,1,0);
    glBindTexture(GL_TEXTURE_2D, GBPS_texArr[GBPS_TEXTURE_TYRE]);

    glPushMatrix();
    glTranslatef(-1.205,-0.277,0.733);
    glRotatef(-(Car.rot*2)+90,0,1,0);
    glRotatef(Car.TyreRot,-1,0,0);
    glmDraw(tyre1,GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();//tr
    glTranslatef(-1.206,-0.277,-0.731);
    glRotatef(-(Car.rot*2)+270,0,1,0);
    glRotatef(Car.TyreRot,1,0,0);
    glmDraw(tyre1,GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.155,-0.277,0.731);
    glRotatef(90,0,1,0);
    glRotatef(Car.TyreRot,-1,0,0);
    glmDraw(tyre1,GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.154,-0.277,-0.733);
    glRotatef(270,0,1,0);
    glRotatef(Car.TyreRot,1,0,0);
    glmDraw(tyre1,GLM_SMOOTH | GLM_TEXTURE);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
