#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

class ILogObserver;

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Loggable
//
// ----------------------------------------------------------------------------------------------------------------

class ILoggable {
public:
  virtual std::string stringToLog() = 0;
  virtual ~ILoggable()= default;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                ISubject
//
// ----------------------------------------------------------------------------------------------------------------

class ISubject {
public:
  virtual ~ISubject() = default;
  virtual void attach(ILogObserver* observer) = 0;
  virtual void detach(ILogObserver* observer) = 0;
  virtual void notify(ILoggable*) = 0;
};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                Subject
//
// ----------------------------------------------------------------------------------------------------------------

class Subject : ISubject {
private:
  std::vector<ILogObserver*> observers;
public:
  Subject() = default;
  ~Subject() override = default;

  void attach(ILogObserver* observer) override;
  void detach(ILogObserver* observer) override;
  void notify(ILoggable*) override;

};

// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                ILogObserver
//
// ----------------------------------------------------------------------------------------------------------------

class ILogObserver {
public:
  virtual ~ILogObserver() = default;
  virtual void update(ILoggable*) = 0;
};


// -----------------------------------------------------------------------------------------------------------------
//
//
//                                                LogObserver
//
// ----------------------------------------------------------------------------------------------------------------

class LogObserver : ILogObserver {
public:
  LogObserver() = default;
  ~LogObserver() override = default;
  void update(ILoggable*) override;
};
