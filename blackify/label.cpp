#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() 
{
  ifstream blk("all.txt");
  ifstream blu("pf.txt");
  ifstream redf("pd.txt");  

  ofstream foutBlue("blue.txt");
  ofstream foutRed("red.txt");
  ofstream foutBlack("black.txt");
  ofstream colorFile("colorFile.txt");
  ofstream totalEC("totalEC.txt");
  ofstream repeatFile("repeatFile.txt");

  vector<string> black, blue, red;

  // read in all pf
  string s;
  while (blu >> s) 
    blue.push_back(s); 

  // read in all pd
  while (redf >> s) 
    red.push_back(s);

  // ensure there aren't any overlap in red and blue
  vector<string> repeat;
  for (auto i : blue)
    for (auto j : red) 
      if (i==j) {
        bool rep = false;
        for (auto k : repeat)
          if (i == k) rep = true;
        if (rep==false) repeat.push_back(i);
      }

  // Print out all the blue ECs
  for (auto i : blue) {
    bool valid = true;
    for (auto j : repeat) 
      if (i==j) valid = false;
      
    if (valid) {
      foutBlue << i << " blue\n"; 
      colorFile << i << " blue\n";
      totalEC << i << "\n";
    }
  }

  // Print out all the red ECs
  for (auto i : red) {
    bool valid = true;
    for (auto j : repeat) 
      if (i==j) valid = false;

    if (valid) {
      foutRed << i << " red\n";
      colorFile << i << " red\n";
      totalEC << i << "\n";
    }
  }

  // The ec is black ONLY if it isn't blue or red
  while (blk >> s) {
    bool isBlack = true;

    for (auto i : blue)
      if (i == s) isBlack = false;

    for (auto i : red)
      if (i == s) isBlack = false;

    // if it's a repeat, it's automatically black
    for (auto i : repeat)
      if (i == s) isBlack = true;

    if (isBlack == true)
      black.push_back(s);
  }

  // Print all black ECs
  for (auto i : black) {
    foutBlack << i << " black\n";
    colorFile << i << " black\n";
    totalEC << i << "\n";
  }

  // Print out all the ECs which appear in blue and red file
  for (auto i : repeat)
    repeatFile << i << "\n";   

  return 0;
}
