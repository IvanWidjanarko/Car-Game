#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "MenuUtama.h"
#include "Awal.h"
#include "Game.h"

int main(int argc,char * argv[])
{
    Fullscreen();
    gbps_InitWindow(argc,argv);
    glutFullScreen();
    gbps_EnterMainMenu();
    glutMainLoop();
    return 0;
}

void Fullscreen()
{  keybd_event(VK_MENU,
				0x38,
				0,
				0);
	keybd_event(VK_RETURN,
				0x1c,
				0,
				0);
	keybd_event(VK_RETURN,
				0x1c,
				KEYEVENTF_KEYUP,
				0);
	keybd_event(VK_MENU,
				0x38,
				KEYEVENTF_KEYUP,
				0);
}
