// Copyright 2021 Baklanov 
#include "TimedDoor.h"
#include <iostream>

void DoorTimeAdapter::Timeout(TimedDoor* door) {
    door->doorTimeOut();
}

void TimedDoor::open() {
    adapter->setState(doorState::OPEN);
    Timer a(this->adapter, this);
}

void TimedDoor::close() {
    adapter->setState(doorState::CLOSE);
}

void TimedDoor::doorTimeOut() {
    try {
        this->throwState();
    }
    catch (doorState a){
        if (a == doorState::OPEN) {
            std::cout << "close the door!" << std::endl;
        }
    }
}
