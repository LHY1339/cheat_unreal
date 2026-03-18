#include "cheat_exit.h"
#include "gvalue.h"

void cheat_exit::main()
{
    while (!gvalue::is_clean)
    {
        Sleep(100);
    }
    FreeLibraryAndExitThread(gvalue::dll_inst, 0);
}