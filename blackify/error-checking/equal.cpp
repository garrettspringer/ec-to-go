#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
  ifstream all("all.txt");
  ifstream sorted("sorted-ec.txt");

  vector<string> smolList;

  string s;
  while (sorted >> s)
    smolList.push_back(s);

  while (all >> s) {
    bool found = false;
    
    for (auto i : smolList) 
      if (i == s) {
        found = true;
        break;
     }

    if (found == false)
      cout << "Fuck, I didn't find " << s << "\n";
  }

  return 0;
}
