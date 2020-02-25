#include <iostream>
#include <fstream>

using namespace std;

class Node {
public:

  Node(int i = 0) {
    info = i;
    leftSon = rightSon = nullptr;
  } // constructor

  ~Node() {
    if (leftSon) {
      delete leftSon;
      leftSon = nullptr;
    }
    if (rightSon) {
      delete rightSon;
      leftSon = nullptr;
    }
    cerr << "Deleted the value " << info << ' ' << "in destructor\n";
  } // destructor

  int info;
  Node *leftSon, *rightSon;
};

class ABC {
public:

  ABC() {
    root = nullptr;
  } // constructor
  
  ~ABC() {
    delete root;
    root = nullptr;
  }

  void operator + (int value) {
    m_insert(value, root);
  }

  ABC& operator >> (int value) {
    m_insert(value, root);
    return *this;
  }

  void operator - (int value) {
    m_findForErase(value, root);
  }

  void erase(int value) {
    m_findForErase(value, root);
  }

  int getDepth() {
    return m_getDepth(root);
  }

  void printLeaves(ostream &out) {
    out << "Leaves of the tree are: ";
    m_printLeaves(root, out);
    out << "\n\n";
  }

private:

  Node *root;

  void m_insert(int value, Node *&currentNode) {

    if (not currentNode) {
      currentNode = new Node(value);
      cerr << "Inserted the value " << value << '\n';
      return;
    }

    if (value <= currentNode -> info) {
      m_insert(value, currentNode -> leftSon);
    }
    else {
      m_insert(value, currentNode -> rightSon);
    }
  }


  void m_inOrderPrint(Node *currentNode, ostream &out) {

    if (not currentNode) {
      return;
    }

    m_inOrderPrint(currentNode -> leftSon, out);
    out << currentNode -> info << ' ';
    m_inOrderPrint(currentNode -> rightSon, out);
  }

  void m_preOrderPrint(Node *currentNode, ostream &out) {

    if (not currentNode) {
      return;
    }

    out << currentNode -> info << ' ';
    m_preOrderPrint(currentNode -> leftSon, out);
    m_preOrderPrint(currentNode -> rightSon, out);
  }

  void m_postOrderPrint(Node *currentNode, ostream &out) {

    if (not currentNode) {
      return;
    }

    m_postOrderPrint(currentNode -> leftSon, out);
    m_postOrderPrint(currentNode -> rightSon, out);
    out << currentNode -> info << ' ';
  }

  void m_findForErase(int value, Node *&currentNode) {

    if (not currentNode) {
      return;
    }

    if (value < currentNode -> info) {
      m_findForErase(value, currentNode -> leftSon);
      return;
    }
    if (value > currentNode -> info) {
      m_findForErase(value, currentNode -> rightSon);
      return;
    }

    cerr << "Planning to delete " << currentNode -> info << '\n';
    m_erase(currentNode);
  }

  void m_erase(Node *&currentNode) {

    if (not currentNode -> rightSon) {
      auto aux = currentNode -> leftSon;
      currentNode -> leftSon = nullptr;
      delete currentNode;
      currentNode = aux;
      return;
    }

    Node *& nextNode = currentNode -> rightSon;
    while (nextNode -> leftSon) {
      nextNode = nextNode -> leftSon;
    }

    swap(currentNode -> info, nextNode -> info);
    auto aux = nextNode -> rightSon;
    nextNode -> rightSon = nullptr;
    delete nextNode;
    nextNode = aux;
  }

  int m_getDepth(Node *curNode) {
    if (not curNode) return -1;
    return max(m_getDepth(curNode -> leftSon), m_getDepth(curNode -> rightSon)) + 1;
  }

  void m_printLeaves(Node *curNode, ostream &out) {

    if (not curNode) return;

    if (curNode -> leftSon == curNode -> rightSon and curNode -> rightSon == nullptr) {
      out << curNode -> info << ' ';
      return;
    }

    m_printLeaves(curNode -> leftSon, out);
    m_printLeaves(curNode -> rightSon, out);
  }

  friend ostream& operator << (ostream &os, ABC &abc);
};

ostream& operator << (ostream &os, ABC &abc) {
  os << "\nIn order print:\n";
  abc.m_inOrderPrint(abc.root, os);
  os << "\n\nPreorder print:\n";
  abc.m_preOrderPrint(abc.root, os);
  os << "\n\nPostorder print:\n";
  abc.m_postOrderPrint(abc.root, os);
  os << '\n';
  return os;
}


int main() {

  ABC abc;

  // testing insert;

  /* abc + 5; */
  /* abc + 2; */
  /* abc + 8; */
  /* abc + 10; */
  /* abc + 9; */
  /* abc + 1; */
  /* abc + 3; */
  /* abc + 2; */
  /* abc + 2; */

  // testing overloaded insert

  abc >> 5 >> 2 >> 8 >> 10 >> 9 >> 1 >> 3 >> 2 >> 2;

  // testing print function

  cerr << abc << '\n';

  // testing erase

  /* abc.erase(10); */
  /* cerr << abc << '\n'; */
  /* abc.erase(5); */
  /* cerr << abc << '\n'; */
  /* abc.erase(2); */
  /* cerr << abc << '\n'; */

  // testing erase with overload

  abc - 10;
  cerr << abc << '\n';
  abc - 5;
  cerr << abc << '\n';
  abc - 2;
  cerr << abc << '\n';

  // testing depth function

  cerr << "Depth of the tree is " << abc.getDepth() << "\n\n";

  // test print leaves function

  abc.printLeaves(cerr);
}
