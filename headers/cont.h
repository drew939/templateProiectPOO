class ContBancar{
    private:
        double sold;
        std::string iban;
        std::string valuta;
        std::string titularCont;
        std::string dataDeschiderii;
        std::string stareCont;
    public:
        ContBancar(std::string _valuta) : valuta(_valuta){}
};

class ContCurent : virtual public ContBancar{
    private:
        double comisionAdministrare;
        double pragIncasareLunara;
        double limitaDescoperire;
    public:
        ContCurent(std::string _valuta) : ContBancar(_valuta){}

};

class ContEconomii : virtual public ContBancar{
    private:
        double dobanda;
        double soldMinim;
        int ziCapitalizare;
    public:
        
};

class ContCurentAcumulare : virtual public ContCurent, virtual public ContEconomii{

};

class ContRoundUp : virtual public ContEconomii{
    int multiplicatorRotunjire;
    std::string ibanContSursa;
};

class DepozitBancar : virtual public ContEconomii{
    private:
        int termen;
        std::string dataMaturitate;
        bool prelungireAutomata;

    public:

};

class ContInvestitii : virtual public ContBancar{
    std::vector<std::string> portofoliuActiuni;
};

class ContSweep : virtual public ContCurent, virtual public ContEconomii{
    private:
        double prag;
        std::string frecventaSurplus;
    public:

};

