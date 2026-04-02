#include "imprumut.h"
#include<iostream>


std::ostream& operator<<(std::ostream& out, const Imprumut& i)
{
    out << "[Imprumut]"
       << " Suma=" << i.sumaCreditata << " RON"
       << " | Rata=" << i.rataLunara << " RON/luna"
       << " | Dobanda=" << i.dobandaAnuala << "%"
       << " | SoldRamas=" << i.soldRamasDePlata << " RON"
       << " | Scadenta=" << i.scadenta;
    return out;
}

void CreditGarantat::afisareDetalii() const
{
    std::cout << "  [CreditGarantat]\n"
              << "    Suma creditata : " << sumaCreditata    << " RON\n"
              << "    Rata lunara    : " << rataLunara       << " RON\n"
              << "    Dobanda anuala : " << dobandaAnuala    << "%\n"
              << "    Sold ramas     : " << soldRamasDePlata << " RON\n"
              << "    Scadenta       : " << scadenta         << "\n"
              << "    Bun garantat   : " << bunGarantat      << "\n"
              << "    Val. garantie  : " << valoareGarantie  << " RON\n";
}

void CreditRefinantare::afisareDetalii() const
{
    std::cout << "  [CreditRefinantare]\n"
              << "    Suma creditata  : " << sumaCreditata    << " RON\n"
              << "    Rata lunara     : " << rataLunara       << " RON\n"
              << "    Dobanda anuala  : " << dobandaAnuala    << "%\n"
              << "    Sold ramas      : " << soldRamasDePlata << " RON\n"
              << "    Banca initiala  : " << bancaInitiala    << "\n"
              << "    Suma refinantata: " << sumaRefinantata  << " RON\n";
}

void RefinantareIpotecara::afisareDetalii() const
{
    std::cout << "  [RefinantareIpotecara]\n"
              << "    Suma creditata  : " << sumaCreditata    << " RON\n"
              << "    Rata lunara     : " << rataLunara       << " RON\n"
              << "    Dobanda anuala  : " << dobandaAnuala    << "%\n"
              << "    Sold ramas      : " << soldRamasDePlata << " RON\n"
              << "    Bun garantat    : " << bunGarantat      << "\n"
              << "    Val. garantie   : " << valoareGarantie  << " RON\n"
              << "    Banca initiala  : " << bancaInitiala    << "\n"
              << "    Suma refinantata: " << sumaRefinantata  << " RON\n";
}

void CreditNevoiPersonale::afisareDetalii() const 
{
    std::cout << "  [CreditNevoiPersonale]\n"
              << "    Suma creditata: " << sumaCreditata    << " RON\n"
              << "    Rata lunara   : " << rataLunara       << " RON\n"
              << "    Dobanda anuala: " << dobandaAnuala    << "%\n"
              << "    Sold ramas    : " << soldRamasDePlata << " RON\n"
              << "    Scadenta      : " << scadenta         << "\n";
}

void LeasingAuto::afisareDetalii() const {
    std::cout << "  [LeasingAuto]\n"
              << "    Suma creditata: " << sumaCreditata    << " RON\n"
              << "    Rata lunara   : " << rataLunara       << " RON\n"
              << "    Dobanda anuala: " << dobandaAnuala    << "%\n"
              << "    Sold ramas    : " << soldRamasDePlata << " RON\n"
              << "    Autovehicul   : " << bunGarantat      << "\n"
              << "    Val. garantie : " << valoareGarantie  << " RON\n";
}

