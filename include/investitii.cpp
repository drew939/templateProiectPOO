#include "investitii.h"
#include<iostream>
#include<string.h>
#include<vector>

std::ostream& operator<<(std::ostream& out, const ActivFinanciar& a)
{
    out << "[ActivFinanciar] ID=" << a.identificator
       << " | Pret=" << a.pretCurent << " RON"
       << " | Achizitionat=" << a.dataAchizitie;
    return out;
}

void Actiune::afisareDetalii() const
{
    std::cout << "  [Actiune] " << numeCompanie
              << " (ID: " << identificator << ")\n"
              << "    Nr. actiuni : " << numarActiuni << "\n"
              << "    Pret curent : " << pretCurent << " RON\n"
              << "    Achizitionat: " << dataAchizitie << "\n";
}

void Obligatiune::afisareDetalii() const
{
    std::cout << "  [Obligatiune] ID: " << identificator << "\n"
              << "    Dobanda anuala: " << dobandaAnuala << "%\n"
              << "    Durata        : " << durata << " luni\n"
              << "    Pret curent   : " << pretCurent << " RON\n"
              << "    Achizitionat  : " << dataAchizitie << "\n";
}

void TitluDeStat::afisareDetalii() const 
{
    std::cout << "  [TitluDeStat] ID: " << identificator << "\n"
              << "    Dobanda anuala: " << dobandaAnuala << "%\n"
              << "    Durata        : " << durata << " luni\n"
              << "    Pret curent   : " << pretCurent << " RON\n"
              << "    Achizitionat  : " << dataAchizitie << "\n";
}

void ActiuneFractionara::afisareDetalii() const 
{
    std::cout << "  [ActiuneFractionara] " << numeCompanie
              << " (ID: " << identificator << ")\n"
              << "    Fractiune     : " << fractiune << " actiuni\n"
              << "    Pret curent   : " << pretCurent << " RON\n"
              << "    Achizitionat  : " << dataAchizitie << "\n";
}

void FondMutualMixt::copiazaPortofoliu(const FondMutualMixt& other) 
{
    for(const auto* a : other.portofoliuActiuni)
        portofoliuActiuni.push_back(dynamic_cast<Actiune*>(a->clone()));
    for(const auto* o : other.portofoliuObligatiuni)
        portofoliuObligatiuni.push_back(dynamic_cast<Obligatiune*>(o->clone()));
    for(const auto* t : other.portofoliuTitluri)
        portofoliuTitluri.push_back(dynamic_cast<TitluDeStat*>(t->clone()));
}

void FondMutualMixt::stergePortofoliu() 
{
    for(const auto* a : portofoliuActiuni)    delete a;
    for(const auto* o : portofoliuObligatiuni) delete o;
    for(const auto* t : portofoliuTitluri)    delete t;
    portofoliuActiuni.clear();
    portofoliuObligatiuni.clear();
    portofoliuTitluri.clear();
}

FondMutualMixt::FondMutualMixt(const FondMutualMixt& other) :
        numeFond(other.numeFond), valoareTotala(other.valoareTotala),
        comisionAdministrare(other.comisionAdministrare) 
        {
            copiazaPortofoliu(other);   
        }

FondMutualMixt& FondMutualMixt::operator=(const FondMutualMixt& other)
{
    if (this == &other) return *this;
    stergePortofoliu();
    numeFond = other.numeFond;
    valoareTotala = other.valoareTotala;
    comisionAdministrare = other.comisionAdministrare;
    copiazaPortofoliu(other);
    return *this;
}

FondMutualMixt::~FondMutualMixt() 
{
    stergePortofoliu();
}

void FondMutualMixt::afisareDetalii() const 
{
    std::cout << "=== Fond Mutual: " << numeFond << " ===\n"
              << "  Valoare totala  : " << valoareTotala << " RON\n"
              << "  Comision admin  : " << comisionAdministrare << "%\n"
              << "  --- Actiuni (" << portofoliuActiuni.size() << ") ---\n";
    for(const auto* a : portofoliuActiuni)     a->afisareDetalii();
        std::cout << "  --- Obligatiuni (" << portofoliuObligatiuni.size() << ") ---\n";
    for(const auto* o : portofoliuObligatiuni) o->afisareDetalii();
        std::cout << "  --- Titluri de Stat (" << portofoliuTitluri.size() << ") ---\n";
    for(const auto* t : portofoliuTitluri)
        t->afisareDetalii();
}

std::ostream& operator<<(std::ostream& out, const FondMutualMixt& f)
{
    out << "[FondMutualMixt] " << f.numeFond
       << " | Valoare=" << f.valoareTotala << " RON"
       << " | Comision=" << f.comisionAdministrare << "%"
       << " | Actiuni=" << f.portofoliuActiuni.size()
       << " | Obligatiuni=" << f.portofoliuObligatiuni.size()
       << " | TitluriStat=" << f.portofoliuTitluri.size();
    return out;
}
