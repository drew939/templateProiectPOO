class Client{
    private:
        std::string nume;
        std::string email;
        std::string telefon;

};

class ClientPersoanaFizica : virtual public Client{
    private:
        std::string prenume;
        std::string cnp;
};

class ClientPersoanaJuridica : virtual public Client{
    private:
        std::string tipEntitate;
        std::string cui;
};