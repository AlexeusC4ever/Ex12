// Copyright 2021 Baklanov
#include "TimedDoor.h"
#include <iostream>

int main() {
    TimedDoor tDoor(5);
    tDoor.lock();
    tDoor.unlock();
    return 0;
}
