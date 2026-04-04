#include "cont.h"
#include "exceptii.h"
#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include<ostream>

int ContBancar::contorIban = 100200001100;

std::string ContBancar::generareIban() 
{
    return "RO49AAAA" + std::to_string(contorIban++);
}

void ContBancar::depune(double suma) 
{
    if (suma <= 0)
        throw ExceptieSumaInvalida("Suma trebuie sa fie strict pozitiva!");
    sold += suma;
}

void ContBancar::retrage(double suma) 
{
    if (suma <= 0)
        throw ExceptieSumaInvalida("Suma de retras trebuie sa fie strict pozitiva!");
    if (sold < suma)
        throw ExceptieFonduriInsuficiente(
            "Fonduri insuficiente! Sold=" + std::to_string(sold) + " RON, cerut=" + std::to_string(suma) + " RON");
    sold -= suma;
}

std::ostream& operator<<(std::ostream& out, const ContBancar& c) 
{
    out << "[Cont] IBAN=" << c.iban
       << " | Valuta=" << c.valuta
       << " | Sold=" << c.sold
       << " | Titular=" << c.titularCont
       << " | Stare=" << c.stareCont;
    return out;
}


void ContCurent::retrage(double suma) 
{
    if (suma <= 0)
        throw ExceptieSumaInvalida("Suma de retras trebuie sa fie strict pozitiva!");

    if (sold - suma < -limitaDescoperire)
        throw ExceptieFonduriInsuficiente("Retragerea depaseste limita de descoperire ("+ std::to_string(limitaDescoperire) + " RON)!");
    sold -= suma;
}

void ContCurent::afisareDetalii() const 
{
    std::cout << "  [ContCurent] IBAN: " << iban << "\n"
              << "    Valuta              : " << valuta << "\n"
              << "    Sold                : " << sold << " " << valuta << "\n"
              << "    Titular             : " << titularCont << "\n"
              << "    Stare               : " << stareCont << "\n"
              << "    Comision adm.       : " << comisionAdministrare << " " << valuta << "/luna\n"
              << "    Limita descoperire  : " << limitaDescoperire << " " << valuta << "\n";
}


void ContEconomii::aplicaDobanda() 
{
    sold += sold * (dobanda / 100.0);
}

void ContEconomii::afisareDetalii() const 
{
    std::cout << "  [ContEconomii] IBAN: " << iban << "\n"
              << "    Valuta         : " << valuta << "\n"
              << "    Sold           : " << sold << " " << valuta << "\n"
              << "    Titular        : " << titularCont << "\n"
              << "    Dobanda        : " << dobanda << "%\n"
              << "    Sold minim     : " << soldMinim << " " << valuta << "\n"
              << "    Zi capitalizare: " << ziCapitalizare << "\n";
}


void ContCurentAcumulare::afisareDetalii() const
{
    std::cout << "  [ContCurentAcumulare] IBAN: " << iban << "\n"
              << "    Valuta           : " << valuta << "\n"
              << "    Sold             : " << sold << " " << valuta << "\n"
              << "    Titular          : " << titularCont << "\n"
              << "    Comision adm.    : " << comisionAdministrare << " " << valuta << "/luna\n"
              << "    Limita descoperire: " << limitaDescoperire << " " << valuta << "\n"
              << "    Dobanda acumulare: " << dobanda << "%\n";
}


void ContRoundUp::afisareDetalii() const 
{
    std::cout << "  [ContRoundUp] IBAN: " << iban << "\n"
              << "    Valuta          : " << valuta << "\n"
              << "    Sold            : " << sold << " " << valuta << "\n"
              << "    Multiplicator   : " << multiplicatorRotunjire << "x\n"
              << "    IBAN sursa      : " << ibanContSursa << "\n"
              << "    Dobanda         : " << dobanda << "%\n";
}

void DepozitBancar::retrage(double suma) 
{
    if (suma <= 0)
        throw ExceptieSumaInvalida("Suma de retras trebuie sa fie strict pozitiva!");
    if (sold < suma)
        throw ExceptieFonduriInsuficiente("Fonduri insuficiente in depozit!");

    double penalizare = suma * 0.10;
    std::cout << "  [INFO] Retragere anticipata depozit – penalizare: "
              << penalizare << " " << valuta << "\n";
    sold -= (suma + penalizare);
    if (sold < 0) sold = 0;
}

void DepozitBancar::afisareDetalii() const 
{
    std::cout << "  [DepozitBancar] IBAN: " << iban << "\n"
              << "    Valuta              : " << valuta << "\n"
              << "    Sold                : " << sold << " " << valuta << "\n"
              << "    Titular             : " << titularCont << "\n"
              << "    Dobanda             : " << dobanda << "%\n"
              << "    Termen              : " << termen << " luni\n"
              << "    Data maturitate     : " << dataMaturitate << "\n"
              << "    Prelungire automata : " << (prelungireAutomata ? "DA" : "NU") << "\n";
}


ContInvestitii::ContInvestitii(const ContInvestitii& other) : 
        ContBancar(other.valuta, other.sold), randament(other.randament),
        investitieInitiala(other.investitieInitiala), gradRisc(other.gradRisc) 
            {
                for(auto* activ : other.portofoliu)
                    portofoliu.push_back(activ->clone());
            }

ContInvestitii& ContInvestitii::operator=(const ContInvestitii& other)
{
    if (this == &other) 
        return *this;
    for (auto* activ : portofoliu) 
        delete activ;
    portofoliu.clear();
    valuta = other.valuta;
    sold = other.sold;
    randament = other.randament;
    investitieInitiala = other.investitieInitiala;
    gradRisc = other.gradRisc;
    for (auto* activ : other.portofoliu)
        portofoliu.push_back(activ->clone());
    return *this;
}

ContInvestitii::~ContInvestitii() 
{
    for (auto* activ : portofoliu) 
        delete activ;
}

void ContInvestitii::afisareDetalii() const 
{
    std::cout << "  [ContInvestitii] IBAN: " << iban << "\n"
              << "    Valuta              : " << valuta << "\n"
              << "    Sold                : " << sold << " " << valuta << "\n"
              << "    Titular             : " << titularCont << "\n"
              << "    Investitie initiala : " << investitieInitiala << " " << valuta << "\n"
              << "    Randament           : " << randament << "%\n"
              << "    Grad risc           : " << gradRisc << "\n"
              << "    Portofoliu (" << portofoliu.size() << " active):\n";
    for (auto* activ : portofoliu)
        activ->afisareDetalii();
}

void ContBusiness::afisareDetalii() const 
{
    std::cout << "  [ContBusiness] IBAN: " << iban << "\n"
              << "    Valuta       : " << valuta << "\n"
              << "    Sold         : " << sold << " " << valuta << "\n"
              << "    Titular      : " << titularCont << "\n"
              << "    Imputerniciti: ";
    for (const auto& imp : imputerniciti)
        std::cout << imp << "; ";
    std::cout << "\n";
}

void ContSweep::afisareDetalii() const {
    std::cout << "  [ContSweep] IBAN: " << iban << "\n"
              << "    Valuta           : " << valuta << "\n"
              << "    Sold             : " << sold << " " << valuta << "\n"
              << "    Titular          : " << titularCont << "\n"
              << "    Prag transfer    : " << prag << " " << valuta << "\n"
              << "    Frecventa surplus: " << frecventaSurplus << "\n"
              << "    Dobanda          : " << dobanda << "%\n";
}
