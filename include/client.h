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
		Client(const std::string& _nume, const std::string& _email, const std::string& _telefon) : 
				nume(_nume), email(_email), telefon(_telefon) {}

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
		ClientPersoanaFizica(const std::string& _nume, const std::string& _prenume, const std::string& _email, const std::string& _telefon, const std::string& _cnp, int _varsta);
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
		ClientPersoanaJuridica(const std::string& _nume, const std::string& _email, const std::string& _telefon, const std::string& _tipEntitate, const std::string& _cui) : 
				Client(_nume, _email, _telefon),
				tipEntitate(_tipEntitate), cui(_cui) {}

		virtual ~ClientPersoanaJuridica() {}

		void afisareDetalii() const override;
		std::string getIdentificator() const override {return cui;}

		std::string getCUI() const {return cui;}
		std::string getTipEntitate() const {return tipEntitate;}
};
