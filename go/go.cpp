#include<iostream>
#include<unordered_map>
#include<vector>
#include<fstream>
#include<cstdio>
using namespace std;

int main()
{
  ifstream fin("sorted-ec.txt");
  ifstream goFile("go-file.txt"); 
  ofstream fout("sorted-go.txt");
  ofstream foutType("sorted-type.txt");

  // array of EC
  string s;
  vector<string> ec;
  while (fin >> s)
    ec.push_back(s);

  unordered_map<string, vector<string>> ec2go;
  vector<string> vecOfTypes;
  vector<string> vecOfGos;

  // for every ec, match it to possible go terms
  // search document for term
  for (string i : ec) {
    char c;
    vecOfGos.clear();
    string goTerm = "";
    unsigned int count = 0;
    bool matchFound = false;
    while (goFile >> c) {
      count++;
      if (c == i[0]) {
        bool match = true;
        for (unsigned int j=1; j<i.size(); j++) {
          goFile >> c;
          if (c != i[j]) {
            match = false;
            break;
          }
        }
        
        if (match == true) { 
          // check that the ec is the same (1.1.1.1 != 1.1.1.10)
          goFile >> c;
          bool verified = false;
          if (c == '>') verified = true;

          if (verified) {
            matchFound = true;
            // keep reading until you encounter "GO:"
            for (int z=0; z<3; z++) 
              goFile >> c;

            // read until ';'
            string typeText = "";
            goFile >> typeText;
            while (typeText != ";") {
              goTerm+=typeText;
              goTerm+=' ';
              goFile >> typeText;
            }
            // add type to vector of types
            vecOfTypes.push_back(goTerm);
          }

          // Add the go number to the output file
          //vecOfGos.push_back(goNum);
        }
      }
    }    
    // Add vector list of go terms to corresponding ec
    ec2go[i] = vecOfGos;

    // reset go file to beginning
    goFile.clear();
    goFile.seekg(0, ios::beg);

    // add place holder if no match found
    if (matchFound == false) vecOfTypes.push_back("No match found");
  } 

  // Print sorted types to output file
  for (auto i : vecOfTypes)
    foutType << i << "\n";

  // Print sorted gos to output file
  vector<string> goTerms;
  for (auto i : ec2go) {
    goTerms.clear();
    goTerms = i.second;
    for (auto j : goTerms)
      fout << j << " ";
    fout << "\n";
  }

  return 0;
}
