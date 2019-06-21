#pragma once
#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "constants.hh"

typedef std::vector<std::pair<int,int>> phrase;
const std::string nname[] = {"One","Two","Three","Four"};
const std::string version = "\\version \"2.18.2\"\n"; //stable
const std::string footer = R"(\score {
  <<
    \new StaffGroup  <<
      \new Staff <<
        \clef "treble_8"
        \context Voice  \voicea
        \context Voice \voiceb
      >>
      \new TabStaff = "guitar tab" <<
        \context TabVoice  \voicea
        \context TabVoice \voiceb
      >>
    >>
  >>
\layout {}
\midi {}
})";

void OutputtoLily (std::vector<phrase> input, std::string outputname);

#endif
