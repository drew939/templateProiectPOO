class Client{
    private:
        std::string nume;

};

class ClientPersoanaFizica : virtual public Client{
    private:
        std::string prenume;
};

class ClientPersoanaJuridica : virtual public Client{
    private:
        std::string tipEntitate;
};