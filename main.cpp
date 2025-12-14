#include "mylib.h"
int main()
{
    //SetConsoleOutputCP(CP_UTF8);
    //SetConsoleCP(CP_UTF8); // lietuvisku raidziu isvedimui GALIMAI PAKEISTI REIKES

    map<string, zodzioInfo> zodziai = failo_nuskaitymas("tekstas.txt");
    failo_isvedimas(zodziai);
}
