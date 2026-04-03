#pragma once
#include "card.h"
#include "imprumut.h"
#include "cont.h"
#include<vector>


class Client {
	protected:
		std::string nume;
		std::string email;
		std::string telefon;

		std::vector<ContBancar*> conturi;
		std::vector<Imprumut*> imprumuturi;
		std::vector<CardBancar*> carduri;

	public:
		Client(std::string _nume, std::string _email, std::string _telefon) : 
				nume(std::move(_nume)), email(std::move(_email)), telefon(std::move(_telefon)) {}

		Client(const Client& other);            
		Client& operator=(const Client& other); 
		virtual ~Client();           

		virtual void afisareDetalii() const = 0;
		virtual std::string getIdentificator() const = 0;

		
		void adaugaCont(ContBancar* cont) {conturi.push_back(cont);}
		void adaugaImprumut(Imprumut* imprumut) {imprumuturi.push_back(imprumut);}
		void adaugaCard(CardBancar* card) {carduri.push_back(card);}

		void stergeCont(int index);

		ContBancar* operator[](int index);
		const ContBancar* operator[](int index) const;

		std::string getNume() const {return nume;}
		std::string getEmail() const {return email;}
		std::string getTelefon() const {return telefon;}

		int getNumarConturi() const {return static_cast<int>(conturi.size());}
		int getNumarImprumuturi() const {return static_cast<int>(imprumuturi.size());}
		int getNumarCarduri() const {return static_cast<int>(carduri.size());}

		const std::vector<ContBancar*>& getConturi() const {return conturi;}
		const std::vector<Imprumut*>& getImprumuturi() const {return imprumuturi;}
		const std::vector<CardBancar*>& getCarduri() const {return carduri;}

		
		friend std::ostream& operator<<(std::ostream& out, const Client& c);

	private:
		void copiazaDate(const Client& other);
		void stergeDate();
};


class ClientPersoanaFizica : virtual public Client {
	private:
		std::string prenume;
		std::string cnp;
		int varsta;

	public:
		ClientPersoanaFizica(std::string _nume, std::string _prenume, std::string _email, std::string _telefon, std::string _cnp, int _varsta);
		virtual ~ClientPersoanaFizica() {}

		void afisareDetalii() const override;
		std::string getIdentificator() const override {return cnp;}

		std::string getCNP() const {return cnp;}
		std::string getPrenume() const {return prenume;}
		int getVarsta() const {return varsta;}
};

class ClientPersoanaJuridica : virtual public Client {
	private:
		std::string tipEntitate;
		std::string cui;

	public:
		ClientPersoanaJuridica(std::string _nume, std::string _email, std::string _telefon, std::string _tipEntitate, std::string _cui) : 
				Client(std::move(_nume), std::move(_email), std::move(_telefon)),
				tipEntitate(std::move(_tipEntitate)), cui(std::move(_cui)) {}

		virtual ~ClientPersoanaJuridica() {}

		void afisareDetalii() const override;
		std::string getIdentificator() const override {return cui;}

		std::string getCUI() const {return cui;}
		std::string getTipEntitate() const {return tipEntitate;}
};
