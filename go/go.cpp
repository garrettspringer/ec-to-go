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
    // Helps if there are no explicit matches to settle for a general match
    bool matchCovered = false;
    bool generalSearch = false;
    int failCount = 0;
    while (matchCovered == false) {
      bool firstMatch = true;
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
            
            // automatically pass if doing general search
            if (generalSearch == true) verified = true;

            if (verified == true) {
              matchFound = true;
              // keep reading until you encounter "GO:"
              for (int z=0; z<3; z++) 
                goFile >> c;

              // read until ';'
              string typeText = "";
              goFile >> typeText;
              if (firstMatch == false) goTerm+="; ";
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
              if (firstMatch == false) goNum+=" ; ";
              while (c != 'E') {
                goNum+=c;
                goFile >> c;
              } 

              firstMatch = false;
            }
          }
        }
      }    
      // add place holder if no match found
      if (matchFound == false) {
        failCount++;
        // Give up if second search doesn't reveal match
        if (failCount > 1) {
          matchCovered = true;
          vecOfTypes.push_back("No match found");
          vecOfGos.push_back("No match found");
        } else generalSearch = true;
        cout << "ahhh\n";
      } else {
        cout << i << "\n";
        matchCovered = true;
        vecOfTypes.push_back(goTerm);
        vecOfGos.push_back(goNum);
      }

      // Reset the file and search by X.X.X to find closest match
      if (matchCovered == false) {
        string tempI = i;
        i = "";
        int iCount = 0;
        for (unsigned int k=0; iCount < 3; k++) {
          if (tempI[k] == '.') iCount++;
          if (iCount < 3) i+=tempI[k];
        }
      }

      // reset go file to beginning
      goFile.clear();
      goFile.seekg(0, ios::beg);
    }
  } 

  // Print sorted types to output file
  for (auto i : vecOfTypes)
    foutType << i << "\n";

  // Print sorted gos to output file
  for (auto i : vecOfGos)
    fout << i << "\n";

  return 0;
}
