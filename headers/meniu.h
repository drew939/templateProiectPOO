#pragma once
#include "client.h"
#include "exceptii.h"

class Meniu {
private:
    std::vector<Client*> listaClienti;

    Meniu() = default;
    Meniu(const Meniu&) = delete;
    Meniu& operator=(const Meniu&) = delete;

public:
    static Meniu& getInstance();
    ~Meniu();

    void adaugaClient(Client* client);
    Client* cautaClientDupaId(const std::string& id);
    void stergeClient(const std::string& id);
    void afiseazaTotiClientii() const;

    
    void deschideCont(const std::string& idClient, ContBancar* cont);
    void efectueazaDepunere(const std::string& idClient, int indexCont, double suma);
    void efectueazaRetragere(const std::string& idClient, int indexCont, double suma);

    void run();

private:
    void meniuPrincipal();
    void meniuAdaugaClient();
    void meniuCautaClient();
    void meniuStergeClient();
    void meniuOperatiuniClient();
    void meniuDeschideCont(Client* client);
    void meniuOperatiuniCont(Client* client);

    static void afiseazaSeparator();
};
