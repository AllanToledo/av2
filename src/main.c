#include "menu/menu.h"
#include <windows.h>

int main() {
    //Possivelmente essa linha de problema caso seja compilado para linux
    SetConsoleOutputCP(CP_UTF8);
    menuPrincipal();
    return 0;
}
