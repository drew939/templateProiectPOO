# Sistem de management bancar
Acest proiect implementeaza un sistem complet de gestiune bancara care permite administrarea clientilor, a conturilor bancare, a cardurilor, imprumuturilor si instrumentelor de investitii. Sistemul include o interfata cu un meniu ierarhizat.

---

## 1. Descriere

  Sistem complet de gestiune bancara pentru administrarea clientilor, conturi bancare, carduri, imprumuturi si investitii. Este operat printr-o interfata interactiva tip meniu ierarhizat.

**Organizare fisiere:**
```
proiect/
├── src/
│   └── main.cpp
└── include/
    ├── client.h/cpp
    ├── cont.h/cpp
    ├── card.h/cpp
    ├── imprumut.h/cpp
    ├── investitii.h/cpp
    ├── meniu.h/cpp
    └── exceptii.h
```

---

## 2. Arhitectura claselor

### 2.1 Ierarhia Client

**Client (clasa clasa abstracta)**  
Clasa de baza pentru toti clientii. 
Atribute:
- nume, email, telefon
- vectori de produse bancare: conturi, imprumuturi, carduri

Metode:
- metode virtuale pure: `afisareDetalii()`, `getIdentificator()`
- gestionare produse: `adaugaCont()`, `adaugaImprumut()`, `adaugaCard()`, `stergeCont()`
- operator `[]` pentru acces indexat la conturi
- regula celor 3 (constructor copiere, operator=, destructor)

**ClientPersoanaFizica** - atribute: CNP, prenume, varsta (minim 18 ani cu validare)  
**ClientPersoanaJuridica** - atribute: CUI, tip entitate (SRL/SA/etc.)

---

### 2.2 Ierarhia ContBancar

**ContBancar (clasa abstracta)**  
Clasa de baza pentru toate tipurile de conturi bancare.
Atribute:
- sold, IBAN (generat automat), valuta, titular
- contor static pentru generare IBAN-uri unice

-se genereaza IBAN unic prin membrul static `contorIban` si metoda statica `generareIban()`. 
-metode: `depune()`, `retrage()` (validare prin exceptii). 
-operatorul `+=` se poate folosi pentru depuneri. 
-metode virtuale pure: `afisareDetalii()`, `clone()`, `getTipCont()`.

**Conturi (clase derivate din ContBancar):**
- **ContCurent** - poate avea descoperire de cont, comision lunar
- **ContEconomii** - primeste dobanda, este nevoie de un sold minim, `aplicaDobanda()`
- **ContRoundUp** - economisire automata prin rotunjirea tranzactiilor
- **DepozitBancar** - termen fix, penalizare 10% retragere anticipata
- **ContBusiness** - contine lista imputerniciti pentru companii
- **ContInvestitii** - portofoliu `ActivFinanciar*`, profilul risc seteaza randamentul (metoda statica `calculeazaRandament()`)

**Mostenire diamant:**
- **ContCurentAcumulare** ----- `ContCurent` + `ContEconomii`
  -moateneate atat ContCurent, cat si ContEconomii. Reprezinta un cont care ofera simultan operatiuni zilnice cu descoperire si acumulare prin dobanda.
- **ContSweep** ----- `ContBusiness` + `ContEconomii`
  -moateneate atat ContCurent, cat si ContEconomii. Reprezinta un cont care ofera simultan operatiuni zilnice cu descoperire si acumulare prin dobanda.

---

### 2.3 Ierarhia CardBancar

**CardBancar (clasa abstracta)**  
Atribute:
- titular, valuta, limita tranzactii
- stari: activat, blocat
- detalii securitate: numar card, PIN, operator plati
Metode:
-gestionare stare: `activeaza()`, `blocheaza()`, `deblocheaza()`.
-validare limite prin `seteazaLimitaTranzactii()`.

**Carduri (clase derivate din CardBancar):**
- **CardDebit** - acces direct la sold, limita retragere, plati internationale
- **CardCredit** - linie credit, dobanda, suma minima plata
- **CardVirtual** - optional single-use
- **CardPrepaid** - extinde Virtual, limita lunara de incarcare
- **CardOverdraft**(mostenire diamant) ----- `CardDebit` + `CardCredit`

---

### 2.4 Ierarhia Imprumut

**Imprumut (clasa abstracta)**  
Clasa de baza pentru toate tipurile de credite.
Atribute:
- suma creditata, dobanda anuala, rata lunara
- sold ramas de plata, scadenta
- IBAN cont rambursare

Metode:
- `platesteLunara()` pentru amortizare
- validare sume pozitive in constructor
- metode virtuale pure: `afisareDetalii()`, `clone()`

**Împrumuturi (clase derivate din Imprumut):**
- **CreditGarantat** - bun, valoare garantie
- **CreditRefinantare** - preluare de la alta banca
- **CreditNevoiPersonale** - consum negarantat
- **LeasingAuto** - CreditGarantat pentru automobile
- **RefinantareIpotecara(mostenire diamant) ------ `CreditGarantat` + `CreditRefinantare`

---

### 2.5 Ierarhia ActivFinanciar

**ActivFinanciar (clasa abstracta)**  
-identificator, pret curent, data achizitie
-metode virtuale pure: `afisareDetalii()`, `clone()`.

**Instrumente financiare (clase derivate din ActivFinanciar):**
- **Actiune** - numar actiuni, nume companie
- **Obligatiune** - dobanda anuala, durata
- **TitluDeStat** - extinde Obligatiune (risc zero guvernamental)
- **ActiuneFractionara** - extinde Actiune cu membru `fractiune` (double)

**FondMutualMixt**
-gestioneaza un portofoliu diversificat de active financiare
-se percepe comision administrare.
-contine trei vectori separati: `Actiune*`, `Obligatiune*`, `TitluDeStat*`.
-metode helper `copiazaPortofoliu()`, `stergePortofoliu()`.

---

### 2.6 Meniu (tip Singleton)

Clasa Meniu controleaza intreaga aplicatie si implementeaza design pattern-ul Singleton. Exista o singura instanta a meniului care gestioneaza:
- vectorul de clienti (`vector<Client*>`)
- interfata utilizator (meniu ierarhizat)
- toate operatiunile CRUD

**Functionalitati principale:**
- **Create**: `meniuAdaugaClient()` (PF/PJ), `meniuDeschideCont()` (5 tipuri pentru PF, 2 tipuri pentru PJ)
- **Read**: `cautaClientDupaId()`, `afiseazaTotiClientii()`
- **Update**: `efectueazaDepunere()`, `efectueazaRetragere()`, `meniuOperatiuniClient()`
- **Delete**: `stergeClient()` cu cleanup memorie; auto-stergere DepozitBancar la sold=0

- tipuri conturi diferite pentru PF vs PJ - detectia tipului de cont
- implementare structuri try-catch pentru erori
- meniu ierarhizat (meniu principal ----- submeniuri specifice)

---

### 2.7 Exceptii
Aplicatia utilizeaza cinci clase de exceptii derivate din `std::exception`:

- **ExceptieFonduriInsuficiente** (runtime_error) - retrageri peste sold
- **ExceptieCardBlocat** (runtime_error) - carduri blocate
- **ExceptieSumaInvalida** (logic_error) - sume negative/zero
- **ExceptieClientNegasit** (runtime_error) - ID inexistent
- **ExceptieVarstaInvalida** (logic_error) - client minor

---

## 3. Implementarea cerintelor tehnice

### 3.1 Mostenire in diamant

Proiectul implementeaza ierarhii complexe si 4 structuri de moatenire in diamant:

1. **ContCurentAcumulare**  
```
        ContBancar
        /         \
   ContCurent  ContEconomii
        \         /
    ContCurentAcumulare
```
-combina functionalitatile de cont curent (descoperire) cu cele de cont economii (dobanda).

--- 

2. **ContSweep**  
   `ContBusiness` + `ContEconomii`
```
        ContBancar
        /         \
  ContBusiness  ContEconomii
        \         /
        ContSweep
```
-cash management automat pentru companii cu dobanda la excesul de lichiditati.

---

3. **CardOverdraft**  
   `CardDebit` + `CardCredit` 
   (card hibrid: sold propriu + linie credit)
   
```
        CardBancar
        /         \
   CardDebit   CardCredit
        \         /
      CardOverdraft
```
---

4. **RefinantareIpotecara**  
   `CreditGarantat` + `CreditRefinantare` 
```
          Imprumut
          /      \
  CreditGarantat  CreditRefinantare
          \      /
   RefinantareIpotecara
```
Refinantare credit ipotecar cu garantie imobiliara.

---

### 3.2 Metode si membrii statici

**Membru static:**  
`ContBancar::contorIban` - contor global pentru a genera IBAN-uri unice

**Metode statice:**
- `ContBancar::generareIban()` - IBAN format: "RO49ABCDUMX" + secventa de cifre
- `ContInvestitii::calculeazaRandament(profil)` - mapare in fucntie de profilul de risc (CONSERVATOR = 7.5% / MODERAT = 15% / DINAMIC = 30%)

---

### 3.3 Encapsulare si gestiune resurse

**Modificatori acces:**  
`private`: sold, limite, alte date;  `protected`: atribute mostenite; `public`: interfata

**Regula celor 3:**
- `Client` - copiere integrala pentru vectori conturi/imprumuturi/carduri
- `ContInvestitii` - copiere integrala pentru portofoliu prin `clone()`
- `FondMutualMixt` - copiere integrala a trei vectori cu helper methods

**std::vector utilizari:**
- `Meniu::listaClienti` (Client*)
- `Client`: trei vectori (ContBancar*, Imprumut*, CardBancar*)
- `ContInvestitii::portofoliu` (ActivFinanciar*)
- `FondMutualMixt`: trei vectori clase active
- `ContBusiness::imputerniciti` (string)

---

### 3.4 Polimorfism

**Metodele virtuale pure** din clasele abstracte:
- `Client`: `afisareDetalii()`, `getIdentificator()`
- `ContBancar`, `CardBancar`, `Imprumut`, `ActivFinanciar`: `afisareDetalii()`, `clone()`
- `ContBancar`: `getTipCont()`

**Override:**
- `ContCurent::retrage()` - permite overdraft
- `DepozitBancar::retrage()` - aplica penalitati 10%
- `ContCurentAcumulare::retrage()` - delega la `ContCurent`

**Utilizare polimorfica:** manipulare prin pointeri baza (`Client*`, `ContBancar*`)

---

### 3.5 Tratarea Exceptiilor

**Throw:**
- constructori: validare varsta, sume
- metode: `depune()`, `retrage()`, `cautaClientDupaId()`, `operator[]`

**Catch:**
- `Meniu::efectueazaDepunere/Retragere()`
- `Meniu::deschideCont()` - cleanup la eroare (delete cont)
- `Meniu::meniuAdaugaClient()` - validare varsta
- Toate metodele meniu - imbuntatirea interfatei

### Validari implementate:

**Validari de date:**
- verificarea sumelor pozitive (depuneri, retrageri, limite)
- validarea varstei minime (18 ani pentru clienti)
- verificarea fondurilor disponibile la retrageri
- validarea ID-urilor unice (CNP/CUI)

**Validari de stare:**
- verificarea indexului valid la accesul prin `operator[]`
- verificarea existentei clientului in baza de date
- verificarea starii cardurilor (blocat/activ)

**Validari de logica a functionalitatilor produselor:**
- depaairea limitei de descoperire la ContCurent
- penalizare retragere anticipata la DepozitBancar
- validare limita de credit la CardCredit

---

## 4. Aspecte ale implementarii
- **Singleton** - Meniu (instanta unica globala)
- **Prototype** - metoda `clone()` in toate ierarhiile
- **Factory** - `generareIban()` pentru identificatori unici
- **Template Method** - metode virtuale in clase abstracte
- Resource management (destructori virtuali, cleanup memorie)
- Error handling cu exceptii tipizate

---

## 5. Meniul
## Meniul aplicatiei

```
1. Adauga client nou
2. Cauta client (CNP/CUI)
3. Afiaeaza toti clientii
4. Operatiuni client/cont
   4.1. Afiaeaza detalii client
   4.2. Deschide cont nou
   4.3. Operatiune cont (depunere/retragere)
5. Șterge client
0. Ieaire
```

### Submeniu: Deschide cont

**Pentru persoane fizice:**
1. ContCurent
2. ContEconomii
3. ContCurentAcumulare
4. DepozitBancar
5. ContInvestitii

**Pentru persoane juridice:**
1. ContBusiness
2. ContSweep

---

## Etapele rularii aplicatiei

1. **Pornire**: programul creeaza instanta Singleton a meniului
2. **Interactiune**: utilizatorul foloseste meniul ierarhizat
3. **Validare**: toate datele sunt validate si exceptiile sunt tratate
4. **Stocare**: clientii si produsele sunt salvate in vectori
5. **Operatiuni**: depuneri, retrageri, deschideri conturi
6. **Identificare dinamica**: se identifica automat tipul contului (prin `dynamic_cast`)
7. **Cleanup**: destructorul Meniu elibereaza memoria alocata la inchidere

---
