
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>

using namespace std;

const int kOffsetWidth = 12;
const int kPTEWidth = 10;
const int kPDEWidth = 10;

const int kPageSize = 4 * 1024;

int main()
{
  ifstream in("in.txt");
  ofstream out("out.txt");
  unsigned int vaddr, paddr;
  unsigned int pdeIndex, pdeContext, pteIndex, pteContext;
  unsigned int mask;
  while (in >> hex >> vaddr)
  {
    in >> hex >> paddr;
    pdeIndex = vaddr >> (kOffsetWidth + kPTEWidth);
    pdeContext = pdeIndex - 0x300 + 1;
    mask = 1023u << kOffsetWidth;
    pteIndex = (vaddr & mask) >> kOffsetWidth;
    pteContext = paddr >> kOffsetWidth;
    out << "va 0x" << setfill('0') << setw(8) << hex << vaddr;
    out << ", pa 0x" << setfill('0') << setw(8) << hex << paddr;
    out << ", pde_idx 0x" << setfill('0') << setw(8) << hex << pdeIndex;
    out << ", pde_ctx 0x" << setfill('0') << setw(8) << hex << pdeContext;
    out << ", pte_idx 0x" << setfill('0') << setw(8) << hex << pteIndex;
    out << ", pte_ctx 0x" << setfill('0') << setw(8) << hex << pteContext;
    out << endl;
  }
  in.close();
  out.close();
  return 0;
}
