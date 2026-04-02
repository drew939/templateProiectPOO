class Imprumut{
    double sumaCreditata;
    std::string scadenta;
};

class CreditGarantat : virtual public Imprumut{

};

class CreditRefinantare : virtual public Imprumut{

};

class RefinantareIpotecara : virtual public CreditGarantat, virtual public CreditRefinantare{

};

class CreditNevoiPersonale : virtual public Imprumut{

};

class LeasingAuto : virtual public CreditGarantat{

};