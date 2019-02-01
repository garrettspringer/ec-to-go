#include<fstream>
#include<iostream>
#include<vector>
using namespace std;

int main()
{
  ifstream input("purine-ec.txt");
  ifstream typeIn("sorted-type.txt");
  ifstream ecIn("sorted-ec.txt");
  ifstream goIn("sorted-go.txt");
  ofstream goOut("foundGos.txt");
  ofstream typeOut("foundTypes.txt");

  vector<string> matchedGos;
  vector<string> matchedTypes;

  // Get terms to query in vector
  vector<string> lookupTerms;
  string lookie;
  while (input >> lookie)
    lookupTerms.push_back(lookie);

  // Read until you find the match
  for (auto query: lookupTerms) {
    string s, type, go;
    bool matchFound = false;
    while (ecIn >> s && matchFound == false) {
      // keep in line with other sorted files
      getline(typeIn, type);
      getline(goIn, go);

      if (query == s) {
        if (type == "found") {
          matchedTypes.push_back("No match found");
          matchedGos.push_back("No match found");
        } else {
          matchedTypes.push_back(type);
          matchedGos.push_back(go);
        }
        matchFound = true;
      }   
    }
    // Reset file pointer
    ecIn.clear();
    typeIn.clear();
    goIn.clear();
    ecIn.seekg(0, ios::beg);
    typeIn.seekg(0, ios::beg);
    goIn.seekg(0, ios::beg);
  }

  for (auto i : matchedGos)
    goOut << i << "\n"; 

  for (auto i : matchedTypes)
    typeOut << i << "\n";

  return 0;
}
