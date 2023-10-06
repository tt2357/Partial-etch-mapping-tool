#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

vector<int> wczytaj(string plik) 
{
    vector<int> vect;
    ifstream file(plik + ".txt");
    int x;
    while (file >> x) {
        vect.push_back(x);
    }
    return vect;
}

int dwumian(int n, int k) 
{
    int wynik = 1;
    for (int i = 0; i < k; i++) 
    {
        wynik = wynik * (n-i) / (i+1);
    }
    return wynik;
}

int sprawdzanie(int k, vector<int> vect) 
{
    for (int k = 5; k < 15; k++)
    {
        if (dwumian(k+2,2) == vect.size())
        {
            return k;
        }
    }
    cout << "NIE ZNALEZIONO K" << endl;
    return 0;
}

bool sprawdzenie_roznicy(vector<int> vect)
{
    for(int i = 0; i<vect.size(); i++)
    {
        if (vect[i] == vect[vect.size()-1] - vect[vect.size()-2])
        {
            return true;
        }
    }
    return false;
}

void sprawdz_i_zaktualizuj(vector<int>&vect, vector<int>&vect2, vector<int>&uzyte, bool &sprawdz1)
{
    vector<int> sumy;
    for (int j = 0; j < vect2.size(); j++) 
    {
        for (int k = j; k < vect2.size(); k++) 
        {
            int suma = 0;
            for (int l = j; l <= k; l++) 
            {
                suma += vect2[l];
            }
            sumy.push_back(suma);
        }
    }
    bool znajdujesie = true;
    for(auto x : sumy)
    {
        if(find(vect.begin(), vect.end(), x) == vect.end())
        {
            znajdujesie = false;
            break;
        }
    }
    if(znajdujesie)
    {
        sprawdz1=true;
        for(int k=0; k<sumy.size();k++)
        {
            for(int l = 0; l<vect.size();l++)
            {
                if(vect[l]==sumy[k] && uzyte[l]==0)
                {
                    uzyte[l]=1;
                    break;
                }
            }
        }
        sumy.clear();
    }
    else
    {
        sprawdz1 = false;
        sumy.clear();
    }
}

bool czywszystkie(vector<int> uzyte)
{
    for(int i = 0; i<uzyte.size(); i++)
    {
        if(uzyte[i]==0)
        {
            return false;
        }
    }
    return true;
}

void wyzeruj(vector<int>&uzyte)
{
    for(int i = 0; i<uzyte.size(); i++)
    {
        uzyte[i]=0;
    }
}


void szukaj_mapy(vector<int> &vect, int x, int ind, vector<int> &vect2, vector<int> &uzyte) 
{
    bool sprawdz1 = true;
    wyzeruj(uzyte);
    sprawdz_i_zaktualizuj(vect,vect2,uzyte, sprawdz1);
    if (ind == x+1 && czywszystkie(uzyte)) 
    {
        cout<<endl<<"ZNALEZIONO MAPE"<<endl;
        for(int i = 0; i<vect2.size(); i++)
        {
            cout<<vect2[i]<<" ";
        }
        return;
    }

    for(int i = 0; i<vect.size(); i++)
    {
        if(uzyte[i]==1)
        {
            continue;
        }
        if(uzyte[i]==0)
        {
            vect2.push_back(vect[i]);
        }
        sprawdz_i_zaktualizuj(vect,vect2,uzyte, sprawdz1);
        if(sprawdz1)
        {
            // for(int j = 0; j<vect2.size();j++)
            // {
            //     cout<<vect2[j]<<" ";
            // }
            // cout<<endl;
            wyzeruj(uzyte);
            szukaj_mapy(vect,x,ind+1,vect2,uzyte);
        }
        else
        {
            vect2.pop_back();
        }
    }
    vect2.pop_back();

}
int main() 
{
    int k;
    int ind = 0;
    double czas;
    clock_t start, koniec;
    string nazwapliku;
    cout<<"Podaj nazwe pliku: (bez '.txt')"<<endl;
    cin >> nazwapliku;
    vector<int> mapa;
    vector<int> uzyte;
    vector<int> vect = wczytaj(nazwapliku);
    sort(vect.begin(), vect.end());
    for(int i = 0; i<vect.size(); i++)
    {
        uzyte.push_back(0);
    }
    mapa.push_back(vect[vect.size()-1] - vect[vect.size()-2]);

    if(!sprawdzenie_roznicy(vect))
    {
        cout << "ROZNICA NIE ZNALEZIONA" << endl;
    }
    k = sprawdzanie(k, vect);
    start = clock();
    szukaj_mapy(vect,k,ind+1,mapa,uzyte);
    koniec = clock();

    cout<<endl<<"Czas wykonwyania algorytmu: "<<(double)(koniec-start)/CLOCKS_PER_SEC<<" s"<<endl;
    return 0;
}