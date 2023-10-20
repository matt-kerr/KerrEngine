// Matthew Kerr

#ifndef SAMPLE_SCENE_H
#define SAMPLE_SCENE_H

#include <iostream>
#include <string>
#include <fstream>
#include "../kerr_engine.h"

class SampleScene {
    public:
        SampleScene() { throw std::invalid_argument("SampleScene cannot be instantiated without parameters."); }
        virtual ~SampleScene() = default;
       
        static void run(int width, int height, std::string filepath);
};

#endif