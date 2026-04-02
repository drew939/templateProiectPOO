class ActivFinanciar{
    private:
        std::string identificator;
        double pretCurent;
        std::string dataAchizitie;
};

class Actiune : virtual public ActivFinanciar{
    private:
        int numarActiuni;
        std::string numeCompanie;
};

class Obligatiune : virtual public ActivFinanciar{
    double dobandaAnuala;
    int durata;
};

class FondMutualMixt{
    private:
        std::string numeFond;
        double valoareTotala;
        double comisionAdministrare;
        
        std::vector<Actiune*> portofoliuActiuni;
        std::vector<Obligatiune*> portofoliuObligatiuni;
        std::vector<TitluDeStat*> portofoliuTitluri;
};

class TitluDeStat : virtual public Obligatiune{

};

class ActiuneFractionara : virtual public Actiune{

};