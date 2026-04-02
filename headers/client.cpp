#include "client.h"
#include <iostream>
#include <stdexcept>


void Client::copiazaDate(const Client& other) 
{
    for (auto* cont : other.conturi)
        conturi.push_back(cont->clone());
    for (auto* imp : other.imprumuturi)
        imprumuturi.push_back(imp->clone());
    for (auto* card : other.carduri)
        carduri.push_back(card->clone());
}

void Client::stergeDate()
{
    for (auto* cont : conturi)
		delete cont;
    for (auto* imp  : imprumuturi)
		delete imp;
    for (auto* card : carduri)	
		delete card;
    conturi.clear();
    imprumuturi.clear();
    carduri.clear();
}

Client::Client(const Client& other) : nume(other.nume), email(other.email), telefon(other.telefon)
{
    copiazaDate(other);
}

Client& Client::operator=(const Client& other)
{
    if (this == &other) 
		return *this;
    stergeDate();
    nume = other.nume;
    email = other.email;
    telefon = other.telefon;
    copiazaDate(other);
    return *this;
}

Client::~Client()
{
    stergeDate();
}

ContBancar* Client::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(conturi.size()))
        throw std::out_of_range("Index cont invalid: " + std::to_string(index));
    return conturi[index];
}

const ContBancar* Client::operator[](int index) const
{
    if (index < 0 || index >= static_cast<int>(conturi.size()))
        throw std::out_of_range("Index cont invalid: " + std::to_string(index));
    return conturi[index];
}

void Client::stergeCont(int index)
{
    if (index < 0 || index >= static_cast<int>(conturi.size()))
        throw std::out_of_range("Index cont invalid: " + std::to_string(index));
    delete conturi[index];
    conturi.erase(conturi.begin() + index);
}


std::ostream& operator<<(std::ostream& out, const Client& c)
{
    out << "[Client] Nume=" << c.nume
       << " | Email=" << c.email
       << " | Telefon=" << c.telefon
       << " | Conturi=" << c.conturi.size()
       << " | Imprumuturi=" << c.imprumuturi.size()
       << " | Carduri=" << c.carduri.size();
    return out;
}

ClientPersoanaFizica::ClientPersoanaFizica(std::string _nume, std::string _prenume, std::string _email, std::string _telefon, std::string _cnp, int _varsta) :
			Client(std::move(_nume), std::move(_email), std::move(_telefon)), prenume(std::move(_prenume)), cnp(std::move(_cnp))
			{
				if (_varsta < 18)
					throw ExceptieVarstaInvalida(
						"Clientul " + prenume + " " + nume +
						" are " + std::to_string(_varsta) +
						" ani – minim 18 ani pentru deschidere cont!"
						);
				varsta = _varsta;
			}

void ClientPersoanaFizica::afisareDetalii() const
{
    std::cout << "=== CLIENT PERSOANA FIZICA ===\n"
              << "  Nume complet : " << prenume << " " << nume << "\n"
              << "  CNP          : " << cnp << "\n"
              << "  Varsta       : " << varsta << " ani\n"
              << "  Email        : " << email << "\n"
              << "  Telefon      : " << telefon << "\n"
              << "  --- Conturi (" << conturi.size() << ") ---\n";
    for (auto* cont : conturi)
		cont->afisareDetalii();
    std::cout << "  --- Imprumuturi (" << imprumuturi.size() << ") ---\n";
    for (auto* imp  : imprumuturi)
		imp->afisareDetalii();
    std::cout << "  --- Carduri (" << carduri.size() << ") ---\n";
    for (auto* card : carduri)
		card->afisareDetalii();
}

void ClientPersoanaJuridica::afisareDetalii() const
{
    std::cout << "=== CLIENT PERSOANA JURIDICA ===\n"
              << "  Denumire    : " << nume << "\n"
              << "  Tip entitate: " << tipEntitate << "\n"
              << "  CUI         : " << cui << "\n"
              << "  Email       : " << email << "\n"
              << "  Telefon     : " << telefon << "\n"
              << "  --- Conturi (" << conturi.size() << ") ---\n";
    for (auto* cont : conturi)    
		cont->afisareDetalii();
    std::cout << "  --- Imprumuturi (" << imprumuturi.size() << ") ---\n";
    for (auto* imp  : imprumuturi) 
		imp->afisareDetalii();
    std::cout << "  --- Carduri (" << carduri.size() << ") ---\n";
    for (auto* card : carduri)    
		card->afisareDetalii();
}

