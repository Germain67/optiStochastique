/*

tracks
  id
  list <session>

session
  id
  idTrack
  list<papers>
  startDate
  isPleniere

papers
  id
  idSession
  duration
  numPassageInSession
  fuseauHoraire
  dispoDay[0-3] => interval

*/

  typedef struct{
    int startHour;
    int endHour;
  } Interval;

  typedef struct{
    int ID;
    int ID_Session;
    int duration;
    int numPassageInSession;
    int fuseauHoraire;
    vector<Interval> dispoDay1;
    vector<Interval> dispoDay2;
    vector<Interval> dispoDay3;
  } Paper;

  typedef struct{
    int ID;
    int ID_Track ;
    vector<Paper> papers;
    struct tm* startDate;
    bool isPleniere;
  } Session;

  typedef struct{
    int ID;
    vector<Session> sessions;
  } Track;
