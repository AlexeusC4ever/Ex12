// Copyright 2021 Baklanov
#ifndef INCLUDE_TIMEDDOOR_H_
#define INCLUDE_TIMEDDOOR_H_

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

class DoorTimerAdapter : public TimerClient {
 private:
    TimedDoor* door;

 public:
     explicit DoorTimerAdapter(TimedDoor* door_) :
         door(door_) {}
    void Timeout() override;
};

class TimedDoor : public Door {
 private:
    DoorTimerAdapter* adapter;
    int iTimeout;
    bool opened;

 public:
     explicit TimedDoor(int a):
     iTimeout(a), opened(true) {
         adapter = new DoorTimerAdapter(this);
     }
     bool isDoorOpened() { return opened; }
    void unlock();
    void lock();
    void DoorTimeOut();
    void throwState();
};

class Timer {
 private:
    TimerClient* client;
    void sleep(int);

 public:
     explicit Timer(TimerClient* client_) :
         client(client_) {}
    void tregister(int, TimerClient*);
};
#endif  // INCLUDE_TIMEDDOOR_H_
