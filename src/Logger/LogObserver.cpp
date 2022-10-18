#include "LogObserver.h"

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Subject - (Observable)
//
// ----------------------------------------------------------------------------------------------------------------

void Subject::attach(ILogObserver* observer) {
  if(observer == nullptr){ throw std::runtime_error("Observer is null."); }
  observers.push_back(observer);
}

void Subject::detach(ILogObserver* observer) {
  for(auto it = observers.begin(); it != observers.end(); it++){
    if(*it == observer){
      observers.erase(it);
      return;
    }
  }
}

void Subject::notify(ILoggable* loggable) {
  for(auto& observer : observers){
    observer->update(loggable);
  }
}

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                LogObserver
//
// ----------------------------------------------------------------------------------------------------------------

void LogObserver::update(ILoggable* loggable) {
  // log the string
}

