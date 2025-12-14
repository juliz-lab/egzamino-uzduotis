#include "mylib.h"

map<string, int> failo_nuskaitymas(const string &failas)
{
    map<string, int> zodziai;
    ifstream fd(failas);

    if (!fd)
    {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return {};
    }
    else
    {
        cout << "Nuskaitomas " << failas << endl;
        string eil;

        while (getline(fd, eil))
        {
            istringstream iss(eil); // eilute paverciam i duomenu srauta
            string zodis;

            while (iss >> zodis)
            {
                zodis = naikinti_simbolius(zodis);
                if (zodis != "")
                {
                    if (zodziai.find(zodis) == zodziai.end())
                    {
                        zodziai.insert({zodis, 0});
                        zodziai[zodis] += 1;
                    }
                    else
                    {
                        zodziai[zodis] += 1;
                    }
                }
            }
        }
    }
    return zodziai;
}

bool ar_leistina_raide(string c)
{
    vector<string> lietuviskos = {"Ą", "ą", "Č", "č", "Ę", "ę", "Ė", "ė", "Į", "į", "Š", "š", "Ų", "ų", "Ū", "ū", "Ž", "ž"};
    if (c.size() == 1 && isalpha(c[0]) != 0)
    {
        return true;
    }
    for (auto l : lietuviskos)
    {
        if (c == l)
        {
            return true;
        }
    }
    return false;
}

string naikinti_simbolius(string s)
{
    string rezultatas;

    for (int i = 0; i < s.size();)
    {
        unsigned char c = s[i];
        int ilg = 1;

        if (c <= 0x7F)
        {
            ilg = 1;
        }
        else if (c >= 0xC0 && c <= 0xDF)
        {
            ilg = 2;
        }
        else if (c >= 0xE0 && c <= 0xEF)
        {
            ilg = 3;
        }
        else if (c >= 0xF0 && c <= 0xF7)
        {
            ilg = 4;
        }
        string simbolis = s.substr(i, ilg);

        if (ar_leistina_raide(simbolis))
        {
            rezultatas += simbolis;
        }
        i += ilg;
    }
    return rezultatas;
}

void failo_isvedimas(map<string, int> zodziai)
{
    ofstream fr("rezultatai.txt");
    for (auto z : zodziai)
    {
        if (z.second > 1)
        {
            fr << z.first << ": " << z.second << endl;
        }
    }
    cout << "Failai isvesti." << endl;
    fr.close();
}
