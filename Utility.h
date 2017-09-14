#ifndef _Utility_h_
#define _Utility_h_

#include <iostream>
#include <chrono>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;


#define property(type, variable) \
  private:\
    type variable;\
  public:\
    type get_##variable () { return variable ; }\
    type set_##variable ( type val) { variable = val; }

#define property_get(type, variable) \
  private:\
    type variable;\
  public:\
    type get_##variable () { return variable ; }\


// random float between rangeStart and rangeEnd
#define randf(rangeStart, rangeEnd) ((((float)rand() / (float)INT_MAX) * (rangeEnd - rangeStart)) + rangeStart)

// triangular matrix indexing
#define triMtxN(N) (((N*N) + N) / 2.)
#define triMtxI(j, i) (i + j*(j+1)/2)
#define triMtx(i, j) (i > j ? triMtxI(i, j) : triMtxI(j, i))


#define degreesToRadians(deg) (deg*M_PI/180.)
#define radiansToDegrees(rad) (rad*180./M_PI)


#define charToDouble(str) strtod(str, NULL)
#define stringToDouble(cppstr) strtod(cppstr.c_str(), NULL)
#define stringToInt(cppstr) atoi(cppstr.c_str())



// trim from start
static inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

// timing

class Timer {
private:
  timeval startTime;
  double duration;

public:
  void start(){
    gettimeofday(&startTime, NULL);
  }

  void stop(){
    timeval endTime;
    long seconds, useconds;

    gettimeofday(&endTime, NULL);

    seconds  = endTime.tv_sec  - startTime.tv_sec;
    useconds = endTime.tv_usec - startTime.tv_usec;

    duration = seconds + useconds/1000000.0;
  }

  void print(ostream *stream){
    double seconds = duration;

    // calculate human time
    int minutes = seconds / 60;
    seconds -= (minutes * 60.);
    int hours = minutes / 60;
    minutes -= (hours * 60);

    // output timing information
    *stream << "time: ";
    if(hours > 0.) {
      *stream << hours << " hours ";
    }
    if(minutes > 0.) {
      *stream << minutes << " minutes ";
    }
    *stream << seconds << " seconds elapsed." << endl;
  }
};

#endif
