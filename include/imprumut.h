#pragma once
#include<string>
#include "exceptii.h"

class Imprumut{
    protected:
        double sumaCreditata;
        std::string scadenta;
        double rataLunara;
        double dobandaAnuala;
        double soldRamasDePlata;
        std::string ibanContRambursare;
    public:
        Imprumut(double suma, const std::string& scad, double rata, double dob, const std::string& iban) : 
                sumaCreditata(suma), scadenta(scad),
                rataLunara(rata), dobandaAnuala(dob),
                soldRamasDePlata(suma), ibanContRambursare(iban) 
                {
                    if (suma <= 0)
                        throw ExceptieSumaInvalida("Suma creditata trebuie sa fie pozitiva!");
                    if (rata <= 0)
                        throw ExceptieSumaInvalida("Rata lunara trebuie sa fie pozitiva!");
                }

        virtual ~Imprumut() {}
        virtual void afisareDetalii() const = 0;
        virtual Imprumut* clone() const = 0;

        void platesteLunara() {
            if (soldRamasDePlata <= 0)
                throw ExceptieFonduriInsuficiente("Imprumutul a fost deja achitat integral!");
            soldRamasDePlata -= rataLunara;
            if (soldRamasDePlata < 0) 
                soldRamasDePlata = 0.0;
        }

        double getSumaCreditata()   const {return sumaCreditata;}
        double getSoldRamas()   const {return soldRamasDePlata;}
        double getRataLunara()  const {return rataLunara;}
        double getDobandaAnuala()   const {return dobandaAnuala;}
        std::string getScadenta()   const {return scadenta;}
        std::string getIbanRambursare() const {return ibanContRambursare;}

        friend std::ostream& operator<<(std::ostream& out, const Imprumut& i);
};

class CreditGarantat : virtual public Imprumut{
    protected:
        std::string bunGarantat;
        double valoareGarantie;
    public:
        CreditGarantat(double suma, const std::string& scad, double rata, double dob, const std::string& iban, const std::string& bun, double valGar) :
            Imprumut(suma, scad, rata, dob, iban),
            bunGarantat(bun), valoareGarantie(valGar) {}
        virtual ~CreditGarantat() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new CreditGarantat(*this);}
};

class CreditRefinantare : virtual public Imprumut{
    protected:
        std::string bancaInitiala;
        double sumaRefinantata;
    public:
        CreditRefinantare(double suma, const std::string& scad, double rata, double dob, const std::string& iban, const std::string& banca, double sumaRef) : 
            Imprumut(suma, scad, rata, dob, iban), bancaInitiala(banca), sumaRefinantata(sumaRef) {}

        virtual ~CreditRefinantare() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new CreditRefinantare(*this);}
};

class RefinantareIpotecara : virtual public CreditGarantat, virtual public CreditRefinantare{
    public:
        RefinantareIpotecara(double suma, const std::string& scad, double rata, double dob, 
                            const std::string& iban, const std::string& bun, double valGar, 
                            const std::string& banca, double sumaRef):
                                Imprumut(suma, scad, rata, dob, iban),
                                CreditGarantat(suma, scad, rata, dob, iban, bun, valGar),
                                CreditRefinantare(suma, scad, rata, dob, iban, banca, sumaRef) {}

        virtual ~RefinantareIpotecara() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new RefinantareIpotecara(*this);}
};

class CreditNevoiPersonale : virtual public Imprumut{
    public:
        CreditNevoiPersonale(double suma, const std::string& scad, double rata, double dob, const std::string& iban) : 
            Imprumut(suma, scad, rata, dob, iban) {}

        virtual ~CreditNevoiPersonale() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new CreditNevoiPersonale(*this);}
};

class LeasingAuto : virtual public CreditGarantat{
    public:
        LeasingAuto(double suma, const std::string& scad, double rata, double dob, const std::string& iban, const std::string& bun, double valGar) :
                Imprumut(suma, scad, rata, dob, iban),
                CreditGarantat(suma, scad, rata, dob, iban, bun, valGar) {}

        virtual ~LeasingAuto() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new LeasingAuto(*this);}
};
