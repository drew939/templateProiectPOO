class ContBancar{
    private:
        double sold;
        std::string iban;
        std::string valuta;
        std::string titularCont;
    public:
        ContBancar(std::string _valuta) : valuta(_valuta){}
};

class ContCurent : virtual public ContBancar{
    private:
        double comisionAdministrare;
    public:
        ContCurent(std::string _valuta) : ContBancar(_valuta){}

};

class ContEconomii : virtual public ContBancar{
    private:
        double dobanda;
    public:
        
};

class ContCurentAcumulare : virtual public ContCurent, virtual public ContEconomii{
    
};

class ContRoundUp : virtual public ContEconomii{

};

class DepozitBancar : virtual public ContEconomii{
    private:
        int termen;
    public:

};

class ContInvestitii : virtual public ContBancar{

};

class ContSweep : virtual public ContCurent, virtual public ContEconomii{
    private:
        double prag;
    public:

};

