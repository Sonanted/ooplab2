#include <QApplication>

#include "prefixtree.h"
#include "mainwindow.h"
#include <assert.h>

using namespace std;

void test1() {
  PrefixTree<string, string> test;
  assert(test.getValueCount() == 0);
  cout << "test1 passed\n";
}

void test2() {
  PrefixTree<string, string> test;
  test.addChild("abc","d");
  assert(test.getValueCount() == 1);
  test.addChild("abc","d");
  assert(test.getValueCount() == 1);
  cout << "test2 passed\n";
}

void test3() {
  PrefixTree<string, string> test;
  test.addChild("abc","d");
  assert(test.isKeyInTree("abc") == 1);
  assert(test.isKeyInTree("ab") == 0);
  assert(test.isKeyInTree("a") == 0);
  cout << "test3 passed\n";
}

void test4() {
  PrefixTree<string, string> test;
  test.addChild("abc","d");
  assert(test["abc"] == "d");
  cout << "test4 passed\n";
}

void test5() {
  PrefixTree<string, string> test;
  test.addChild("a","a");
  test.addChild("b","b");
  test.addChild("c","c");
  assert(test.getValueCount() == 3);
  test.deleteChild("a");
  assert(test.getValueCount() == 2);
  test.deleteChild("d");
  assert(test.getValueCount() == 2);
  cout << "test5 passed\n";
}

void test6() {
  PrefixTree<string, string> test;
  test.addChild("a","a");
  test.addChild("b","b");
  assert(test.isKeyInTree("a") == 1);
  test.deleteChild("a");
  assert(test.isKeyInTree("a") == 0);
  cout << "test6 passed\n";
}

void test7() {
  PrefixTree<string, string> test1, test2;
  test1.addChild("a","a");
  test1.addChild("b","b");
  test1.addChild("c","c");
  test1.deleteTree();
  assert(test1 == test2);
  cout << "test7 passed\n";
}

void test8() {
  PrefixTree<string, string> test;
  test.addChild("abc", "d");
  PrefixTree<string, string> copy(test);
  assert(test == copy);
  copy.deleteChild("abc");
  assert(test != copy);
  cout << "test8 passed\n";
}

void test9() {
  PrefixTree<string, string> test1, test2;
  test1.addChild("abc","d");
  test1.addChild("ab","f");
  test1.addChild("a","g");
  test1.saveTree("test.txt");
  test2.loadTree("test.txt");
  assert(test1 == test2);
  cout << "test9 passed\n";
}
int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
