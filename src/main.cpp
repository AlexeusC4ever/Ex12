// Copyright 2021 Baklanov
#include "TimedDoor.h"
#include <iostream>

int main() {
    DoorTimeAdapter* a = new DoorTimeAdapter();
    TimedDoor* door = new TimedDoor(a);
    door->unlock();
}
