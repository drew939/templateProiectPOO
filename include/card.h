#pragma once
#include "exceptii.h"
#include<string>

class CardBancar {
    protected:
        bool activat = false;
        bool blocat = false;

        std::string titularCard;
        std::string valuta;
        double limitaTranzactii;

        std::string dataExpirare;
        std::string numarCard;
        std::string numarSecuritate;
        std::string codPin;
        std::string operatorPlati;

    public:
        CardBancar(const std::string& _valuta, const std::string& _operator) : valuta(_valuta), operatorPlati(_operator) {}

        virtual ~CardBancar() {}

        virtual void afisareDetalii() const = 0;

        virtual CardBancar* clone() const = 0;

        bool esteBlocat() const {return blocat;}
        bool esteActivat() const {return activat;}
        std::string getTitular() const {return titularCard;}
        std::string getValuta() const {return valuta;}
        std::string getNumarCard() const {return numarCard;}

        void seteazaTitular(const std::string& t)   {titularCard = t;}
        void seteazaNumar(const std::string& n)     {numarCard = n;}
        void seteazaExpirare(const std::string& e)  {dataExpirare = e;}
        void seteazaPin(const std::string& p)       {codPin = p;}
        void seteazaLimitaTranzactii(double l) {
            if (l < 0) 
                throw ExceptieSumaInvalida("Limita tranzactii nu poate fi negativa!");
            limitaTranzactii = l;
        }

        void activeaza()    {activat = true;}
        void blocheaza()    {blocat = true;}
        void deblocheaza()  {blocat = false;}

        friend std::ostream& operator<<(std::ostream& out, const CardBancar& c);
};

class CardDebit : virtual public CardBancar {
    protected:
        double limitaRetragere;
        bool platiInternationale;
    public:
        CardDebit(const std::string& valuta, const std::string op, double limita = 5000.0, bool international = false) :
            CardBancar(valuta, op), limitaRetragere(limita), platiInternationale(international) {}

        virtual ~CardDebit() {}

        void afisareDetalii() const override;
        CardBancar* clone() const override {return new CardDebit(*this);}

        double getLimitaRetragere() const {return limitaRetragere;}
        void setLimitaRetragere(double l) {
            if (l < 0) 
                throw ExceptieSumaInvalida("Limita retragere invalida!");
            limitaRetragere = l;
        }
        bool getPlatiInternationale() const {return platiInternationale;}
};

class CardCredit : virtual public CardBancar {
    protected:
        double limitaCredit;
        double dobanda;
        double sumaMinimaPlata;
        std::string dataScadentaLunara;
    
    public:
        CardCredit(const std::string& valuta, const std::string& op, double limita = 10000.0, double dob = 0.0) : 
            CardBancar(valuta, op),
            limitaCredit(limita), dobanda(dob) {}

        virtual ~CardCredit() {}

        void afisareDetalii() const override;
        CardBancar* clone() const override {return new CardCredit(*this);}

        double getLimitaCredit() const {return limitaCredit;}
        double getDobanda() const {return dobanda;}
};

class CardOverdraft : virtual public CardDebit, virtual public CardCredit {
    private:
        double taxaDepasireLimita = 0.0;

    public:
        CardOverdraft(const std::string& valuta, const std::string& op, double limRetragere = 5000.0, double limCredit = 10000.0,double taxa = 0.0) :
                CardBancar(valuta, op), CardDebit(valuta, op, limRetragere),
                CardCredit(valuta, op, limCredit), taxaDepasireLimita(taxa) {}

        virtual ~CardOverdraft() {}

        void afisareDetalii() const override;
        CardBancar* clone() const override {return new CardOverdraft(*this);}
};

class CardVirtual : virtual public CardDebit {
protected:
    bool singleUse = false;

public:
    CardVirtual(const std::string& valuta, const std::string& op, bool su = false) : CardBancar(valuta, op),
                                                                       CardDebit(valuta, op), singleUse(su) {}

    virtual ~CardVirtual() {}

    void afisareDetalii() const override;
    CardBancar* clone() const override {return new CardVirtual(*this);}

    bool isSingleUse() const {return singleUse;}
};

class CardPrepaid : virtual public CardVirtual {
    private:
        int limitaIncarcareLunara = 1000;

    public:
        CardPrepaid(const std::string& valuta, const std::string& op, int limita = 1000) : 
            CardBancar(valuta, op), CardDebit(valuta, op),
            CardVirtual(valuta, op), limitaIncarcareLunara(limita) {}

        virtual ~CardPrepaid() {}

        void afisareDetalii() const override;
        CardBancar* clone() const override {return new CardPrepaid(*this);}

        int getLimitaIncarcare() const {return limitaIncarcareLunara;}
};
