// Matthew Kerr

#ifndef SAMPLE_GLASS_SPHERES_H
#define SAMPLE_GLASS_SPHERES_H

#include <iostream>
#include <string>
#include <fstream>
#include "../kerr_engine.h"

class SampleGlassSpheres {
    public:
        SampleGlassSpheres() { throw std::invalid_argument("SampleGlassSpheres cannot be instantiated without parameters."); }
        virtual ~SampleGlassSpheres() = default;
       
        static void run(int width, int height, std::string filepath);
};

#endif