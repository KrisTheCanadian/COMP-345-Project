#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>

class ILogObserver;
class GameEngine;

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
  virtual void resetObservers() = 0;
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
  void resetObservers() override;

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
private:
    // Object Owner
    GameEngine* game;

public:

    // Constructors
    explicit LogObserver(GameEngine*);
    ~LogObserver() override = default;
    explicit LogObserver(LogObserver*);

    void update(ILoggable*) override;

    // Stream Operator
    friend std::ostream &operator << (std::ostream &out, const LogObserver &log);

    // Assignment Operator
    LogObserver& operator=(const LogObserver &other);

};
