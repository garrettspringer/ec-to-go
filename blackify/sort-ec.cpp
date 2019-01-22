// Sorts the enzyme commission numbers in increasing order
#include<iostream>
#include<unordered_map>
#include<fstream>
#include<algorithm>
#include<stdlib.h>
#include<vector>
using namespace std;

// reads in the numbers
/*void num_converter(const string a, const string b, int &a1, int &a2, int &a3, int &a4, int &b1, int &b2, int &b3, int &b4)
{
  for (unsigned int i=0; i<a; i++) {
    
  }

}*/

bool operator<(const string a, const string b)
{
  int a1, a2, a3, a4, b1, b2, b3, b4;
  a1 = int(a[0]);
  a2 = int(a[2]);
  a3 = int(a[4]);
  b1 = int(b[0]);
  b2 = int(b[2]);
  b3 = int(b[4]);

  if (a[6] != 'n') a4 = int(a[6]);
  else a4 = int(a[7]);

  if (b[6] != 'n') b4 = int(b[6]);
  else b4 = int(b[7]);

  if (a1 < b1) return true;
  else if (a2 < b2) return true;
  else if (a3 < b3) return true;
  else if (a4 < b4) return true;
  else return false;
}

int main()
{
  ifstream fin("all.txt");
  ofstream fout("sorted-ec.txt");

  vector<string> ec;

  // read input
  string s;
  while (fin >> s)
    ec.push_back(s);

  sort(ec.begin(), ec.end());

  // remove repeats
  for (unsigned int i=1; i<ec.size(); i++)
    if (ec[i-1] == ec[i])
      ec[i-1] = "";

  // Print to file
  for (auto i : ec)
    if (i != "") fout << i << "\n";
 
  return 0;
}
