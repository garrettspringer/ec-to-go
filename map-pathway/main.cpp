/*
 * Given a txt file of ec numbers that belong to a specific pathway
 * an output file is created that gives the respective GO terms for the EC
 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
  ifstream fin("input.txt");
  ifstream sorted_types("sorted-type.txt");
  ifstream sorted_gos("sorted-go.txt");
  ifstream sorted_ecs("sorted-ec.txt");
  ofstream fout("output.txt");

  vector<string> ec, sorted_ec_vec, go, type, ec_to_go, ec_to_type;

  string s;
  while(getline(fin, s)) ec.emplace_back(s);
  while(getline(sorted_types, s)) type.emplace_back(s);
  while(getline(sorted_gos, s)) go.emplace_back(s);
  while(getline(sorted_ecs, s)) sorted_ec_vec.emplace_back(s);

  for (string enz : ec) {
    bool found = false;
    int counter = 0;
    for (string g : sorted_ec_vec) {
      if (enz == g) {
        ec_to_type.emplace_back(type[counter]);
        ec_to_go.emplace_back(go[counter]);
        found = true; 
        break;
      }
      counter++;
    }      
    if (found == false) {
      ec_to_type.emplace_back("Not Found");
      ec_to_go.emplace_back("Not Found");
    }
  }

  for (unsigned int i=0; i<ec.size(); i++) 
    fout << ec[i] << " = " << ec_to_go[i] << " : " << ec_to_type[i] << "\n"; 
  
  return 0;
}
