#pragma once
#include "investitii.h"
#include<string>

class ContBancar {
    protected:
        double sold;
        std::string iban;
        std::string valuta;
        std::string titularCont;
        std::string dataDeschiderii;
        std::string stareCont;

        static long long int contorIban;
        static std::string generareIban();

    public:
        ContBancar(const std::string& _valuta, double _sold = 0.0) : 
            sold(_sold), iban(generareIban()), 
            valuta(_valuta), stareCont("ACTIV") {}
        
        virtual ~ContBancar() {}
        virtual void afisareDetalii() const = 0;
        virtual ContBancar* clone() const = 0;

        virtual std::string getTipCont() const = 0;

        virtual void depune(double suma);
        virtual void retrage(double suma);

        double getSold() const {return sold;}
        std::string getIban() const {return iban;}
        std::string getValuta() const {return valuta;}
        std::string getTitular() const {return titularCont;}
        std::string getStare() const {return stareCont;}

        void setTitular(const std::string& t) {titularCont = t;}
        void inchide() {stareCont = "INCHIS";}

        ContBancar& operator+=(double suma) {
            depune(suma);
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& out, const ContBancar& c);

};

class ContCurent : virtual public ContBancar {
    protected:
        double comisionAdministrare;
        double pragIncasareLunara;
        double limitaDescoperire;
    public:
        ContCurent(const std::string& _valuta, double _sold = 0.0, double comision = 10.0, double limDescoperire = 1000.0) : 
                ContBancar(_valuta, _sold), comisionAdministrare(comision), 
                pragIncasareLunara(0.0), limitaDescoperire(limDescoperire) {}
        virtual ~ContCurent() {}

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new ContCurent(*this);}

        std::string getTipCont() const override {return "ContCurent";}

        void retrage(double suma) override;

        double getComision() const {return comisionAdministrare;}
        double getLimitaDescoperire() const {return limitaDescoperire;}
};

class ContEconomii : virtual public ContBancar {
    protected:
        double dobanda;
        double soldMinim;
        int ziCapitalizare;
    public:
        ContEconomii(const std::string& _valuta, double soldInitial = 0.0, double dob = 0.0, double soldMin = 0.0) : 
            ContBancar(_valuta, soldInitial), dobanda(dob), 
            soldMinim(soldMin), ziCapitalizare(10) {}

        virtual ~ContEconomii() {}

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new ContEconomii(*this);}

        std::string getTipCont() const override {return "ContEconomii";}

        void aplicaDobanda();

        double getDobanda() const {return dobanda;}
        double getSoldMinim() const {return soldMinim;}
        
};

class ContCurentAcumulare : virtual public ContCurent, virtual public ContEconomii {
    public:
        ContCurentAcumulare(const std::string& _valuta, double soldInitial = 0.0, double comision = 0.0, double dob = 1.0) : 
            ContBancar(_valuta, soldInitial), ContCurent(_valuta, soldInitial, comision),
            ContEconomii(_valuta, soldInitial, dob) {}

        virtual ~ContCurentAcumulare() {}

        void afisareDetalii() const override;
        void retrage(double suma) override;
        ContBancar* clone() const override {return new ContCurentAcumulare(*this);}

        std::string getTipCont() const override {return "ContCurentAcumulare";}

};

class ContRoundUp : virtual public ContEconomii {
    private:
        int multiplicatorRotunjire;
        std::string ibanContSursa;

    public:
        ContRoundUp(const std::string& _valuta, double soldInitial = 0.0, int multiplicator = 2, const std::string& ibanSursa = "") :
         ContBancar(_valuta, soldInitial), ContEconomii(_valuta, soldInitial), 
         multiplicatorRotunjire(multiplicator), ibanContSursa(ibanSursa) {}

        virtual ~ContRoundUp() {}

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new ContRoundUp(*this);}

        std::string getTipCont() const override {return "ContRoundUp";}
};

class DepozitBancar : virtual public ContEconomii {
    private:
        int termen;
        std::string dataMaturitate;
        bool prelungireAutomata;

    public:
        DepozitBancar(const std::string& _valuta, double soldInitial = 0.0, int t = 12, double dob = 3.0, bool prelungire = false) : 
            ContBancar(_valuta, soldInitial), ContEconomii(_valuta, soldInitial, dob),
            termen(t), prelungireAutomata(prelungire) {}

        virtual ~DepozitBancar() {}

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new DepozitBancar(*this);}

        void retrage(double suma) override;

        int  getTermen() const {return termen;}
        bool activatPrelungireAutomata() const {return prelungireAutomata;}

        std::string getTipCont() const override {return "DepozitBancar";}

};

class ContInvestitii : virtual public ContBancar {
    private:
        double randament;
        double investitieInitiala;
        std::string profilRisc;
        std::vector<ActivFinanciar*> portofoliu;

        static double calculeazaRandament(const std::string& profil) {
            if (profil == "CONSERVATOR") 
                return 7.50;
            else if (profil == "DINAMIC")
                return 30.00;
                 else
                    return 15.00;
        }

    public:
        ContInvestitii(const std::string& _valuta, double soldInitial = 0.0, const std::string& risc = "MEDIU") :
            ContBancar(_valuta, soldInitial), randament(calculeazaRandament(risc)), investitieInitiala(soldInitial),
            profilRisc(risc) {}

        ContInvestitii(const ContInvestitii& other);
        ContInvestitii& operator=(const ContInvestitii& other);
        ~ContInvestitii();

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new ContInvestitii(*this);}

        std::string getTipCont() const override {return "ContInvestitii";}

        void adaugaActiv(ActivFinanciar* activ) {portofoliu.push_back(activ);}
        std::string getProfilRisc() const {return profilRisc;}
        int getDimensiunePortofoliu() const {return static_cast<int>(portofoliu.size());}
};


class ContBusiness : virtual public ContBancar {
    protected:
        std::vector<std::string> imputerniciti;

    public:
        ContBusiness(const std::string& _valuta, double soldInitial = 0.0) :
            ContBancar(_valuta, soldInitial) {}

        virtual ~ContBusiness() {}

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new ContBusiness(*this);}

        std::string getTipCont() const override {return "ContBusiness";}
        
        void adaugaImputernicit(const std::string& nume) {imputerniciti.push_back(nume);}
};

class ContSweep : virtual public ContBusiness, virtual public ContEconomii {
    private:
        double prag;
        std::string frecventaSurplus;

    public:
        ContSweep(const std::string& _valuta, double soldInitial = 0.0, double _prag = 10000.0, const std::string& frecventa = "ZILNIC") : ContBancar(_valuta, soldInitial), ContBusiness(_valuta, soldInitial), ContEconomii(_valuta, soldInitial), prag(_prag), frecventaSurplus(frecventa) {}

        virtual ~ContSweep() {}

        void afisareDetalii() const override;
        ContBancar* clone() const override {return new ContSweep(*this);}

        std::string getTipCont() const override {return "ContSweep";}
};
