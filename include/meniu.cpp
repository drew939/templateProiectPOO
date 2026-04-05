#include "meniu.h"
#include <iostream>
#include <limits>


Meniu& Meniu::getInstance() 
{
    static Meniu instance;
    return instance;
}

Meniu::~Meniu() 
{
    for(const auto* client : listaClienti)
        delete client;
}


void Meniu::afiseazaSeparator() 
{
    std::cout << "--------------------------------------------\n";
}

void Meniu::adaugaClient(Client* client) 
{
    listaClienti.push_back(client);
    std::cout << "Client adaugat: " << *client << "\n";
}

Client* Meniu::cautaClientDupaId(const std::string& id) 
{
    for (auto* client : listaClienti)
        if (client->getIdentificator() == id) return client;
    throw ExceptieClientNegasit("Nu exista client cu identificatorul: " + id);
}

void Meniu::stergeClient(const std::string& id) 
{
    for (auto it = listaClienti.begin(); it != listaClienti.end(); ++it) 
    {
        if ((*it)->getIdentificator() == id) 
        {
            delete *it;
            listaClienti.erase(it);
            std::cout << "Clientul cu ID=" << id << " a fost sters.\n";
            return;
        }
    }
    throw ExceptieClientNegasit("Nu exista client cu identificatorul: " + id);
}

void Meniu::afiseazaTotiClientii() const 
{
    if (listaClienti.empty()) {
        std::cout << "Nu exista clienti in baza de date.\n";
        return;
    }
    afiseazaSeparator();
    for (size_t i = 0; i < listaClienti.size(); i++) 
    {
        std::cout << i + 1 << ". ";
        listaClienti[i]->afisareDetalii();
        afiseazaSeparator();
    }
}


void Meniu::deschideCont(const std::string& idClient, ContBancar* cont) 
{
    if (cont == nullptr) {
        throw std::invalid_argument("nullptr to ContBancar");
    }
    if (idClient.empty()) {
        throw std::invalid_argument("idClient cannot be empty");
    }
    try {
        Client* client = cautaClientDupaId(idClient);
        cont->setTitular(client->getNume());
        client->adaugaCont(cont);
        std::cout << "Cont deschis: " << *cont << "\n";
    } catch (const ExceptieClientNegasit& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
        delete cont;
    }
}

void Meniu::efectueazaDepunere(const std::string& idClient, int indexCont, double suma) 
{
    try {
        Client* client = cautaClientDupaId(idClient);
        ContBancar* cont = (*client)[indexCont];

        *cont += suma;
        std::cout << "Depunere " << suma << " " << cont->getValuta()
                  << " efectuata. Sold nou: " << cont->getSold() << "\n";

    } catch (const ExceptieSumaInvalida& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    } catch (const ExceptieClientNegasit& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    }
}

void Meniu::efectueazaRetragere(const std::string& idClient, int indexCont, double suma) 
{
    try {
        Client* client = cautaClientDupaId(idClient);
        ContBancar* cont = (*client)[indexCont];   
        
        ContCurentAcumulare* cca = dynamic_cast<ContCurentAcumulare*>(cont);
        if (cca != nullptr) 
        {
            std::cout << "Cont Curent cu Acumulare detectat.\n"
                      << "Dobanda activa: " << cca->getDobanda() << "%\n"
                      << "Limita descoperire: "
                      << cca->getLimitaDescoperire() << " " << cca->getValuta() << "\n";
        }

        const ContInvestitii* ci = dynamic_cast<ContInvestitii*>(cont);
        if (ci != nullptr) 
        {
            std::cout << "Cont Investitii detectat."
                      << "Randament: " << ci->getRandament() << "%"
                      << "|Active portofoliu: " << ci->getDimensiunePortofoliu() << "\n";
        }

        cont->retrage(suma);
        std::cout << "Retragere " << suma << " " << cont->getValuta()
                  << " efectuata. Sold nou: " << cont->getSold() << "\n";

    } catch (const ExceptieFonduriInsuficiente& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    } catch (const ExceptieSumaInvalida& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    } catch (const ExceptieClientNegasit& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    } catch (const std::out_of_range& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    }
}

void Meniu::meniuAdaugaClient() 
{
    int tip;
    std::cout << "Tip client (1=Persoana Fizica, 2=Persoana Juridica): ";
    std::cin >> tip;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string nume, email, telefon;
    std::cout << "Nume: "; 
    std::getline(std::cin, nume);
    std::cout << "Email: "; 
    std::getline(std::cin, email);
    std::cout << "Telefon: "; 
    std::getline(std::cin, telefon);

    try {
        if (tip == 1) 
        {
            std::string prenume, cnp;
            int varsta;
            std::cout << "Prenume: "; std::getline(std::cin, prenume);
            std::cout << "CNP: "; std::getline(std::cin, cnp);
            std::cout << "Varsta: "; std::cin >> varsta;
            auto* c = new ClientPersoanaFizica(nume, prenume, email, telefon, cnp, varsta);
            adaugaClient(c);
        } else {
            std::string tipEnt, cui;
            std::cout << "Tip entitate (SRL/SA/RA/etc): ";
            std::getline(std::cin, tipEnt);
            std::cout << "CUI: ";
            std::getline(std::cin, cui);
            auto* c = new ClientPersoanaJuridica(nume, email, telefon, tipEnt, cui);
            adaugaClient(c);
        }
    } catch (const ExceptieVarstaInvalida& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    }
}

void Meniu::meniuCautaClient() 
{
    std::string id;
    std::cout << "Introdu CNP sau CUI: ";
    std::cin >> id;
    try {
        const Client* c = cautaClientDupaId(id);
        std::cout << "\n";
        c->afisareDetalii();
    } catch (const ExceptieClientNegasit& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    }
}

void Meniu::meniuStergeClient() 
{
    std::string id;
    std::cout << "Introdu CNP sau CUI al clientului care va fi sters: ";
    std::cin >> id;
    try {
        stergeClient(id);
    } catch (const ExceptieClientNegasit& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    }
}


void Meniu::meniuDeschideCont(Client* client)
{
    afiseazaSeparator();
    std::cout << "Tip cont:\n"
              << "  1. ContCurent\n"
              << "  2. ContEconomii\n"
              << "  3. ContCurentAcumulare\n"
              << "  4. DepozitBancar\n"
              << "  5. ContInvestitii\n"
              << "  6. ContBusiness\n"
              << "Optiune: ";
    int tip; 
    std::cin >> tip;

    std::string valuta;
    double soldInitial;
    std::cout << "Valuta (RON/EUR/USD): "; 
    std::cin >> valuta;
    std::cout << "Sold initial: "; 
    std::cin >> soldInitial;

    ContBancar* cont = nullptr;
    try {
        switch (tip) {
            case 1: cont = new ContCurent(valuta, soldInitial);
                break;
            case 2: cont = new ContEconomii(valuta, soldInitial, 2.5);
                break;
            case 3: cont = new ContCurentAcumulare(valuta, soldInitial); 
                break;
            case 4: { 
                int termen; std::cout << "Termen (luni): "; 
                std::cin >> termen;
                cont = new DepozitBancar(valuta, soldInitial, termen); 
                    break;}
            case 5: { 
                double rand; std::cout << "Randament (%): "; 
                std::cin >> rand;
                cont = new ContInvestitii(valuta, soldInitial, rand); 
                    break;}
            case 6: cont = new ContBusiness(valuta, soldInitial); 
                break;
            default: std::cout << "Optiune invalida.\n"; 
            return;
        }
        cont->setTitular(client->getNume());
        client->adaugaCont(cont);
        std::cout << "[OK] " << *cont << "\n";
    } catch (const ExceptieSumaInvalida& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
        delete cont;
    }
}

void Meniu::meniuOperatiuniCont(Client* client) 
{
    if (client->getNumarConturi() == 0)
    {
        std::cout << "Clientul nu are conturi.\n";
        return;
    }
    std::cout << "Conturi disponibile:\n";
    for (int i = 0; i < client->getNumarConturi(); i++) 
        std::cout << "  " << i << ". " << *(*client)[i] << "\n";
    int idx; double suma;
    std::cout << "Index cont: ";
    std::cin >> idx;
    std::cout << "1=Depunere, 2=Retragere: ";
    int op; 
    std::cin >> op;
    std::cout << "Suma: "; 
    std::cin >> suma;

    const std::string id = client->getIdentificator();
    if (op == 1) 
        efectueazaDepunere(id, idx, suma);
    else 
        efectueazaRetragere(id, idx, suma);
}

void Meniu::meniuOperatiuniClient() 
{
    std::string id;
    std::cout << "Introdu CNP sau CUI: ";
    std::cin >> id;
    try {
        Client* client = cautaClientDupaId(id);
        int opt;
        std::cout << "1. Afiseaza detalii\n"
                  << "2. Deschide cont\n"
                  << "3. Operatiune cont\n"
                  << "Optiune: ";
        std::cin >> opt;
        switch (opt) {
            case 1: client->afisareDetalii();
                break;
            case 2: meniuDeschideCont(client); 
                break;
            case 3: meniuOperatiuniCont(client);
                break;
            default: std::cout << "Optiune invalida.\n";
        }
    } catch (const ExceptieClientNegasit& e) {
        std::cerr << "[EROARE] " << e.what() << "\n";
    }
}


void Meniu::meniuPrincipal()
{
    int opt;
    do {
        afiseazaSeparator();
        std::cout << "  SISTEM BANKING\n";
        afiseazaSeparator();
        std::cout << " 1. Adauga client nou\n"
                  << " 2. Cauta client (CNP/CUI)\n"
                  << " 3. Afiseaza toti clientii\n"
                  << " 4. Operatiuni client/cont\n"
                  << " 5. Sterge client\n"
                  << " 0. Iesire\n";
        afiseazaSeparator();
        std::cout << " Optiune: ";
        std::cin >> opt;

        switch (opt) {
            case 1: meniuAdaugaClient();
                break;
            case 2: meniuCautaClient();       
                break;
            case 3: afiseazaTotiClientii();   
                break;
            case 4: meniuOperatiuniClient();  
                break;
            case 5: meniuStergeClient();      
                break;
            case 0: std::cout << "La revedere!\n"; 
                break;
            default: std::cout << "Optiune invalida. Incercati din nou.\n";
        }
    }while (opt != 0);
}

void Meniu::run()
{
    meniuPrincipal();
}