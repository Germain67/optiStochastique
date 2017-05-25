

#ifndef PROBLEM_DEP_H
#define PROBLEM_DEP_H

//#include "CRandomGenerator.h"
#include <stdlib.h>
#include <iostream>
#include <CIndividual.h>
#include <Parameters.h>
#include <cstring>
#include <sstream>

using namespace std;

class CRandomGenerator;
class CSelectionOperator;
class CGenerationalCriterion;
class CEvolutionaryAlgorithm;
class CPopulation;
class Parameters;

extern int EZ_POP_SIZE;
extern int OFFSPRING_SIZE;

// User classes

class Match {
public:
// Default methods for class Match
  Match(){  // Constructor
  }
  Match(const Match &EASEA_Var) {  // Copy constructor
    mdr=EASEA_Var.mdr;
  }
  virtual ~Match() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	EASEA_Line << this->mdr << " ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	(*EASEA_Line) >> this->mdr;
  }
  Match& operator=(const Match &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    mdr = EASEA_Var.mdr;
  return *this;
  }

  bool operator==(Match &EASEA_Var) const {  // Operator==
    if (mdr!=EASEA_Var.mdr) return false;
  return true;
  }

  bool operator!=(Match &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Match& EASEA_Var) { // Output stream insertion operator
    os <<  "mdr:" << EASEA_Var.mdr << "\n";
    return os;
  }

// Class members 
  int mdr;
};


class IndividualImpl : public CIndividual {

public: // in edtGenetic_ez the genome is public (for user functions,...)
	// Class members
  	// Class members 
  Match paper[200];


public:
	IndividualImpl();
	IndividualImpl(const IndividualImpl& indiv);
	virtual ~IndividualImpl();
	float evaluate();
	static unsigned getCrossoverArrity(){ return 2; }
	float getFitness(){ return this->fitness; }
	CIndividual* crossover(CIndividual** p2);
	void printOn(std::ostream& O) const;
	CIndividual* clone();

	unsigned mutate(float pMutationPerGene);

	void boundChecking();      

	string serialize();
	void deserialize(string EASEA_Line);

	friend std::ostream& operator << (std::ostream& O, const IndividualImpl& B) ;
	void initRandomGenerator(CRandomGenerator* rg){ IndividualImpl::rg = rg;}

};


class ParametersImpl : public Parameters {
public:
	void setDefaultParameters(int argc, char** argv);
	CEvolutionaryAlgorithm* newEvolutionaryAlgorithm();
};

/**
 * @TODO ces functions devraient s'appeler weierstrassInit, weierstrassFinal etc... (en gros edtGenetic_ezFinal dans le tpl).
 *
 */

void edtGenetic_ezInit(int argc, char** argv);
void edtGenetic_ezFinal(CPopulation* pop);
void edtGenetic_ezBeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void edtGenetic_ezEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm);
void edtGenetic_ezGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm);


class EvolutionaryAlgorithmImpl: public CEvolutionaryAlgorithm {
public:
	EvolutionaryAlgorithmImpl(Parameters* params);
	virtual ~EvolutionaryAlgorithmImpl();
	void initializeParentPopulation();
};

#endif /* PROBLEM_DEP_H */

