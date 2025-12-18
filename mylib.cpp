#include "mylib.h"

map<string, zodzioInfo> failo_nuskaitymas(const string &failas)
{
    map<string, zodzioInfo> zodziai;
    ifstream fd(failas);
    int eil_nr = 0;

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
            eil_nr += 1;
            istringstream iss(eil); // eilute paverciam i duomenu srauta
            string zodis;

            while (iss >> zodis)
            {
                zodis = naikinti_simbolius(zodis);
                if (zodis != "")
                {
                    if (zodziai.find(zodis) == zodziai.end())
                    {
                        zodziai[zodis].kiekis++;
                        zodziai[zodis].eil.push_back(eil_nr);
                    }
                    else
                    {
                        zodziai[zodis].kiekis += 1;
                        zodziai[zodis].eil.push_back(eil_nr);
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
        string simbolis = s.substr(i, ilg);

        if (ar_leistina_raide(simbolis))
        {
            rezultatas += simbolis;
        }
        i += ilg;
    }
    return rezultatas;
}

void failo_isvedimas(map<string, zodzioInfo> zodziai)
{
    ofstream fr("pasikartojantys_zodziai.txt");
    fr << setw(25) << left << "Žodis" << setw(25) << left << "Pasikartojimų sk." << setw(20) << left << "Eilučių nr." << endl;
    for (const auto &z : zodziai)
    {
        if (z.second.kiekis > 1)
        {
            fr << left << setw(25) << z.first << left << setw(25) << z.second.kiekis << left;
            for (int i = 0; i < z.second.eil.size(); i++)
            {
                fr << z.second.eil[i] << " ";
            }
            fr << endl;
        }
    }
    cout << "Žodžiai išvesti faile pasikartojantys_zodziai.txt." << endl;
    fr.close();
}

vector<string> url_nuskaitymas(const string &failas)
{
    vector<string> galai;
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
            galai.push_back(eil);
        }
    }
    return galai;
}

vector<string> nuorodu_paieska(const string &failas, const vector<string> &galai)
{
    vector<string> nuorodos;
    ifstream fd(failas);
    if (!fd)
    {
        cout << "Nepavyko atidaryti failo: " << failas << endl;
        return nuorodos;
    }
    else
    {
        string eil;
        regex r = regex_sablonas(galai);

        cout << "Pradedama nuorodų paieška." << endl;
        while (getline(fd, eil))
        {
            istringstream iss(eil);
            string zodis;
            while (iss >> zodis)
            {
                while (!zodis.empty() && ispunct(zodis.front()))
                {
                    zodis.erase(zodis.begin());
                }
                while (!zodis.empty() && ispunct(zodis.back()))
                {
                    zodis.pop_back();
                }
                if (regex_patikra(zodis, r))
                {
                    nuorodos.push_back(zodis);
                }
            }
        }
    }
    return nuorodos;
}

bool regex_patikra(const string &zodis, const regex &r)
{
    return regex_match(zodis, r);
}

regex regex_sablonas(const vector<string> &galai)
{
    string sablonas = R"((https?://)?(www\.)?\S+\.()";

    for (size_t i = 0; i < galai.size(); i++)
    {
        sablonas += galai[i];
        if (i + 1 < galai.size())
        {
            sablonas += "|";
        }
    }
    sablonas += R"()(\b[^\[\(\s]+)?)";
    regex r(sablonas, regex::icase);
    return r;
}

void nuorodu_isvedimas(const vector<string> &nuorodos)
{
    ofstream fr("nuorodos.txt");
    for (const auto &n : nuorodos)
    {
        fr << n << endl;
    }
    cout << "Nuorodos išvestos faile nuorodos.txt." << endl;
    fr.close();
}
