class Imprumut{
    private:
        double sumaCreditata;
        std::string scadenta;
        double rataLunara;
        double dobandaAnuala;
        double soldRamasDePlata;
        std::string ibanContRambursare;
};

class CreditGarantat : virtual public Imprumut{
    private:
        std::string bunGarantat;
        double valoareGarantie;
};

class CreditRefinantare : virtual public Imprumut{
    private:
        std::string bancaInitiala;
        double sumaRefinantata;
};

class RefinantareIpotecara : virtual public CreditGarantat, virtual public CreditRefinantare{

};

class CreditNevoiPersonale : virtual public Imprumut{

};

class LeasingAuto : virtual public CreditGarantat{

};