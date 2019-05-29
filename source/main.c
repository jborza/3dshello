#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <time.h>

int main(int argc, char* argv[])
{
	PrintConsole topScreen, bottomScreen;
	gfxInitDefault();
	consoleInit(GFX_TOP, &topScreen);
	consoleInit(GFX_BOTTOM, &bottomScreen);

	int counter = 0;

	// Main loop
	while (aptMainLoop())
	{
		gspWaitForVBlank();
		gfxSwapBuffers();
		hidScanInput();

		// Your code goes here
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		if(kDown & KEY_A)
			counter++;

		//get the current time
		time_t unixTime = time(NULL); 
		struct tm* timeStruct = gmtime((const time_t *)&unixTime);
		consoleSelect(&topScreen);
		//move the cursor back to 1,1 (Row, Column)
		printf("\x1b[1;1H");
		printf("Hello, world from CFW!\n");

		
		printf("Time is: \x1b[31m %02d:%02d:%02d \x1b[0m\n", 
			timeStruct->tm_hour, timeStruct->tm_min, timeStruct->tm_sec);

		
		printf("\x1b[30;16HPress Start to exit."); 
		
		consoleSelect(&bottomScreen);
		printf("\x1b[10;1H");
		printf("Press [A] to increment counter\n");
		printf("  Counter value is: %d\n", counter);

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank(); 
	}

	gfxExit();
	return 0;
}
