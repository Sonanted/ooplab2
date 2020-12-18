#ifndef PREFIXTREE_H
#define PREFIXTREE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

template <class K, class V>
class PrefixTree {
public:
    PrefixTree(); // конструктор по умолчанию
    PrefixTree(const PrefixTree& other); // конструктор копирования
    ~PrefixTree(); // деструктор

    void deleteTree(); // удаление всех значений из коллекции
    int getValueCount() const; // метод, возвращающий число хранящихся в коллекции значений

    void saveTree(string& path) const; // сохранение в файл содержимого коллекции
    void loadTree(string& path); // загрузка из файла содержимого коллекции

    bool operator==(const PrefixTree& other) const; // метод, возвращающий 1, если обе коллекции хранят одинаковые пары ключ-значение

    void addChild(const K& key, const V& value); // метод, добавляющий в коллекцию пару ключ-значение
    void deleteChild(const K& key, const V& value); // удаление элемента

    V& operator[](const K& key) const; // оператор [] принимает ключ по ссылке и возвращает значение
    bool isKeyInTree(const K& key) const; // метод, возвращающий 1 при наличии ключа в дереве и 0 при отсутствии
    vector<K> getKeys(const K& key) const; // метод, возвращающий список хранящихся ключей, начинающихся с заданной последовательности

private:
    struct node {
        bool isChain = false; // является ли элементом
        map<K, node*> children;
        void addNode(const K& key) {
            children[key] = new node;
        }
    };
    node* tree; // дерево
    int values; // кол-во значений в коллекции




};

template <class K, class V>
PrefixTree<K, V>::PrefixTree() {
    tree = new node;
    values = 0;
}

template <class K, class V>
PrefixTree<K, V>::PrefixTree(const PrefixTree& other) {

}

template <class K, class V>
PrefixTree<K, V>::~PrefixTree() {
    delete tree;
}

template <class K, class V>
void PrefixTree<K, V>::deleteTree() {

}

template <class K, class V>
int PrefixTree<K, V>::getValueCount() const {
    return values;
}

template <class K, class V>
void PrefixTree<K, V>::saveTree(string& path) const {

}

template <class K, class V>
void PrefixTree<K, V>::loadTree(string& path) {

}

template <class K, class V>
bool PrefixTree<K, V>::operator==(const PrefixTree& other) const {

}

template <class K, class V>
void PrefixTree<K, V>::addChild(const K& key, const V& value) {
//    for (int i = 0; i < key.size(); i++) {
//        K new_key = {key[i]};
//        if (tree->children.count(new_key) == 0 ) {
//            tree->addNode(new_key);
//        }
//    }

//    tree->isChain = true;
//    values++;
}

template <class K, class V>
void PrefixTree<K, V>::deleteChild(const K& key, const V& value) {

}

template <class K, class V>
V& PrefixTree<K, V>::operator[](const K& key) const {

}

template <class K, class V>
bool PrefixTree<K, V>::isKeyInTree(const K& key) const {
//    for (int i = 0; i < key.size(); i++) {
//        K new_key = {key[i]};
//        if (tree->children.count(new_key) == 0) {
//            return 0;
//        }
//    }
//    return 1;
}

template <class K, class V>
vector<K> PrefixTree<K, V>::getKeys(const K& key) const {

}

#endif // PREFIXTREE_H
