#ifndef PREFIXTREE_H
#define PREFIXTREE_H
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
using namespace std;


template<typename K, typename V>
class PrefixTree;

template <class K, class V>
class PrefixTree {
public:
    PrefixTree() = default; // + конструктор по умолчанию
    PrefixTree(const PrefixTree& other); // + конструктор копирования

    void deleteTree(); // удаление всех значений из коллекции
    int getValueCount() const; // + метод, возвращающий число хранящихся в коллекции значений

    void saveTree(const string& path) const; // сохранение в файл содержимого коллекции
    void loadTree(const string& path); // загрузка из файла содержимого коллекции

    bool operator==(const PrefixTree& other) const;
    bool operator!=(const PrefixTree& other) const;

    template<typename Q, typename W> friend ostream& operator<<(ostream& stream, const PrefixTree<K, V>& prefixtree);
    template<typename Q, typename W> friend istream& operator>>(istream& stream, PrefixTree<K, V>& prefixtree);

    void addChild(const K& key, const V& value);
    void deleteChild(const K& key);

    V& operator[](const K& key);
    const V& operator[](const K& key) const;

    bool isKeyInTree(const K& key);
    vector<K> getKeys() const; // + метод, возвращающий список хранящихся ключей, начинающихся с заданной последовательности

    V& get(const K& key); // получить значение по ключу +

private:
    map<char, PrefixTree> children;
    vector<K> keys;
    V value;
    bool isChain = false; // является ли ключом
};

template <class K, class V>
PrefixTree<K, V>::PrefixTree(const PrefixTree& other) {
    this->children = other.children;
    this->value = other.value;
    this->isChain = other.isChain;
}

template <class K, class V>
void PrefixTree<K, V>::deleteTree() {
  children.clear();
}

template <class K, class V>
int PrefixTree<K, V>::getValueCount() const {
  return getKeys().size();
}

template <class K, class V>
void PrefixTree<K, V>::saveTree(const string& path) const {
    ofstream output(path);
    output << *this;
}

template <class K, class V>
void PrefixTree<K, V>::loadTree(const string& path) {
  ifstream input(path);
    if (input) {
        input >> *this;
    }
}

template <class K, class V>
bool PrefixTree<K, V>::operator==(const PrefixTree& other) const {
 return this->children == other.children;
}

template <class K, class V>
bool PrefixTree<K, V>::operator!=(const PrefixTree& other) const {
 return this->children != other.children;
}

template <class K, class V>
void PrefixTree<K, V>::addChild(const K& key, const V& value) {
    if (key.size() > 1) {
        children[key[0]].addChild(key.substr(1), value);
    }
    else if (key.size() == 1) {
        children[key[0]].isChain = true;
        children[key[0]].value = value;
    }
}

template <class K, class V>
void PrefixTree<K, V>::deleteChild(const K& key) {
    if (key.size() > 1) {
        children[key[0]].deleteChild(key.substr(1));
    }
    else if (key.size() == 1)
        children.erase(key[0]);
}

template <class K, class V>
V& PrefixTree<K, V>::operator[](const K& key) {
  return get(key);
}

template <class K, class V>
const V& PrefixTree<K, V>::operator[](const K& key) const {
  return const_cast<PrefixTree&>(*this)[key];
}

template <class K, class V>
bool PrefixTree<K, V>::isKeyInTree(const K& key) {
    if (key.size() > 1) {
        if (children.count(key[0]) != 0)
            return children[key[0]].isKeyInTree(key.substr(1));
        else
            return false;
    }
    else if (key.size() == 1) {
        if ((children.count(key[0]) != 0) && (children[key[0]].isChain))
            return true;
        else
            return false;
    }
    else
      return false;
}

template <class K, class V>
vector<K> PrefixTree<K, V>::getKeys() const {
    vector<K> result{};
    if (children.size() != 0) {
      for (auto it = children.begin(); it != children.end(); ++it) {
          if (it->second.isChain) {
              result.push_back(string(1, it->first));
          }
          auto temp = it->second.getKeys();
          for (auto &item : temp)
              item.insert(0, string(1, it->first));
          result.insert(result.end(), temp.begin(), temp.end());
      }
    }
    return result;
}

template <class K, class V>
V& PrefixTree<K, V>::get(const K& key) {
  V* result;
  if (key.size() > 1) {
      result = &children[key[0]].get(key.substr(1));
  }
  else if (key.size() == 1) {
      result = &children[key[0]].value;
  }
  return *result;
}

template<typename K, typename V>
ostream& operator<<(ostream& stream, const PrefixTree<K, V>& prefixtree) {
    bool k = false;
    for (const auto& key : prefixtree.getKeys() ) {
      if (k == false) {
        stream << key << ' ' << prefixtree[key];
        k = true;
      } else {
        stream << endl << key << ' ' << prefixtree[key];
      }
    }
    return stream;
}

template<typename K, typename V>
istream& operator>>(istream& stream, PrefixTree<K, V>& prefixtree) {
    string input_key, input_value;
    while (stream) {
        stream >> input_key >> input_value;
        prefixtree.addChild(input_key, input_value);
    }
    return stream;
}


#endif // PREFIXTREE_H
