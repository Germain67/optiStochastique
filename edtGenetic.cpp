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

using namespace std;

typedef struct{
  int startHour;
  int endHour;
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
  struct tm* startDate;
} Paper;

ifstream fPaper;
vector<Paper> papers;

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
    for(int i = 1; i<horaires.size() ; i++)
    {
      Interval cur_interval;
      std::vector<std::string> vals = split(horaires[i], ',');
      cur_interval.startHour = atoi(vals[0].c_str());
      cur_interval.endHour = atoi(split(vals[1], ']')[0].c_str());
      res.push_back(cur_interval);
    }
  }
  return res;
}

std::vector<Paper> readPapers()
{
  std::ifstream file("Parser/papers.txt");
  std::vector<Paper> papers;
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
  return papers;
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

int main()
{
  std::cout << "Importing papers.txt" << '\n';
  std::vector<Paper> papers = readPapers();
  std::cout << "Importing finished" << '\n';
  return 0;
}
