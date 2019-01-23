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

  vector<string> vecOfTypes;
  vector<string> vecOfGos;

  // for every ec, match it to possible go terms
  // search document for term
  for (string i : ec) {
    char c;
    string goTerm = "";
    string goNum = "";
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

            // read the go number
            string numText = "";
            for (int z=0; z<3; z++) 
              goFile >> c;
            
            goFile >> c;
            while (c != 'E') {
              goNum+=c;
              goFile >> c;
            } 
            goNum+=' ';
          }
        }
      }
    }    
    // add place holder if no match found
    if (matchFound == false) {
      vecOfTypes.push_back("No match found");
      vecOfGos.push_back("No match found");
    } else {
      vecOfTypes.push_back(goTerm);
      vecOfGos.push_back(goNum);
    }

    // reset go file to beginning
    goFile.clear();
    goFile.seekg(0, ios::beg);
  } 

  // Print sorted types to output file
  for (auto i : vecOfTypes)
    foutType << i << "\n";

  // Print sorted gos to output file
  for (auto i : vecOfGos)
    fout << i << "\n";

  return 0;
}
