#pragma once

class ActivFinanciar {
    protected:
        std::string identificator;
        double pretCurent;
        std::string dataAchizitie;
    public:
        ActivFinanciar(std::string id, double pret, std::string data) : 
            identificator(std::move(id)), pretCurent(pret),
            dataAchizitie(std::move(data)) {}

        virtual ~ActivFinanciar() {}

        virtual void afisareDetalii() const = 0;

        virtual ActivFinanciar* clone() const = 0;

        std::string getIdentificator() const {return identificator;}
        double getPretCurent() const {return pretCurent;}
        std::string getDataAchizitie() const {return dataAchizitie;}

        friend std::ostream& operator<<(std::ostream& out, const ActivFinanciar& a);
};

class Actiune : virtual public ActivFinanciar {
    protected:
        int numarActiuni;
        std::string numeCompanie;
    public:
        Actiune(std::string id, double pret, std::string data, int nr, std::string companie) : 
            ActivFinanciar(std::move(id), pret, std::move(data)),
            numarActiuni(nr), numeCompanie(std::move(companie)) {}

        virtual ~Actiune() {}

        void afisareDetalii() const override;
        ActivFinanciar* clone() const override {return new Actiune(*this);}

        int getNumarActiuni() const {return numarActiuni;}
        std::string getNumeCompanie() const {return numeCompanie;}
};

class Obligatiune : virtual public ActivFinanciar {
    protected:
        double dobandaAnuala;
        int durata;
    public:
        Obligatiune(std::string id, double pret, std::string data, double dob, int dur) : 
            ActivFinanciar(std::move(id), pret, std::move(data)), dobandaAnuala(dob), durata(dur) {}

        virtual ~Obligatiune() {}

        void afisareDetalii() const override;
        ActivFinanciar* clone() const override {return new Obligatiune(*this);}

        double getDobandaAnuala() const {return dobandaAnuala;}
        int getDurata() const {return durata;}
};

class TitluDeStat : virtual public Obligatiune{
    public:
        TitluDeStat(std::string id, double pret, std::string data, double dob, int dur) :
            ActivFinanciar(std::move(id), pret, std::move(data)),
            Obligatiune(id, pret, data, dob, dur) {}

        virtual ~TitluDeStat() {}

        void afisareDetalii() const override;
        ActivFinanciar* clone() const override {return new TitluDeStat(*this);}
};

class FondMutualMixt {
    private:
        std::string numeFond;
        double valoareTotala;
        double comisionAdministrare;

        std::vector<Actiune*> portofoliuActiuni;
        std::vector<Obligatiune*> portofoliuObligatiuni;
        std::vector<TitluDeStat*> portofoliuTitluri;

        void copiazaPortofoliu(const FondMutualMixt& other);
        void stergePortofoliu();

    public:
        FondMutualMixt(std::string nume, double valoare, double comision) : 
            numeFond(std::move(nume)), valoareTotala(valoare),
            comisionAdministrare(comision) {}

        FondMutualMixt(const FondMutualMixt& other);
        FondMutualMixt& operator=(const FondMutualMixt& other);
        ~FondMutualMixt();

        void adaugaActiune(Actiune* a)      {portofoliuActiuni.push_back(a);}
        void adaugaObligatiune(Obligatiune* o)      {portofoliuObligatiuni.push_back(o);}
        void adaugaTitlu(TitluDeStat* t)        {portofoliuTitluri.push_back(t);}

        void afisareDetalii() const;
        friend std::ostream& operator<<(std::ostream& out, const FondMutualMixt& f);
};

class ActiuneFractionara : virtual public Actiune {
    private:
        double fractiune;
    public:
        ActiuneFractionara(std::string id, double pret, std::string data, int nr, std::string companie, double frac) : 
            ActivFinanciar(std::move(id), pret, std::move(data)),
            Actiune(id, pret, data, nr, companie), fractiune(frac) {}

        virtual ~ActiuneFractionara() {}

        void afisareDetalii() const override;
        ActivFinanciar* clone() const override {return new ActiuneFractionara(*this);}

        double getFractiune() const {return fractiune;}
};
