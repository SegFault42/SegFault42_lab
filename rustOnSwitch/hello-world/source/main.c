#include <string.h>
#include <stdio.h>

#include <switch.h>

int main(int argc, char **argv)
{
    consoleInit(NULL);

    printf("\x1b[16;20HHello World!");

    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) {
			break;
		}
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
