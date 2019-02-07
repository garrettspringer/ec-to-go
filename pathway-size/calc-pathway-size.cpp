#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
  ifstream fin("pathways.txt");

  string s, query;
  do {
    query = "";
    cout << "What map would you like to search?" << endl;
    cin >> query;
    unsigned int pathwaySize = 0;

    // read until specified pathway
    while (fin >> s) 
      if (query == s) 
        pathwaySize++;

    // reset file pointer
    fin.clear();
    fin.seekg(0);

    cout << pathwaySize << "\n";
  } while (query != "quit");
 
  return 0;
}
