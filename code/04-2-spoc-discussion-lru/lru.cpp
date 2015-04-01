#include <iostream>

using namespace std;

class Node
{
public:
  Node* next;
  Node* prev;
  int value;
  Node(int vvalue = 0)
    : value(vvalue), prev(NULL), next(NULL) {}
};

class List
{
public:
  Node* head;
  Node* tail;
  int num;
  List()
  {
    head = new Node();
    tail = new Node();
    head->prev = head;
    head->next = tail;
    tail->prev = head;
    tail->next = tail;
    num = 0;
  }
  ~List()
  {
    delete head;
    delete tail;
  }
  Node* Head()
  {
    if (head->next == tail)
      return NULL;
    else
      return head->next;
  }
  Node* Tail()
  {
    if (tail->prev == head)
      return NULL;
    else
      return tail->prev;
  }
  Node* Next(Node* node)
  {
    if (node == NULL || node->next == tail)
      return NULL;
    return node->next;
  }
  Node* Prev(Node* node)
  {
    if (node == NULL || node->prev == head)
      return NULL;
    return node->prev;
  }
  void AddAfter(Node* node, Node* after)
  {
    if (node == NULL || after == NULL)
      return;
    node->prev = after;
    node->next = after->next;
    after->next->prev = node;
    after->next = node;
    num++;
  }
  void AddAsHead(Node* node)
  {
    AddAfter(node, head);
  }
  void AddAsTail(Node* node)
  {
    AddAfter(node, tail->prev);
  }
  void DeleteNode(Node* node)
  {
    if (node == NULL)
      return;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
    num--;
  }
  Node* FindNode(int value)
  {
    Node* node = head->next;
    while (node != tail)
    {
      if (node->value == value)
        return node;
      node = node->next;
    }
    return NULL;
  }
};

class LRU
{
public:
  List list;
  const int kPageNum;
  const int kRange;
  int pageFault;
  LRU(int range = 10, int pageNum = 5)
    : kRange(range), kPageNum(pageNum), pageFault(0) {}
  void AccessPage(int value)
  {
    if (value <= 0 || value > kRange)
    {
      cout << "Page No. out of range." << endl;
      return;
    }
    cout << "Access page No." << value << endl;
    Node* node = list.FindNode(value);
    if (node != NULL)
    {
      cout << "Page's already here." << endl;
      list.DeleteNode(node);
      list.AddAsHead(node);
    }
    else
    {
      cout << "Page Fault." << endl;
      pageFault++;
      node = new Node(value);
      if (list.num >= kPageNum)
      {
        Node* tail = list.Tail();
        if (tail != NULL)
          list.DeleteNode(tail);
      }
        list.AddAsHead(node);
    }
  }
  void PrintCurrentPage()
  {
    cout << "Current Pages:" << endl;
    Node* node = list.Head();
    while (node != NULL)
    {
      cout << node->value << ' ';
      node = list.Next(node);
    }
    cout << endl;
  }
};

int main()
{
  LRU lru(5, 4);
  lru.AccessPage(3);
  lru.AccessPage(1);
  lru.AccessPage(4);
  lru.AccessPage(2);
  lru.PrintCurrentPage();
  lru.AccessPage(5);
  lru.PrintCurrentPage();
  lru.AccessPage(2);
  lru.AccessPage(1);
  lru.AccessPage(2);
  lru.PrintCurrentPage();
  lru.AccessPage(3);
  lru.AccessPage(4);
  lru.PrintCurrentPage();
  return 0;
}
