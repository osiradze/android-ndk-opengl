//
// Created by OSiradze on 09.08.25.
//
#include "Attenuation.h"

std::map<int, Attenuation> getAttenuation() {
    static std::map<int, Attenuation> attenuationMap = {
            { 7,    {1.0f, 0.7f,    1.8f} },
            { 13,   {1.0f, 0.35f,   0.44f} },
            { 20,   {1.0f, 0.22f,   0.20f} },
            { 32,   {1.0f, 0.14f,   0.07f} },
            { 50,   {1.0f, 0.09f,   0.032f} },
            { 65,   {1.0f, 0.07f,   0.017f} },
            { 100,  {1.0f, 0.045f,  0.0075f} },
            { 160,  {1.0f, 0.027f,  0.0028f} },
            { 200,  {1.0f, 0.022f,  0.0019f} },
            { 325,  {1.0f, 0.014f,  0.0007f} },
            { 600,  {1.0f, 0.007f,  0.0002f} },
            { 3250, {1.0f, 0.0014f, 0.000007f} }
    };
    return attenuationMap;
}


Attenuation Attenuation::getNearestAttenuation(float distance) {
    auto attenuationMap = getAttenuation();
    if (attenuationMap.empty()) return {1.0f, 0.0f, 0.0f};

    // First element with key >= distance
    auto it = attenuationMap.lower_bound(static_cast<int>(distance));

    if (it == attenuationMap.begin()) return it->second; // smaller than min
    if (it == attenuationMap.end())   return attenuationMap.rbegin()->second; // bigger than max

    auto prevIt = std::prev(it);
    return (std::fabs(distance - prevIt->first) <= std::fabs(distance - it->first))
           ? prevIt->second
           : it->second;
}

