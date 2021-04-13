#include "TimedDoor.h"
#include <iostream>
#include <string>
#include <ctime>

void TimedDoor::unlock() {
    opened = true;
    Timer* a = new Timer(this->adapter);
    a->tregister(this->iTimeout, adapter);
}

void TimedDoor::lock() {
    opened = false;
}

void Timer::sleep(int Time) {
    time_t a = time(nullptr);
    while (time(nullptr) - a < Time) {
        continue;
    }
}

void Timer::tregister(int timeout, TimerClient* client) {
    sleep(timeout);
    client->Timeout();
}

void TimedDoor::DoorTimeOut() {
    try {
        if (opened) throw std::string("Close the door!");
    }
    catch (const std::string mes) {
        std::cout << mes << std::endl;
    }
}

void TimedDoor::throwState() {
    try {
        if (opened) throw std::string("the door is opened!");
        throw std::string("the door is closed!");
    }
    catch (std::string mes) {
        std::cout << mes << std::endl;
    }
}

void DoorTimerAdapter::Timeout() {
    this->door->DoorTimeOut();
}