

#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

using namespace std;

#include "edtGenetic_ezIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;

CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL

// User declarations
#line 1 "edtGenetic_ez.ez"
 // This section is copied on top of the output file
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <cmath> //std::abs
#define NB_PAPERS 263

using namespace std;

typedef struct{
  double startHour;
  double endHour;
} Interval;

typedef struct{
  int ID;
  int ID_Track;
  int ID_Session;
  int duration;
  double fuseauHoraire;
  vector<Interval> dispoDay1;
  vector<Interval> dispoDay2;
  vector<Interval> dispoDay3;
} Paper;

ifstream fPaper;
vector<Paper> papers;





// User functions

#line 40 "edtGenetic_ez.ez"


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

std::vector<Interval> strToIntervals(std::string str)
{
  vector<Interval> res;
  if(str != "*"){
    std::vector<std::string> horaires = split(str, '[');
    for(size_t i = 1; i < horaires.size() ; i++)
    {
      std::vector<std::string> vals = split(horaires[i], ',');
      Interval cur_interval;
      cur_interval.startHour = atof(vals[0].c_str());
      cur_interval.endHour = atof(split(vals[1], ']')[0].c_str());
      res.push_back(cur_interval);
    }
  }
  return res;
}

void readPapers()
{
  std::ifstream file("Parser/papers.txt");
  std::string line;
  while (std::getline(file, line))
  {
      std::vector<std::string> lineElems = split(line, '|');
      Paper p;
      p.ID = atoi(lineElems[0].c_str());
      p.ID_Track = atoi(lineElems[1].c_str());
      p.ID_Session = atoi(lineElems[2].c_str());
      p.duration = atoi(lineElems[3].c_str());
      if(lineElems[4] == "*")
      {
        p.fuseauHoraire = 0;
      }
      else
      {
        p.fuseauHoraire = atof(lineElems[4].c_str());
      }
      p.dispoDay1 = strToIntervals(lineElems[5]);
      p.dispoDay2 = strToIntervals(lineElems[6]);
      p.dispoDay3 = strToIntervals(lineElems[7]);
      //p.startDate = NULL;
      papers.push_back(p);
  }
}

void printPaper(Paper p){
  std::cout << "ID : " << p.ID << " ID_SESSION : " << p.ID_Session << " ID_Track : " << p.ID_Track << '\n';
  std::cout << "duration : " << p.duration << " fuseauHoraire " << p.fuseauHoraire << '\n';
  if(p.dispoDay1.size() > 0)
  {
    std::cout << "Start hour Dispo day 1" << p.dispoDay1[0].startHour << '\n';
    std::cout << "End hour Dispo day 1" << p.dispoDay1[0].endHour << '\n';
  }
}

struct tm customDateToTm(CustomDate d)
{
  struct std::tm tmTime;
  tmTime.tm_year = d.year - 1900;
  tmTime.tm_mon = d.month - 1;
  tmTime.tm_mday = d.day;
  tmTime.tm_hour = d.hour;
  tmTime.tm_min = d.minute;
  tmTime.tm_sec = d.second;
  return tmTime;
}

bool isBeforeDate(CustomDate d1, CustomDate d2)
{
  struct tm t1 = customDateToTm(d1);
  struct tm t2 = customDateToTm(d2);
  time_t tt1 = mktime(&t1);
  time_t tt2 = mktime(&t2);
  return tt1 < tt2;
}

int differenceMinute(CustomDate d1, CustomDate d2)
{
  struct tm t1 = customDateToTm(d1);
  struct tm t2 = customDateToTm(d2);
  time_t tt1 = mktime(&t1);
  time_t tt2 = mktime(&t2);
  return (abs(tt1 - tt2) / 60);
}



// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 165 "edtGenetic_ez.ez"

  readPapers();
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 169 "edtGenetic_ez.ez"

  //TODO: Afficher les résultats
}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void edtGenetic_ezInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void edtGenetic_ezFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 439 "edtGenetic_ez.ez"
{
#line 173 "edtGenetic_ez.ez"

//cout << "At the beginning of each generation function called" << endl;
}
}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

//cout << "At the end of each generation function called" << endl;
}
}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

//cout << "At each generation before replacement function called" << endl;
}
}


IndividualImpl::IndividualImpl() : CIndividual() {
   
  // Genome Initialiser
#line 188 "edtGenetic_ez.ez"
 // "initializer" is also accepted
  for(int i = 0; i < NB_PAPERS; i++)
  {
    CustomDate d;
    d.year = 2015;
    if(globalRandomGenerator->tossCoin())
    {
      d.month = 9;
      d.day = 30;
      d.hour = (int) globalRandomGenerator->random(6,24);
    }
    else
    {
      d.month = 10;
      d.day = 1;
      d.hour = (int) globalRandomGenerator->random(0,24);
    }
    d.minute = (int) globalRandomGenerator->random(0, 60);
    d.second = (int) globalRandomGenerator->random(0, 60);
    (*this).paper[i].startDate = d;
  }

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    #line 254 "edtGenetic_ez.ez"
 // Returns the score as a real value
  //1/ Pour tout papers du track 15, il faut pas qu'il y ait un autre papers en meme temps
  //2/ Pour chaque paper, vérifier que c'est dans les dispo du chercheur
  //3/ Pour tout paper d'une meme session, il ne doit pas y avoir un autre paper en meme temps
  //4/ Il ne doit pas y avoir trop d'écart entre chaque paper
  CustomDate endDate;
  CustomDate endDate2;
  //int nbDe15 = 0;
  int totalScore = 0;
  int chercheurNonDispo = -100;
  int paperMemeSession = -100;
  int sessionPleniere = -100000;
  int ecartFaible = -1 ; // <2h -1 par heure
  int ecartMoyen = -5; // <4h -5 par heure
  int ecartFort = -10; // >4h -10 par heure
  std::vector<int>numSessions {4,5,6,7,8,9,10,11,12,13,15,16};

  /* for(int i = 0; i< NB_PAPERS;i++) // on compte le nombre de paper des sessions plénières
  {
     if(papers[i].ID_Session == 15)
     {
        nbDe15++;
     }
  }*/

  for(int i = 0; i < NB_PAPERS; i++) // check en même temps
  {
    for(int j = i + 1 ; j < NB_PAPERS; j++)
    {
      if(papers[i].ID_Session == papers[j].ID_Session || papers[i].ID_Session == 15 || papers[j].ID_Session == 15) //paper même session ou paper 15
      {
        endDate = (*this).paper[i].startDate;
        endDate.hour += papers[i].duration;
        if(endDate.hour >= 24)
        {
           endDate.hour = endDate.hour%24;
           endDate.day += 1;
        }
        if(endDate.day >= 30)
        {
           endDate.day = endDate.day%30;
           endDate.month +=1;
        }
        //TODO : Check qu'il n'y ait pas overlapping
        /*if(!isBeforeDate(endDate,Genome.paper[j].startDate))
        {
          if(isBeforeDate(Genome.paper[i].startDate,Genome.paper[j].startDate))
          {
            totalScore += paperMemeSession;
            if(papers[i].ID_Session==15) //si en plus il s'agit de la session 15
              totalScore += sessionPleniere;
          }
        }*/
      }
    }
  }

  for(int i = 0; i < NB_PAPERS; i++) // si Chercheur dispo
  {
        endDate = (*this).paper[i].startDate;
        int jour = endDate.day;
        int heure = endDate.hour;
        if(jour ==30)
        {
           for(size_t j = 0; j< papers[i].dispoDay1.size() ; j++)
           {
              if(heure < papers[i].dispoDay1[j].startHour && heure > papers[i].dispoDay1[j].endHour)
                totalScore += chercheurNonDispo;
           }
        }
        if(jour == 1)
        {
           for(size_t j = 0; j< papers[i].dispoDay2.size() ; j++)
           {
              if(heure < papers[i].dispoDay2[j].startHour && heure > papers[i].dispoDay2[j].endHour)
                totalScore += chercheurNonDispo;
           }
        }
        if(jour == 2)
        {
           for(size_t j = 0; j< papers[i].dispoDay3.size() ; j++)
           {
              if(heure < papers[i].dispoDay3[j].startHour && heure > papers[i].dispoDay3[j].endHour)
                totalScore += chercheurNonDispo;
           }
        }
  }

  for(size_t i = 0 ; i<numSessions.size(); i++) //vérification écart
  {
    vector<CustomDate> papiers;
    vector<int> duree;
    for(int j = 0; j<NB_PAPERS ; j++)
    {
      if(papers[j].ID_Session == numSessions[i])
      {
        papiers.push_back((*this).paper[j].startDate);
        duree.push_back(papers[j].duration);
      }
    }
    for(size_t k = 0 ; k < papiers.size()-1; k++)
    {
      for(size_t g = k ; g < papiers.size(); g++)
      {
        endDate = papiers[k];
        endDate.hour += duree[k];
        if(endDate.hour >24)
        {
          endDate.hour = endDate.hour%24;
          endDate.day += 1;
        }
        if(endDate.day>30)
        {
          endDate.day = endDate.day%30;
          endDate.month +=1;
        }

        endDate2 = papiers[g];
        endDate2.hour += duree[g];
        if(endDate2.hour >24)
        {
          endDate2.hour = endDate2.hour%24;
          endDate2.day += 1;
        }
        if(endDate2.day>30)
        {
          endDate2.day = endDate2.day%30;
          endDate2.month +=1;
        }
        int diff = differenceMinute(endDate,endDate2);
        if(diff<120)
        {
          totalScore += diff * ecartFaible;
        }
        else if(diff<240)
        {
          totalScore += diff * ecartMoyen;
        }
        else
        {
          totalScore += diff * ecartFort;
        }
      }
    }
  }

  return fitness =  totalScore;

  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.

}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	for(int EASEA_Ndx=0; EASEA_Ndx<263; EASEA_Ndx++)
		EASEA_Line << this->paper[EASEA_Ndx].serializer() <<" ";

    EASEA_Line << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	for(int EASEA_Ndx=0; EASEA_Ndx<263; EASEA_Ndx++)
		this->paper[EASEA_Ndx].deserializer(&EASEA_Line);

    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    {for(int EASEA_Ndx=0; EASEA_Ndx<263; EASEA_Ndx++)
       paper[EASEA_Ndx]=genome.paper[EASEA_Ndx];}



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part
  	#line 211 "edtGenetic_ez.ez"

  for(int i=0; i < NB_PAPERS; i++)
  {
    if(globalRandomGenerator->tossCoin())
    {
      child.paper[i] = parent1.paper[i];
    }
    else
    {
      child.paper[i] = parent2.paper[i];
    }
  }



	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	

}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


unsigned IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
  #line 225 "edtGenetic_ez.ez"
 // Must return the number of mutations
  float fMutProbPerGene=(((*EZ_current_generation)%40)/40.0)*(NB_PAPERS*.005)+.1;//.235;
  int nbMutations = 0;
  for(int i = 0; i < NB_PAPERS; i++)
  {
    if (globalRandomGenerator->tossCoin(fMutProbPerGene)){
      CustomDate d;
      d.year = 2015;
      if(globalRandomGenerator->tossCoin())
      {
        d.month = 9;
        d.day = 30;
        d.hour = (int) globalRandomGenerator->random(6,24);
      }
      else
      {
        d.month = 10;
        d.day = 1;
        d.hour = (int) globalRandomGenerator->random(0,24);
      }
      d.minute = (int) globalRandomGenerator->random(0, 60);
      d.second = (int) globalRandomGenerator->random(0, 60);
      (*this).paper[i].startDate = d;
      nbMutations++;
    }
  }
	return  nbMutations>0?true:false;

}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = false;
	this->nbGen = setVariable("nbGen",(int)300);

	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Tournament"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)0.600000);
	replacementPressure = setVariable("reduceFinalPressure",(float)2.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)2.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)2.000000);
	pCrossover = 1.000000;
	pMutation = 0.800000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)64);
	offspringPopulationSize = setVariable("nbOffspring",(int)64);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)1.000000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)1.000000));

	this->elitSize = setVariable("elite",(int)1);
	this->strongElitism = setVariable("eliteType",(int)1);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)300));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",1);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",1);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",0);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"edtGenetic_ez";
	this->plotOutputFilename = (char*)"edtGenetic_ez.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",1);
	std::string* ipFilename=new std::string();
	*ipFilename=setVariable("ipFile","ip.txt");

	this->ipFile =(char*)ipFilename->c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.300000);
    this->serverPort = setVariable("serverPort",2929);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	//EZ_NB_GEN = (unsigned*)setVariable("nbGen",300);
	EZ_current_generation=0;
  EZ_POP_SIZE = parentPopulationSize;
  OFFSPRING_SIZE = offspringPopulationSize;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("edtGenetic_ez.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}

