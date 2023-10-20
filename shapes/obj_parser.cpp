#include "obj_parser.h"

OBJ_Parser::OBJ_Parser(Group *default_group, std::vector<Tuple> vertices, int bad_lines) {
    _default_group = default_group;
    _vertices = vertices;
    _bad_lines = bad_lines;
}

OBJ_Parser parse_obj_file(std::ifstream &fin) {
    int bad_lines = 0;
    size_t pos = 0;
    std::string arg;
    std::string arg1;
    std::string arg2;
    std::string arg3;
    std::string command;
    std::string temp;
    std::string delimiter = " ";
    std::string group_name;
    std::vector<std::string> tokens;
    std::vector<Triangle *> triangles;
    std::vector<Tuple> vertices;
    std::vector<Tuple> face_vertices;
    bool bad_args = false;
    
    Group *default_group = new Group();
    default_group->_name = "Default Group";
    Group *current_group = default_group;
    
    // vertices[0] should not be used
    vertices.push_back(create_point(0.0, 0.0, 0.0));

    while (!fin.eof()) {
        tokens.clear();
        getline(fin, temp);
        
        if (temp == "") { continue; }

        pos = temp.find(delimiter);
        while (pos != std::string::npos) {
            tokens.push_back(temp.substr(0, pos));
            temp.erase(0, pos + delimiter.length());
            pos = temp.find(delimiter);
        }
        // one last token to add
        tokens.push_back(temp);
        
        // command
        command = tokens[0];
        if (command == "v") {
            if (tokens.size() != 4) { bad_lines++; continue; }

            // arg1
            arg1 = tokens[1];
            if (!is_dec(arg1)) { bad_lines++; continue; }
            arg1 = strip_zeros_dec(arg1);

            // arg2
            arg2 = tokens[2];
            if (!is_dec(arg2)) { bad_lines++; continue; }
            arg2 = strip_zeros_dec(arg2);

            // arg3
            arg3 = tokens[3];
            if (!is_dec(arg3)) { bad_lines++; continue; }
            arg3 = strip_zeros_dec(arg3);

            vertices.push_back(create_point(std::stod(arg1), std::stod(arg2), std::stod(arg3)));
        } else if (command == "f") {
            if (tokens.size() == 1) { bad_lines++; continue; }

            // clean args
            for (int i = 1; i < tokens.size(); i++) {
                arg = tokens[i];
                if (!is_uint(arg)) { bad_args = true; continue; }
                tokens[i] = strip_zeros_uint(arg);
            }
            if (bad_args) { bad_lines++; continue; }

            // process args
            face_vertices.push_back(vertices[0]);
            for (int i = 1; i < tokens.size(); i++) { face_vertices.push_back(vertices[stoi(tokens[i])]); }
            
            triangles = fan_triangulation(face_vertices);

            for (int i = 0; i < triangles.size(); i++) { current_group->add_child(triangles[i]); }
            face_vertices.clear();
        } else if (command == "g") {
            if (current_group != default_group) { default_group->add_child(current_group); }
            current_group = new Group;
            group_name = "";
            for (int i = 1; i < tokens.size(); i++) {
                group_name += tokens[i];
                if (i < tokens.size() - 1) { group_name += " "; }
            }
            current_group->_name = group_name;
        } else { bad_lines++; continue; }
    }

    // push final group (if needed)
    if (group_name != "") { default_group->add_child(current_group); }

    return OBJ_Parser(default_group, vertices, bad_lines);
}

bool is_uint(std::string str) {
    if (str.length() == 0) { return false; }
    if (str == "0") { return false; }
	for (int i = 0; i < str.length(); i++) {
        if (str[i] < '0' || str[i] > '9') { return false; }
	}
    return true;
}

bool is_dec(std::string str) {
	if (str.length() == 0) { return false; }
	int digits = 0;
	int dots = 0;
	for (int i = 0; i < str.length(); i++) {
		if (i == 0 && str[i] == '-') { continue; }
		else if (str[i] >= '0' && str[i] <= '9') {
			digits++;
			continue;
		}
		else if (str[i] == '.' && i != str.length() - 1) {
			dots++;
			if (digits == 0 && dots == 1) { return false; }
			if (dots > 1) { return false; }
		}
		else { return false; }
	}
	return digits > 0;
}

std::string strip_zeros_uint(std::string str) {
	std::string ret = str;
	ret.erase(0, std::min(ret.find_first_not_of('0'), ret.size() - 1));
	return ret;
}

std::string strip_zeros_dec(std::string str) {
	std::string ret = str;
	bool is_negative = false;
	if (ret.length() == 0) { return ret; }
	if (ret[0] == '-') {
		is_negative = true;
		ret.erase(0, 1);
	}
	size_t pos = ret.find('.');
	
	if (pos == std::string::npos) {
		// no decimal
		ret.erase(0, std::min(ret.find_first_not_of('0'), ret.size() - 1));
		ret += ".0";
		if (is_negative) { ret = "-" + ret; }
	} else {
		// decimal
		std::string left = ret.substr(0, pos);
		left.erase(0, std::min(left.find_first_not_of('0'), left.size() - 1));

		std::string right = ret.substr(pos + 1);
		right.erase(right.find_last_not_of('0') + 1, std::string::npos);
		if (right.size() == 0) { right = "0"; }

		ret = left + '.' + right;
		if (is_negative && (left != "0" || right != "0")) { ret = "-" + ret; }
	}

	return ret;
}

std::vector<Triangle *>  fan_triangulation(std::vector<Tuple> vertices) {
    std::vector<Triangle *> triangles;
    for (int i = 2; i < vertices.size() - 1; i++) {
        triangles.push_back(new Triangle(vertices[1], vertices[i], vertices[i + 1]));
    }
    return triangles;
}