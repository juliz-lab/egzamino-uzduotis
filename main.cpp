#include "mylib.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8); // lietuvisku raidziu isvedimui terminale

    map<string, zodzioInfo> zodziai = failo_nuskaitymas("tekstas.txt");
    failo_isvedimas(zodziai);
    vector<string> galai = url_nuskaitymas("url.txt");
    vector<string> nuorodos = nuorodu_paieska("tekstas.txt", galai);
    nuorodu_isvedimas(nuorodos);
}
