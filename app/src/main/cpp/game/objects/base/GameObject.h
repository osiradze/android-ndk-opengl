//
// Created by OSiradze on 13.07.25.
//

#pragma once

class GameObject {
    public:
        virtual void init() {};
        virtual void onDraw() {};
        virtual void destroy() {};
};