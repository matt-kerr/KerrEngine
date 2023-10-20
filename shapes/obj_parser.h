// Matthew Kerr

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../kerr_math.h"
#include "../primitives/tuple.h"
#include "shape.h"
#include "group.h"
#include "triangle.h"

class Tuple;
class Shape;
class Group;
class Triangle;
class OBJ_Parser {
    public:
        Group *_default_group = nullptr;
        std::vector<Tuple> _vertices;
        int _bad_lines;

        OBJ_Parser() { throw std::invalid_argument("OBJ Parser requires arguments"); }
        virtual ~OBJ_Parser() = default;
        OBJ_Parser(Group *g, std::vector<Tuple> vertices, int bad_lines);

};

OBJ_Parser parse_obj_file(std::ifstream &fin);
bool is_uint(std::string str);
bool is_dec(std::string str);
std::string strip_zeros_uint(std::string str);
std::string strip_zeros_dec(std::string str);
std::vector<Triangle *> fan_triangulation(std::vector<Tuple> vertices);