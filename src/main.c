#include "menu/menu.h"
#include <windows.h>

void configWindow()
{
    SetConsoleTitle("Locação de Veículos");
    SetConsoleOutputCP(CP_UTF8);
    DWORD l_mode;
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleMode(hStdout, &l_mode);
    SetConsoleMode(hStdout, l_mode |
                                0x4 |
                                0x8);
}

int main()
{
    // Possivelmente essa linha de problema caso seja compilado para linux
    configWindow();
    menuPrincipal();
    return 0;
}
