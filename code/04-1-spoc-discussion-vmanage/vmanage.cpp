#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <string>

using namespace std;
//Big Endian

const string kMemFileName = "memory.txt";
const string kDiskFileName = "disk.txt";
const string kInFileName = "in.txt";
const string kOutFileName = "out.txt";

const int kByte = 8;
const int kRMemSize = 4 * 1024;
const int kVMemSize = 8 * 1024;
const int kDiskSize = 4 * 1024;
const int kPageSize = 32;
const int kPDBR = 0xd80;
const int kPDEEntrySize = 1;
const int kPDENum = 32;
const int kPTEEntrySize = 1;
const int kPTENum = 32;

unsigned char* memory = NULL;
unsigned char* disk = NULL;
unsigned int* PDE = NULL;
unsigned int** PTEList = NULL;

unsigned int* vAddress = NULL;

bool _EntryValid(unsigned int entry, int size)
{
  return ((entry >> (size * kByte - 1)) != 0);
}

bool EntryValid(unsigned int entry)
{
  return _EntryValid(entry, 1);
}

unsigned int _EntryContent(unsigned int entry, int size)
{
  unsigned int mask = ~(1 << (size * kByte - 1));
  return entry & mask;
}

unsigned int EntryContent(unsigned int entry)
{
  return _EntryContent(entry, 1);
}

int PowerOf2(int num)
{
  int cnt = 0;
  while (num > 1)
  {
    cnt++;
    num /= 2;
  }
  return cnt;
}

unsigned int GetOffset(unsigned int addr)
{
  unsigned int mask = kPageSize-1;
  return mask & addr;
}

unsigned int GetPTEIndex(unsigned int addr)
{
  int offset = PowerOf2(kPageSize);
  unsigned int mask = (kPTENum-1) << offset;
  return (mask & addr) >> offset;
}

unsigned int GetPDEIndex(unsigned int addr)
{
  int offset = PowerOf2(kPageSize)+PowerOf2(kPTENum);
  unsigned int mask = (kPDENum-1) << offset;
  return (mask & addr) >> offset;
}

void PrintMem()
{
  if (memory == NULL)
    return;
  for (int i = 0; i < kRMemSize; i++)
  {
    if (i % 32 == 0)
      printf("\n");
    printf("%02x ", memory[i]);
  }
}

void PrintPDE()
{
  for (int i = 0; i < kPDENum; i++)
  {
    if (i % 8 == 0)
      printf("\n");
    printf("(%d, %02x) ", EntryValid(PDE[i]), EntryContent(PDE[i]));
  }  
}

void PrintPTE()
{
  for (int i = 0; i < kPDENum; i++)
  {
    printf("\nPTE %d:", i);
    if (PTEList[i] == NULL)
      printf("NULL\n");
    else
    {
      for (int j = 0; j < kPTENum; j++)
      {
        if (j % 8 == 0)
          printf("\n");
        printf("(%d, %02x) ", EntryValid(PTEList[i][j]), EntryContent(PTEList[i][j]));
      }
    }
  }
}

void init()
{
  ifstream memoryFile(kMemFileName.c_str());
  memory = new unsigned char[kRMemSize];
  unsigned int addr = 0;
  int num;
  while ((addr < kRMemSize) && (memoryFile >> hex >> num))
    memory[addr++] = (unsigned char)num;
  for (int i = addr; i < kRMemSize; i++)
    memory[i] = 0;
  memoryFile.close();

  ifstream diskFile(kDiskFileName.c_str());
  disk = new unsigned char[kDiskSize];
  addr = 0;
  while ((addr < kDiskSize) && (diskFile >> hex >> num))
    disk[addr++] = (unsigned char)num;
  for (int i = addr; i < kDiskSize; i++)
    disk[i] = 0;
  diskFile.close();

  PDE = new unsigned int[kPDENum];
  for (int index = 0; index < kPDENum; index++)
  {
    addr = kPDBR + kPDEEntrySize * index;
    unsigned int temp = 0;
    for (int i = 0; i < kPDEEntrySize; i++)
      temp += memory[addr+i] << (i*kByte);
    PDE[index] = temp;
  }

  PTEList = new unsigned int*[kPDENum];
  for (int i = 0; i < kPDENum; i++)
  {
    if (!EntryValid(PDE[i]))
    {
      PTEList[i] = NULL;
    }
    else
    {
      PTEList[i] = new unsigned int[kPTENum];
      for (int j = 0; j < kPTENum; j++)
      {
        addr = EntryContent(PDE[i]) * kPageSize + kPTEEntrySize * j;
        unsigned int temp = 0;
        for (int k = 0; k < kPTEEntrySize; k++)
          temp += memory[addr+k] << (k*kByte);
        PTEList[i][j] = temp;
      }
    }
  }
  //PrintMem();
  //PrintPDE();
  //PrintPTE();
}

void FindValue(unsigned int vaddr, ofstream& out)
{
  unsigned int offset = GetOffset(vaddr);
  unsigned int PTEIndex = GetPTEIndex(vaddr);
  unsigned int PDEIndex = GetPDEIndex(vaddr);
  out << "Virtual Address 0x" << setfill('0') << setw(4) << hex << vaddr << endl;
  bool PDEValid = EntryValid(PDE[PDEIndex]);
  unsigned int PDEContent = EntryContent(PDE[PDEIndex]);
  out << "  --> pde index:0x" << setfill('0') << setw(2) << hex << PDEIndex << " pde contents:(valid " 
    << dec << PDEValid << ", pt 0x" << setfill('0') << setw(2) << hex << PDEContent << ")" << endl;
  if (!PDEValid)
  {
    out << "    --> Fault (page directory entry not valid)" << endl;
  }
  else
  {
    bool PTEValid = EntryValid(PTEList[PDEIndex][PTEIndex]);
    unsigned int PTEContent = EntryContent(PTEList[PDEIndex][PTEIndex]);
    out << "      --> pte index:0x" << setfill('0') << setw(2) << hex << PTEIndex << "  pte contents:(valid "
      << dec << PTEValid << ", pfn 0x" << setfill('0') << setw(2) << hex << PTEContent << ")" << endl;
    if (!PTEValid)
    {
      unsigned int diskAddr = PTEContent * kPageSize + offset;
      out << "      --> Translates to Disk Sector Address 0x" << setfill('0') << setw(3) << hex << diskAddr;
      out << " --> Value:0x" << setfill('0') << setw(2) << hex << (unsigned int)disk[diskAddr] << endl;
    }
    else
    {
      unsigned int raddr = PTEContent * kPageSize + offset;
      out << "      --> Translates to Physical Address 0x" << setfill('0') << setw(3) << hex << raddr;
      out << " --> Value:0x" << setfill('0') << setw(2) << hex << (unsigned int)memory[raddr] << endl;
    }
  } 
}

int main()
{
  init();
  ifstream in(kInFileName.c_str());
  ofstream out(kOutFileName.c_str());
  unsigned int vaddr;
  while (in >> hex >> vaddr)
    FindValue(vaddr, out);
  in.close();
  out.close();
  return 0;
}
