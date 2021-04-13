// Copyright 2021 Baklanov 
#ifndef INCLUDE_TIMEDOOR_H_
#define INCLUDE_TIMEDOOR_H_

#include <ctime>

enum class doorState {OPEN,CLOSE};

class TimedDoor;

class DoorTimeAdapter {
private:
    doorState state;

public:
    DoorTimeAdapter():
    state(doorState::CLOSE) {}
    void Timeout(TimedDoor* door);
    doorState getState() { return state; };
    void setState(doorState state_) { state = state_; }
};

class TimedDoor {
 protected:
     DoorTimeAdapter* adapter;

 public:
     TimedDoor(DoorTimeAdapter* a) :
         adapter(a) {}
     doorState getState() { return adapter->getState(); };
     void open();
     void close();
     void doorTimeOut();
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

};

#endif // INCLUDE_TIMEDOOR_H_
