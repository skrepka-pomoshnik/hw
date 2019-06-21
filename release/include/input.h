#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "constants.hh"
#include "sets.hh"

inline static std::unordered_map<char, int> notestonumber = {{'c', 0}, {'d', 2}, {'e', 4}, {'f', 5}, {'g', 7}, {'a', 9}, {'b', 11}};
//std::unordered_map<int, std::string> cerror = {{1, "dissonance"}, {2, "starts or end on tonic"}};

std::vector<std::pair<int,int>> stringtophrase (std::string input);

bool checkstring (std::string input);
int ispropercf (std::vector<std::pair<int,int>> input);

#endif
