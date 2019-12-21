#include "Game.h"
#include <math.h>

int gbps_rtLtKey=0;
int gbps_upDownKey=0;
int gbps_TotalOpponentCars=7;
float pos;
int game_over=0;

void gbps_EnterGame()
{
    game_over=0;
    gbps_GamePlaying=2;
    glutSpecialFunc(gbps_GameSpecialKey);
    glutSpecialUpFunc(gbps_GameSpecialKeyUp);
    glutKeyboardFunc(gbps_GameAsciiKey);

    glutMouseFunc(gbps_GameMouse);
    glutMotionFunc(gbps_GameMouseMove);
    glutMouseWheelFunc(gbps_GameMouseWheel);

    glutDisplayFunc(gbps_RenderGame);


    gbps_road_loop=1.0;

    gbps_aziy=0;
    gbps_elex=21;
    gbps_camDist=10;
    gbps_camUp=-2;
    game_changeCamera(0,0);

    total_time=0;

    PlayerCar.CarTexture=GBPS_TEXTURE_CAR1;
    PlayerCar.vel=1;
    PlayerCar.acc=0.03;
    PlayerCar.x=0;
    PlayerCar.y=0;
    PlayerCar.TyreRot=0;
    PlayerCar.rot=0;
    gbps_score=0;

    OpponentCars.Head=OpponentCars.Tail=NULL;
    OpponentCars.NoItems=0;
    gbps_locct=gbps_lsoct=total_time;

    gbps_GameLoop();
}

void gbps_LeaveGame()
{
    gbps_GamePlaying=0;
    glutSpecialFunc(NULL);
    glutSpecialUpFunc(NULL);
    glutKeyboardFunc(NULL);

    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutMouseWheelFunc(NULL);

    while(OpponentCars.NoItems>0)
    {
        free((Gbps_Car*)PopItem(&OpponentCars));
    }
    while(SideObjects.NoItems>0)
    {
        free((GBPS_Tree*)PopItem(&SideObjects));
    }
}

void gbps_GameSpecialKey(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        PlayerCar.vel+=1;
        gbps_upDownKey=1;
        break;

    case GLUT_KEY_DOWN:
        PlayerCar.vel-=0.5;
        gbps_upDownKey=-1;
        break;

    case GLUT_KEY_LEFT:
        gbps_rtLtKey=-1;
        break;

    case GLUT_KEY_RIGHT:
        gbps_rtLtKey=1;
        break;
    }
}

void gbps_GameSpecialKeyUp(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        PlayerCar.vel-=1;
        gbps_upDownKey=0;
        break;

    case GLUT_KEY_DOWN:
        PlayerCar.vel+=0.5;
        gbps_upDownKey=0;
        break;

    case GLUT_KEY_LEFT:

    case GLUT_KEY_RIGHT:
        gbps_rtLtKey=0;
        break;
    }
}

void gbps_GameAsciiKey(int key, int x, int y)
{
    if(game_over==1)
    {
        if(key==13)
        {
             gbps_LeaveGame();
             gbps_EnterMainMenu();
        }
        return;
    }
    switch (key)
    {
    case 27:
        break;

    case 'w':
        gbps_camUp-=0.1;
        game_changeCamera(0,0);
        break;

    case 's':
        gbps_camUp+=0.1;
        game_changeCamera(0,0);
        break;

    case 'p':
        gbps_GamePlaying=(gbps_GamePlaying==2)?1:2;
        break;

    default:
        break;
    }
}

void gbps_GameMouse(int button,int state,int x,int y)
{

}

void gbps_GameMouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
        gbps_camDist--;
        game_changeCamera(0,0);
    }
    else
    {
        gbps_camDist++;
        game_changeCamera(0,0);
    }

    return;
}

void gbps_GameMouseMove(int x,int y)
{
    game_changeCamera(x,y);
}

void glutPrint(float x, float y, LPVOID font, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos3f(x,y,-gbps_camDist);
    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
    glDisable(GL_BLEND);
}

void RenderScore()
{
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);

    char sc[100];
    sprintf(sc,"Score : %d",gbps_score);
    glutPrint(5,-13,GLUT_BITMAP_HELVETICA_18,sc,225,0,0,1);
    sprintf(sc,"High Score : %d",highscore);
    glutPrint(5,-12,GLUT_BITMAP_HELVETICA_18,sc,225,0,0,1);
    glMatrixMode(GL_MODELVIEW);
    glEnable( GL_DEPTH_TEST);
}

void gbps_RenderGame()
{
    glLoadIdentity();
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

    glTranslated(0.0, 0.0, -gbps_camDist);
    //glRotated(GBPS_twi, 0.0, 0.0, 1.0);
    glRotated(gbps_elex, 1.0, 0.0, 0.0);
    glRotated(gbps_aziy, 0.0, 1.0, 0.0);

    glMatrixMode(GL_TEXTURE);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glColor3f(1,1,1);

    GLUquadricObj *qObj = gluNewQuadric();
    gluQuadricNormals(qObj, GLU_SMOOTH);
    gluQuadricTexture(qObj, GL_TRUE);
    glBindTexture(GL_TEXTURE_2D, GBPS_texArr[GBPS_TEXTURE_SKY]);
    glPushMatrix();
    glRotatef(180.0,1.0,0,0);
    gluSphere(qObj, 80.0f, 24, 24);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    glTranslatef(0,gbps_road_loop,0);
    glBindTexture(GL_TEXTURE_2D, GBPS_texArr[GBPS_TEXTURE_ROAD]);

    glBegin(GL_QUADS);

    // glNormal3d(0,1,0);
    glColor3f(1,1,1);

    glTexCoord2f(0.0, 0.0);
    glVertex3d(4,0,-200);

    glTexCoord2f(1.0, 0.0);
    glVertex3d(-4,0,-200);

    glTexCoord2f(1.0, 4.0);
    glVertex3d(-4,0,200);

    glTexCoord2f(0.0, 4.0);
    glVertex3d(4,0,200);

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, GBPS_texArr[GBPS_TEXTURE_SURR]);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0,0.0);
    glVertex3f(-100.0,-0.3,-1000.0);
    glTexCoord2d(0.0,50.0);
    glVertex3f(-100.0,-0.3,1000.0);
    glTexCoord2d(10.0,50.0);
    glVertex3f(100.0,-0.3,1000.0);
    glTexCoord2d(10.0,0.0);
    glVertex3f(100.0,-0.3,-1000.0);
    glTranslatef(0.0,0.0,a);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    DEBUG_drwCord();


    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    DEBUG_drwCord();
    ListItem* CurrentTree=SideObjects.Tail;
    for(i=0; i<SideObjects.NoItems; i++)
    {
        RenderTree(*((GBPS_Tree*)CurrentTree->Data));
        CurrentTree=CurrentTree->Prev;
    }
    RenderCar(PlayerCar);
    ListItem* CurrentCar=OpponentCars.Head;

    for(i=0; i<OpponentCars.NoItems; i++)
    {
        RenderCar(*((Gbps_Car*)CurrentCar->Data));
        CurrentCar=CurrentCar->Next;
    }
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.0, -9.0);
    //glRotated(GBPS_twi, 0.0, 0.0, 1.0);
    glRotated(21.0, 1.0, 0.0, 0.0);
    glRotated(0, 0.0, 1.0, 0.0);

    RenderScore();
    //render_railing();
    render_speedometer();
    if(game_over==1)
    {
        render_game_over();
    }
    glPopMatrix();
    glutSwapBuffers();
}

void UpdateGameLogic()
{
    elapsed_time=GBPS_nf;
    total_time+=elapsed_time;

    UpdateOpponentCars();
    UpdateSideObjects();
    UpdatePlayerCar();

    ListItem* CurrentCar=OpponentCars.Head;
    int i;
    for(i=0; i<OpponentCars.NoItems; i++)
    {
        Gbps_Car* CurCar=(Gbps_Car*)CurrentCar->Data;
        if(fabs(CurCar->x - PlayerCar.x) < 2)
        {
            if(fabs(CurCar->y - PlayerCar.y) < 4.5)
            {
                gbps_GamePlaying=1;
                game_over=1;
                PlayerCar.vel=0;
                if(gbps_score > highscore)
                {
                    highscore=gbps_score;
                    FILE* file=fopen("score.txt","wb");
                    fwrite(&gbps_score,sizeof(long),1,file);
                    fclose(file);
                }
                break;
            }
        }
        CurrentCar=CurrentCar->Next;
    }
}

void UpdatePlayerCar()
{
    PlayerCar.vel+=PlayerCar.acc*(elapsed_time/1000.0);

    float dist=PlayerCar.vel*(elapsed_time/1000.0);

    gbps_score+=(int)(dist*100);

    PlayerCar.TyreRot+=((dist)/(2.0*3.1415*.01))*360.0;
    while(PlayerCar.TyreRot>360.0)
    {
        PlayerCar.TyreRot-=360.0;
    }

    gbps_road_loop-=dist;

    if (gbps_road_loop < 0.0)
    {
        gbps_road_loop = (1+gbps_road_loop);
    }

    if((gbps_rtLtKey)&&(fabs(PlayerCar.x)<3))
    {
        PlayerCar.x+=gbps_rtLtKey*0.3;
        PlayerCar.rot+=gbps_rtLtKey*4;

        if(fabs(PlayerCar.rot)>MAX_CAR_ROT)
        {
            PlayerCar.rot=((PlayerCar.rot<0)?-1:1)*MAX_CAR_ROT;
        }

        if(fabs(PlayerCar.x)>MAX_CAR_SIDE_POS)
        {
            PlayerCar.x=((PlayerCar.x<0)?-1:1)*(MAX_CAR_SIDE_POS-0.01);
        }
    }

    if((!gbps_rtLtKey)&&(fabs(PlayerCar.rot)>0.1))
    {
        PlayerCar.rot+=((PlayerCar.rot>0)?-1:1)*4;
        if(fabs(PlayerCar.rot)<5)PlayerCar.rot=0;
    }
}

void UpdateSideObjects()
{
    int i;
    if(total_time-gbps_lsoct > 20)
    {
        srand(total_time);
        if( (rand()%2) < 1)
        {
            gbps_lsoct=total_time;
            GBPS_Tree* obj=malloc(sizeof(Gbps_Car));
            AddItem(&SideObjects,(void*)obj);

            if(rand()%2 ==0)
                obj->x=15+(sin(rand()%90*3.14/180)*30);
            else
                obj->x=-15-(sin(rand()%90*3.14/180)*30);
            obj->y=200;
        }
    }

    ListItem* CurrentObject=SideObjects.Head;
    for(i=0; i<SideObjects.NoItems; i++)
    {
        float dist;
        dist=PlayerCar.vel*elapsed_time/15.0;
        ((GBPS_Tree*)CurrentObject->Data)->y-=fabs(dist);
        CurrentObject=CurrentObject->Next;
    }

    while(SideObjects.NoItems>0 &&  ((GBPS_Tree*)(SideObjects.Head)->Data)->y < -100)
    {
        free((GBPS_Tree*)PopItem(&SideObjects));
    }
}

void UpdateOpponentCars()
{
    int i;

    if(OpponentCars.NoItems < gbps_TotalOpponentCars)
    {
        if(total_time-gbps_locct > 2000)
        {
            srand(time(0));
            if( (rand()%gbps_TotalOpponentCars) <= (gbps_TotalOpponentCars-OpponentCars.NoItems))
            {
                gbps_locct=total_time;

                Gbps_Car* nc=malloc(sizeof(Gbps_Car));
                AddItem(&OpponentCars,(void*)nc);

                nc->x=((rand()%6)-3);
                nc->y=100;

                nc->vel=(1.0*PlayerCar.vel)/3.0;
                nc->acc=0;

                nc->CarTexture=GBPS_TEXTURE_CAR1;
                nc->rot=nc->TyreRot=0;

                i=rand()%2;
                switch(i)
                {
                case 0:
                    nc->type=CAR_CONSTANT_VEL;
                    break;

                case 1:
                    nc->type=CAR_CONSTANT_VEL_MOVING;
                    nc->state1=(nc->x > 0)?0:1;
                    break;
                }
            }
        }
    }

    ListItem* CurrentCar=OpponentCars.Head;
    for(i=0; i<OpponentCars.NoItems; i++)
    {

        float dist;
        ((Gbps_Car*)CurrentCar->Data)->vel+=((Gbps_Car*)CurrentCar->Data)->acc*(elapsed_time/1000.0);
        dist=(PlayerCar.vel-((Gbps_Car*)CurrentCar->Data)->vel)*(elapsed_time/15.0);
        ((Gbps_Car*)CurrentCar->Data)->y-=fabs(dist);

        ((Gbps_Car*)CurrentCar->Data)->TyreRot+=((fabs(dist))/(2.0*3.1415*.04))*360.0;
        while(((Gbps_Car*)CurrentCar->Data)->TyreRot>360.0)
        {
            ((Gbps_Car*)CurrentCar->Data)->TyreRot-=360.0;
        }

        if(((Gbps_Car*)CurrentCar->Data)->type==CAR_CONSTANT_VEL_MOVING)
        {
            if(((Gbps_Car*)CurrentCar->Data)->state1==0)
            {
                ((Gbps_Car*)CurrentCar->Data)->x-=0.21;
                if(((Gbps_Car*)CurrentCar->Data)->x < -2.7)
                {
                    ((Gbps_Car*)CurrentCar->Data)->state1=1;
                }
            }

            else
            {
                ((Gbps_Car*)CurrentCar->Data)->x+=0.21;
                if(((Gbps_Car*)CurrentCar->Data)->x >2.7)
                {
                    ((Gbps_Car*)CurrentCar->Data)->state1=0;
                }
            }
        }

        CurrentCar=CurrentCar->Next;
    }

    while(OpponentCars.NoItems>0 &&  ((Gbps_Car*)(OpponentCars.Head)->Data)->y < -100)
    {
        free((Gbps_Car*)PopItem(&OpponentCars));
    }
}

void gbps_GameLoop()
{
    if(gbps_GamePlaying==2)
    {
        UpdateGameLogic();
        glutPostRedisplay();
        glutTimerFunc(GBPS_nf,gbps_GameLoop,0);
    }

    else if(gbps_GamePlaying == 1)
    {
        glutPostRedisplay();
        glutTimerFunc(GBPS_nf,gbps_GameLoop,0);
    }
}

void game_changeCamera(int x,int y)
{
    static int prevx,prevy;
    int difx=x-prevx;
    int dify=y-prevy;
    prevx=x;
    prevy=y;

    if (difx>0)
    {
        gbps_aziy++;
    }

    else if (difx<0)
    {
        gbps_aziy--;
    }

    if (dify>0)
    {
        gbps_elex++;
    }

    else if (dify<0)
    {
        gbps_elex--;
    }

    if (gbps_elex>90)gbps_elex=90;
    if (gbps_elex<5)gbps_elex=5;
    if (gbps_camDist<5) gbps_camDist=5;
    if (gbps_camDist>20) gbps_camDist=20;
}
