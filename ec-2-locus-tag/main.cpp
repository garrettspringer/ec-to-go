/*
 * Given a txt file of ec numbers that belong to a specific pathway
 * an output file is created that gives the respective GO terms for the EC
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
  ifstream fin("input.txt");
  ifstream ec_2_locus("ec-2-locus.txt");
  ofstream fout("output.txt");

  vector<string> ec_to_tag, found_ec_matches;
  unordered_map<string, vector<string>> hm;

  string s;
  while(fin >> s) ec_to_tag.emplace_back(s);

  // Hash each EC to Locus tag
  s = "";
  while(getline(ec_2_locus, s, 'x')) {
    // Skip reading the newline (\n) character
    ec_2_locus.ignore();

    // Read the tag
    string tag = "";
    unsigned int i=0;
    for ( ; s[i]!='a'; i++) 
      tag+=s[i];

    // Read the EC
    vector<string> ec_vec;
    string ec_num = "";
    i+=2;
    for ( ; s[i]!='b'; i++) {
      if (s[i] == '_') {
        ec_vec.emplace_back(ec_num); 
        ec_num = "";
      } else {
        ec_num+=s[i];
      }
    }
    ec_vec.emplace_back(ec_num);
     
    // Hash the numbers
    hm[tag] = ec_vec;    
  }
  
  // Lookup matches
  for (string enz : ec_to_tag) {
    bool first = true;
    for (auto i : hm) {
      for (auto j : i.second) {
        if (j == enz) {
          if (first == true) {
            fout << enz << " : " << i.first; 
            first = false;
            break;
          } else {
            fout << " / " << i.first;
            break;
          }
        }
      }
    }
    fout << "\n";
  }
}
