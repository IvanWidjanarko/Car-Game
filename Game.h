#ifndef GAME_H
#define GAME_H

#include "Common.h"
#include "Mobil.h"
#include "Linkedlist.h"
#include "Object.h"

float gbps_camDist;
int gbps_aziy;
int gbps_elex;
float gbps_camUp;
extern int gbps_rtLtKey;
extern int gbps_upDownKey;
extern int gbps_TotalOpponentCars;
extern int game_over;
long gbps_locct;
long gbps_lsoct;

long gbps_score;

long elapsed_time,total_time;

double gbps_road_loop;

Gbps_Car PlayerCar;
gbpsLinkedList OpponentCars;
gbpsLinkedList SideObjects;

void gbps_EnterGame();
void gbps_GameLoop();
void gbps_LeaveGame();
void gbps_PauseGame();
void gbps_ResumeGame();
void gbps_RenderGame();
void UpdateGameLogic();
void UpdatePlayerCar();
void UpdateOpponentCars();

void gbps_GameSpecialKey(int key, int x, int y);
void gbps_GameSpecialKeyUp(int key, int x, int y);
void gbps_GameAsciiKey(int key, int x, int y);
void gbps_GameMouse(int button,int state,int x,int y);
void gbps_GameMouseWheel(int button, int dir, int x, int y);
void gbps_GameMouseMove(int x,int y);

void game_changeCamera(int x,int y);

void DEBUG_drwCord(void);
#endif
