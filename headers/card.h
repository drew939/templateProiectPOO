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

};

class CardCredit : virtual public CardBancar{
    private:
        double limitaCredit;
};

class CardOverdraft : virtual public CardDebit, virtual public CardCredit{

};

class CardVirtual : virtual public CardDebit{

};

class CardPrepaid : virtual public CardVirtual{

};
