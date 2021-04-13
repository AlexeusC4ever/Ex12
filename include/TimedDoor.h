// Copyright 2021 Baklanov
#ifndef INCLUDE_TIMEDDOOR_H_
#define INCLUDE_TIMEDDOOR_H_

#include <ctime>

class DoorTimerAdapter;
class Timer;
class Door;
class TimedDoor;

class TimerClient {
public:
    virtual void Timeout() = 0;
};

class Door {
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool isDoorOpened() = 0;
};

enum class doorState {OPEN, CLOSE};

class TimedDoor;

class DoorTimeAdapter {
 private:
    doorState state;

 public:
    explicit DoorTimeAdapter():
    state(doorState::CLOSE) {}
    void Timeout(TimedDoor* door);
    doorState getState() { return state; };
    void setState(doorState state_) { state = state_; }
};

class TimedDoor {
 protected:
     DoorTimeAdapter* adapter;

 public:
     explicit TimedDoor(DoorTimeAdapter* a) :
         adapter(a) {}
     doorState getState() { return adapter->getState(); };
     void unlock();
     void lock();
     void doorTimeOut();
     bool isDoorOpened();
     doorState throwState() { throw adapter->getState(); }
};

class Timer {
 private:
     DoorTimeAdapter* adapter;

 public:
     Timer(DoorTimeAdapter* adapter_, TimedDoor* door) :
         adapter(adapter_) {
         time_t start = time(nullptr);
         while (time(nullptr) - start < 8) {
             continue;
         }
         adapter->Timeout(door);
     }
     TimerClient* client;
     void sleep(int);
     void tregister(int, TimerClient*);
};
#endif  // INCLUDE_TIMEDDOOR_H_
