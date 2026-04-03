#include "card.h"
#include<iostream>
#include<string.h>
#include<vector>

std::ostream& operator<<(std::ostream& out, const CardBancar& c) 
{
    out << "[Card] Titular=" << c.titularCard
       << " | Valuta=" << c.valuta
       << " | Operator=" << c.operatorPlati
       << " | Activat=" << (c.activat ? "DA" : "NU")
       << " | Blocat="  << (c.blocat  ? "DA" : "NU")
       << " | LimitaTranzactii=" << c.limitaTranzactii;
    return out;
}

void CardDebit::afisareDetalii() const
{
    std::cout << "  [CardDebit]\n"
              << "    Titular             : " << titularCard << "\n"
              << "    Valuta              : " << valuta << "\n"
              << "    Operator            : " << operatorPlati << "\n"
              << "    Limita retragere    : " << limitaRetragere << " " << valuta << "\n"
              << "    Plati internationale: " << (platiInternationale ? "DA" : "NU") << "\n"
              << "    Activat / Blocat    : " << (activat ? "DA" : "NU")
              << " / " << (blocat ? "DA" : "NU") << "\n";
}


void CardCredit::afisareDetalii() const
{
    std::cout << "  [CardCredit]\n"
              << "    Titular          : " << titularCard << "\n"
              << "    Valuta           : " << valuta << "\n"
              << "    Operator         : " << operatorPlati << "\n"
              << "    Limita credit    : " << limitaCredit << " " << valuta << "\n"
              << "    Dobanda          : " << dobanda << "%\n"
              << "    Suma minima plata: " << sumaMinimaPlata << " " << valuta << "\n"
              << "    Scadenta lunara  : " << dataScadentaLunara << "\n"
              << "    Activat / Blocat : " << (activat ? "DA" : "NU")
              << " / " << (blocat ? "DA" : "NU") << "\n";
}


void CardOverdraft::afisareDetalii() const
{
    std::cout << "  [CardOverdraft]\n"
              << "    Titular          : " << titularCard << "\n"
              << "    Valuta           : " << valuta << "\n"
              << "    Limita retragere : " << limitaRetragere << " " << valuta << "\n"
              << "    Limita credit    : " << limitaCredit << " " << valuta << "\n"
              << "    Taxa depasire    : " << taxaDepasireLimita << " " << valuta << "\n"
              << "    Activat / Blocat : " << (activat ? "DA" : "NU")
              << " / " << (blocat ? "DA" : "NU") << "\n";
}


void CardVirtual::afisareDetalii() const
{
    std::cout << "  [CardVirtual]\n"
              << "    Titular     : " << titularCard << "\n"
              << "    Valuta      : " << valuta << "\n"
              << "    Single-use  : " << (singleUse ? "DA" : "NU") << "\n"
              << "    Activ/Blocat: " << (activat ? "DA" : "NU")
              << " / " << (blocat ? "DA" : "NU") << "\n";
}


void CardPrepaid::afisareDetalii() const
{
    std::cout << "  [CardPrepaid]\n"
              << "    Titular              : " << titularCard << "\n"
              << "    Valuta               : " << valuta << "\n"
              << "    Limita incarcare/luna: " << limitaIncarcareLunara << " " << valuta << "\n"
              << "    Single-use           : " << (singleUse ? "DA" : "NU") << "\n"
              << "    Activ/Blocat         : " << (activat ? "DA" : "NU")
              << " / " << (blocat ? "DA" : "NU") << "\n";
}
