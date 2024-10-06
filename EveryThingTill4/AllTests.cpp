#include "BinaryNodeTest.h"
#include "SetTest.h"

int main() {
  BinaryNodeTest::testHeight();
  BinaryNodeTest::testPrint();
  BinaryNodeTest::testSubtreeIter();
  BinaryNodeTest::testSubtreeFirst();
  BinaryNodeTest::testSubtreeLast();
  BinaryNodeTest::testSuccessor();
  BinaryNodeTest::testPredecessor();
  BinaryNodeTest::testSubtreeInsertBefore();
  BinaryNodeTest::testSubtreeInsertAfter();
  BinaryNodeTest::testSubtreeDelete();

  SetTest::testFind();

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
