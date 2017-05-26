

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

class CustomDate {
public:
// Default methods for class CustomDate
  CustomDate(){  // Constructor
  }
  CustomDate(const CustomDate &EASEA_Var) {  // Copy constructor
    minute=EASEA_Var.minute;
    hour=EASEA_Var.hour;
    day=EASEA_Var.day;
  }
  virtual ~CustomDate() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
	EASEA_Line << this->minute << " ";
	EASEA_Line << this->hour << " ";
	EASEA_Line << this->day << " ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
	(*EASEA_Line) >> this->minute;
	(*EASEA_Line) >> this->hour;
	(*EASEA_Line) >> this->day;
  }
  CustomDate& operator=(const CustomDate &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    minute = EASEA_Var.minute;
    hour = EASEA_Var.hour;
    day = EASEA_Var.day;
  return *this;
  }

  bool operator==(CustomDate &EASEA_Var) const {  // Operator==
    if (minute!=EASEA_Var.minute) return false;
    if (hour!=EASEA_Var.hour) return false;
    if (day!=EASEA_Var.day) return false;
  return true;
  }

  bool operator!=(CustomDate &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const CustomDate& EASEA_Var) { // Output stream insertion operator
    os <<  "minute:" << EASEA_Var.minute << "\n";
    os <<  "hour:" << EASEA_Var.hour << "\n";
    os <<  "day:" << EASEA_Var.day << "\n";
    return os;
  }

// Class members 
  int minute;
  int hour;
  int day;
};

class Match {
public:
// Default methods for class Match
  Match(){  // Constructor
  }
  Match(const Match &EASEA_Var) {  // Copy constructor
    startDate=EASEA_Var.startDate;
  }
  virtual ~Match() {  // Destructor
  }
  string serializer() {  // serialize
  	ostringstream EASEA_Line(ios_base::app);
		EASEA_Line << this->startDate.serializer() <<" ";
  	return EASEA_Line.str();
  }
  void deserializer(istringstream* EASEA_Line) {  // deserialize
  	string line;
		this->startDate.deserializer(EASEA_Line);
  }
  Match& operator=(const Match &EASEA_Var) {  // Operator=
    if (&EASEA_Var == this) return *this;
    startDate = EASEA_Var.startDate;
  return *this;
  }

  bool operator==(Match &EASEA_Var) const {  // Operator==
    if (startDate!=EASEA_Var.startDate) return false;
  return true;
  }

  bool operator!=(Match &EASEA_Var) const {return !(*this==EASEA_Var);} // operator!=

  friend ostream& operator<< (ostream& os, const Match& EASEA_Var) { // Output stream insertion operator
    os <<  "startDate:" << EASEA_Var.startDate << "\n";
    return os;
  }

// Class members 
  CustomDate startDate;
};


class IndividualImpl : public CIndividual {

public: // in edtGenetic_ez the genome is public (for user functions,...)
	// Class members
  	// Class members 
  Match paper[263];


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

