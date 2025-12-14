#include <iomanip>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>

using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;
using std::locale;
using std::map;
using std::string;
using std::stringstream;
using std::tolower;
using std::vector;
using std::tolower;
using std::ofstream;

// using std::

map<string, int> failo_nuskaitymas(const string &failas);
bool ar_leistina_raide(string c);
string naikinti_simbolius(string s);
void failo_isvedimas(map<string, int> zodziai);
