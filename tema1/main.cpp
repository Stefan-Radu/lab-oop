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
    /* if (leftSon) delete leftSon; */
    /* if (rightSon) delete rightSon; */
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
    m_recursiveErase(root);
  }

  void operator + (int value) {
    m_insert(value, root);
  }

  ABC* operator >> (int value) {
    m_insert(value, root);
    return this;
  }

  ofstream& operator << (ofstream &out) {
    out << "In order print:\n";
    m_inOrderPrint(root, out);
    out << "Preorder print:\n";
    m_preOrderPrint(root, out);
    out << "Postorder print:\n";
    m_postOrderPrint(root, out);
    return out;
  }

  bool erase(int value) {

    Node *node = find(value, root);
    if (not node) return false;

    Node *nextNode;
    while (node -> rightSon) {

      nextNode = node -> rightSon;
      while (nextNode -> leftSon) {
        nextNode = nextNode -> leftSon;
      }

      swap(node -> info, nextNode -> info);
      node = nextNode;
    }

    delete node;
    return true;
  }

  int getDepth() {
    return m_getDepth(root);
  }

  void printLeaves(ofstream &out) {
    m_printLeaves(root, out);
  }

private:

  Node *root;

  void m_recursiveErase(Node *currentNode) {
    if (not currentNode) return;

    m_recursiveErase(currentNode -> leftSon);
    m_recursiveErase(currentNode -> rightSon);

    delete currentNode;
  }

  void m_insert(int value, Node *currentNode) {

    if (not currentNode) {
      currentNode = new Node(value);
      return;
    }

    if (value <= currentNode -> info) {
      m_insert(value, currentNode -> leftSon);
    }
    else {
      m_insert(value, currentNode -> rightSon);
    }
  }


  void m_inOrderPrint(Node *currentNode, ofstream &out) {

    if (not currentNode) {
      return;
    }

    m_inOrderPrint(currentNode -> leftSon, out);
    out << currentNode -> info << ' ';
    m_inOrderPrint(currentNode -> rightSon, out);
  }

  void m_preOrderPrint(Node *currentNode, ofstream &out) {

    if (not currentNode) {
      return;
    }

    out << currentNode -> info << ' ';
    m_preOrderPrint(currentNode -> leftSon, out);
    m_preOrderPrint(currentNode -> rightSon, out);
  }

  void m_postOrderPrint(Node *currentNode, ofstream &out) {

    if (not currentNode) {
      return;
    }

    m_postOrderPrint(currentNode -> leftSon, out);
    m_postOrderPrint(currentNode -> rightSon, out);
    out << currentNode -> info << ' ';
  }

  Node *find(int value, Node *currentNode) {

    if (not currentNode) {
      return nullptr;
    }

    if (value < currentNode -> info) {
      return find(value, currentNode -> leftSon);
    }
    if (value > currentNode -> info) {
      return find(value, currentNode -> rightSon);
    }

    return currentNode;
  }

  int m_getDepth(Node *curNode) {

    if (not curNode) {
      return 0;
    }

    return max(m_getDepth(curNode -> leftSon), m_getDepth(curNode -> rightSon)) + 1;
  }

  void m_printLeaves(Node *curNode, ofstream &out) {

    if (curNode -> rightSon == curNode -> rightSon and curNode -> rightSon == nullptr) {
      out << curNode -> info << ' ';
      return;
    }

    m_printLeaves(curNode -> leftSon, out);
    m_printLeaves(curNode -> rightSon, out);
  }
};

int main() {

}
