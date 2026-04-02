class CardBancar{
    private:
        bool activat = false;
        bool blocat = false;

        std::string titularCard;
        std::string valuta;
        double limitaTranzactii;

        std::string dataExpirare;
        std::string numarCard;
        std::string numarSecuritate;
        std::string codPin;
        std::string operatorPlati;

    public:
        CardBancar(std::string _valuta, std::string _operator) : valuta(_valuta), operatorPlati(_operator){} 
        
};

class CardDebit : virtual public CardBancar{
    private:
        double limitaRetragere;
        bool platiInternationale;

};

class CardCredit : virtual public CardBancar{
    private:
        double limitaCredit;
        double dobanda;
};

class CardOverdraft : virtual public CardDebit, virtual public CardCredit{
    double taxaDepasireLimita;
};

class CardVirtual : virtual public CardDebit{
    bool singleUse;
};

class CardPrepaid : virtual public CardVirtual{
    int limitaIncarcareLunara;
};
