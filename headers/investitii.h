class ActivFinanciar{

};

class Actiune : virtual public ActivFinanciar{

};

class Obligatiune : virtual public ActivFinanciar{

};

class FondMutualMixt{

};

class TitluDeStat : virtual public Obligatiune{

};

class ActiuneFractionara : virtual public Actiune{

};