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

  // array of EC
  string s;
  vector<string> ec;
  while (fin >> s)
    ec.push_back(s);

  unordered_map<string, vector<string>> ec2go;

  // for every ec, match it to possible go terms
  // search document for term
  for (string i : ec) {
    char c;
    string goTerm;
    vector<string> vecOfGos;
    vecOfGos.clear();
    while (goFile >> c) {
      goTerm = "";
      if (c == i[0]) {
        goTerm+=c;
        bool match = true;
        for (unsigned int j=1; j<i.size(); j++) {
          goFile >> c;
          if (c != s[j]) {
            match = false;
            break;
          }
          goTerm+=c;
        }
        if (match == true) 
          vecOfGos.push_back(goTerm);
      }
    }    
    // Add vector list of go terms to corresponding ec
    ec2go[i] = vecOfGos;

    // reset go file to beginning
    goFile.clear();
    goFile.seekg(0, ios::beg);
  } 

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
