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
        //?double limitaDescoperire;
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
    double soldMinim; //pentru a primi dobanda
    //ziCapitalizare ar trebui sa fie zilnic/saptamanal

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

class ContInvestitii{
    private:
        std::string titularCont;    
        double randament;
        std::string instrumentInvestitii;
        double investitieInitiala;
        std::string gradRisc;
        std::string valuta;
};


class ContBusiness : virtual public ContBancar{
    private:
        std::vector<std::string> imputerniciti;

};

class ContSweep : virtual public ContBusiness, virtual public ContEconomii{
    private:
        double prag;
        std::string frecventaSurplus; //zilnic,saptamanl,lunar
    public:

};

