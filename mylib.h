#include <iomanip>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <cctype>
#include <regex>

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
using std::setw;
using std::left;
using std::regex;

struct zodzioInfo{
    int kiekis = 0;
    vector<int> eil;
};

map<string, zodzioInfo> failo_nuskaitymas(const string &failas);
bool ar_leistina_raide(string c);
string naikinti_simbolius(string s);
void failo_isvedimas(map<string, zodzioInfo> zodziai);
vector<string> url_nuskaitymas(const string &failas);
vector<string> nuorodu_paieska(const string &failas, const vector<string>& galai);
void nuorodu_isvedimas(const vector<string> &nuorodos);
bool regex_patikra(const string &zodis, const regex &r);
regex regex_sablonas(const vector<string> &galai);
