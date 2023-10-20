// Matthew Kerr

#ifndef SAMPLE_TEDDY_H
#define SAMPLE_TEDDY_H

#include <iostream>
#include <string>
#include <fstream>
#include "../kerr_engine.h"

class SampleTeddy {
    public:
        SampleTeddy() { throw std::invalid_argument("SampleTeddy cannot be instantiated without parameters."); }
        virtual ~SampleTeddy() = default;
       
        static void run(int width, int height, std::string filepath);
};

#endif