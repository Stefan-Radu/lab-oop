#include <iostream>
#include <fstream>
#include <cassert>

struct Node {

  int info;
  Node *leftSon, *rightSon;

  Node(int i = 0): info(i), leftSon(nullptr), rightSon(nullptr) {}

  ~Node() {
    if (leftSon) {
      delete leftSon;
      leftSon = nullptr;
    }
    if (rightSon) {
      delete rightSon;
      rightSon = nullptr;
    }

    std::cerr << "Deleted the value " << info << ' ' << "in destructor\n";
  }
};

class ABC {
public:

  ABC(): root(nullptr) {}
  
  ~ABC() {
    delete root;
    root = nullptr;
  }

  ABC& operator + (int value) {
    insert(value, root);
    return *this;
  }

  ABC& operator >> (int value) {
    *this + value;
    return *this;
  }

  ABC& operator - (int value) {
    erase(value);
    return *this;
  }

  void erase(int value) {
    erase(value, root);
  }

  int getDepth() {
    return getDepth(root);
  }

  void printLeaves(std::ostream &out) {
    out << "Leaves of the tree are: ";
    printLeaves(root, out);
    out << "\n\n";
  }

private:

  Node *root;

  void insert(int value, Node *&currentNode) {

    if (not currentNode) {
      currentNode = new Node(value);
      std::cerr << "Inserted the value " << value << '\n';
      return;
    }

    if (value <= currentNode -> info) {
      insert(value, currentNode -> leftSon);
    }
    else {
      insert(value, currentNode -> rightSon);
    }
  }


  void inOrderPrint(Node *currentNode, std::ostream &out) const {

    if (not currentNode) {
      return;
    }

    inOrderPrint(currentNode -> leftSon, out);
    out << currentNode -> info << ' ';
    inOrderPrint(currentNode -> rightSon, out);
  }

  void preOrderPrint(Node *currentNode, std::ostream &out) const {

    if (not currentNode) {
      return;
    }

    out << currentNode -> info << ' ';
    preOrderPrint(currentNode -> leftSon, out);
    preOrderPrint(currentNode -> rightSon, out);
  }

  void postOrderPrint(Node *currentNode, std::ostream &out) const {

    if (not currentNode) {
      return;
    }

    postOrderPrint(currentNode -> leftSon, out);
    postOrderPrint(currentNode -> rightSon, out);
    out << currentNode -> info << ' ';
  }

  void erase(int value, Node *&currentNode) {

    if (not currentNode) {
      return;
    }

    if (value < currentNode -> info) {
      erase(value, currentNode -> leftSon);
      return;
    }
    if (value > currentNode -> info) {
      erase(value, currentNode -> rightSon);
      return;
    }

    std::cerr << "Planning to delete " << currentNode -> info << '\n';

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

    std::swap(currentNode -> info, nextNode -> info);
    auto aux = nextNode -> rightSon;
    nextNode -> rightSon = nullptr;
    delete nextNode;
    nextNode = aux;
  }

  int getDepth(Node *curNode) const {
    if (not curNode) return -1;
    return std::max(getDepth(curNode -> leftSon), getDepth(curNode -> rightSon)) + 1;
  }

  void printLeaves(Node *curNode, std::ostream &out) const {

    if (not curNode) return;

    if (curNode -> leftSon == curNode -> rightSon and curNode -> rightSon == nullptr) {
      out << curNode -> info << ' ';
      return;
    }

    printLeaves(curNode -> leftSon, out);
    printLeaves(curNode -> rightSon, out);
  }

  friend std::ostream& operator << (std::ostream &os, ABC &abc);
};

std::ostream& operator << (std::ostream &os, ABC &abc) {
  os << "\nIn order print:\n";
  abc.inOrderPrint(abc.root, os);
  os << "\n\nPreorder print:\n";
  abc.preOrderPrint(abc.root, os);
  os << "\n\nPostorder print:\n";
  abc.postOrderPrint(abc.root, os);
  os << '\n';
  return os;
}

void insertTest(ABC &abc) {

  abc + 5 + 2;
  assert(abc.getDepth() == 1);
  abc + 8 + 10 + 9;
  assert(abc.getDepth() == 3);
  abc + 1 + 3 + 2;
  assert(abc.getDepth() == 3);
  abc + 2 + 14;
  assert(abc.getDepth() == 4);

  std::cerr << abc << '\n';
  std::cerr << "Depth of the tree is " << abc.getDepth() << "\n\n";
  abc.printLeaves(std::cerr);
}

void eraseTest(ABC &abc) {

  abc - 2;
  assert(abc.getDepth() == 4);
  abc - 10 - 5 - 2;
  assert(abc.getDepth() == 3);
  abc - 3 - 14 - 8;
  assert(abc.getDepth() == 2);

  std::cerr << abc << '\n';
  std::cerr << "Depth of the tree is " << abc.getDepth() << "\n\n";
  abc.printLeaves(std::cerr);
}

void runTests(ABC &abc) {
  insertTest(abc);
  eraseTest(abc);
}

int main() {
  ABC abc;
  runTests(abc);
}
