//
// Created by OSiradze on 26.08.25.
//

#pragma once

struct TouchDown {
    bool start = false;
    bool active = false;
    int x = 0;
    int y = 0;
    float floatX = 0;
    float floatY = 0;

    void reset() {
        start = false;
    }
};
