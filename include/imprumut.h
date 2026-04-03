#pragma once

class Imprumut{
    protected:
        double sumaCreditata;
        std::string scadenta;
        double rataLunara;
        double dobandaAnuala;
        double soldRamasDePlata;
        std::string ibanContRambursare;
    public:
        Imprumut(double suma, std::string scad, double rata, double dob, std::string iban) : 
                sumaCreditata(suma), scadenta(std::move(scad)),
                rataLunara(rata), dobandaAnuala(dob),
                soldRamasDePlata(suma), ibanContRambursare(std::move(iban)) 
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
        CreditGarantat(double suma, std::string scad, double rata, double dob, std::string iban, std::string bun, double valGar) :
            Imprumut(suma, std::move(scad), rata, dob, std::move(iban)),
            bunGarantat(std::move(bun)), valoareGarantie(valGar) {}
        virtual ~CreditGarantat() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new CreditGarantat(*this);}
};

class CreditRefinantare : virtual public Imprumut{
    protected:
        std::string bancaInitiala;
        double sumaRefinantata;
    public:
        CreditRefinantare(double suma, std::string scad, double rata, double dob, std::string iban, std::string banca, double sumaRef) : 
            Imprumut(suma, std::move(scad), rata, dob, std::move(iban)), bancaInitiala(std::move(banca)), sumaRefinantata(sumaRef) {}

        virtual ~CreditRefinantare() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new CreditRefinantare(*this);}
};

class RefinantareIpotecara : virtual public CreditGarantat, virtual public CreditRefinantare{
    public:
        RefinantareIpotecara(double suma, std::string scad, double rata, double dob, 
                            std::string iban, std::string bun, double valGar, 
                            std::string banca, double sumaRef):
                                Imprumut(suma, scad, rata, dob, iban),
                                CreditGarantat(suma, scad, rata, dob, iban, std::move(bun), valGar),
                                CreditRefinantare(suma, scad, rata, dob, iban, std::move(banca), sumaRef) {}

        virtual ~RefinantareIpotecara() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new RefinantareIpotecara(*this);}
};

class CreditNevoiPersonale : virtual public Imprumut{
    public:
        CreditNevoiPersonale(double suma, std::string scad, double rata, double dob, std::string iban) : 
            Imprumut(suma, std::move(scad), rata, dob, std::move(iban)) {}

        virtual ~CreditNevoiPersonale() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new CreditNevoiPersonale(*this);}
};

class LeasingAuto : virtual public CreditGarantat{
    public:
        LeasingAuto(double suma, std::string scad, double rata, double dob, std::string iban, std::string bun, double valGar) :
                Imprumut(suma, scad, rata, dob, iban),
                CreditGarantat(suma, std::move(scad), rata, dob, std::move(iban), std::move(bun), valGar) {}

        virtual ~LeasingAuto() {}

        void afisareDetalii() const override;
        Imprumut* clone() const override {return new LeasingAuto(*this);}
};
