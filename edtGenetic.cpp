//\User declarations : // This section is copied on top of the output file
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
  int ID_Session;
  int ID_Track;
  int duration;
  int numPassageInSession;
  int fuseauHoraire;
  vector<Interval> dispoDay1;
  vector<Interval> dispoDay2;
  vector<Interval> dispoDay3;
  struct tm* startDate;
} Paper;

/*typedef struct{
  int ID;
  int ID_Track;
  //vector<int> papers;
  struct tm* startDate;
  //bool isPleniere;
} Session;*/

/* typedef struct{
  int ID;
  vector<int> sessions;
} Track; */

//
ifstream fPaper;
//,fSession, fTrack;
vector<Paper> papers;
vector<Session> sessions;
//vector<Track> tracks;

//\end

//\User functions:

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
  std::vector<std::string> day = split(str, '[');
  for(int i = 0; i<day.size() ; i++)
  {
    Interval cur_interval;
    std::vector<std::string> vals = split(day[i], ',');
    cur_interval.startHour = atoi(vals[0].c_str());
    cur_interval.endHour = atoi(split(vals[1], ']')[0].c_str());
    res.push_back(cur_interval);
  }
  return res;
}

std::vector<Paper> readPapers()
{
  std::ifstream file("papers.txt");
  std::vector<Paper> papers;
  std::string line;
  while (std::getline(file, line))
  {
      std::vector<std::string> lineElems = split(line, '|');
      Paper p;
      p.ID = atoi(lineElems[0].c_str());
      p.ID_Session = atoi(lineElems[1].c_str());
      p.duration = atoi(lineElems[2].c_str());
      p.numPassageInSession = atoi(lineElems[3].c_str());
      p.fuseauHoraire = atoi(lineElems[4].c_str());
      p.dispoDay1 = strToIntervals(lineElems[5]);
      p.dispoDay2 = strToIntervals(lineElems[6]);
      p.dispoDay3 = strToIntervals(lineElems[7]);
      papers.push_back(p);
  }
  return papers;
}

int main()
{
  readPapers();
  return 0;
}
