#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    string key;
    int value;

    Node(string key, int val)
    {
        this->key = key;
        value = val;
    }
};

class LRUCache
{
public:
    int maxSize;
    list<Node> l;
    unordered_map<string, list<Node>::iterator> m;

    LRUCache(int maxSize)
    {
        this->maxSize = maxSize > 1 ? maxSize : 1;
    }

    void insertKeyValue(string key, int value)
    {
        // Case 1 : present already in Cache

        if (m.count(key) != 0)
        {
            auto it = m[key];
            it->value = value;
        }
        else
        {
            // Case 2 : needed to be inserted

            // check first if cache is full then remove the last element first
            if (l.size() == maxSize)
            {
                Node last = l.back();
                m.erase(last.key);
                l.pop_back();
            }

            // Now lets go ahead with insertion operation
            Node n(key, value);
            l.push_front(n);
            m[key] = l.begin();
        }
    }

    int *getValue(string key)
    {
        if (m.count(key) != 0)
        {
            auto it = m[key];
            l.push_front(*it);
            l.erase(it);
            m[key] = l.begin();
            return &l.begin()->value;
        }

        return NULL;
    }

    string mostRecentKey()
    {
        return l.front().key;
    }
};
int main()
{
    cout << "Abhay K Goyal" << endl;

    LRUCache lru(3);
    lru.insertKeyValue("mango", 10);
    lru.insertKeyValue("orange", 20);
    lru.insertKeyValue("guava", 30);

    cout << lru.mostRecentKey() << endl;

    lru.insertKeyValue("mango", 40);
    cout << lru.mostRecentKey() << endl;

    int *orders = lru.getValue("mango");
    if(orders != NULL)
        cout << "Order Of Mango " << *orders << endl; 
    lru.insertKeyValue("banana", 40);

    if(lru.getValue("orange") == NULL)
        cout << "orange doesn't exist" << endl;
    
    if(lru.getValue("guava") == NULL)
        cout << "guava doesn't exist" << endl;

    if(lru.getValue("banana") == NULL)
        cout << "banana doesn't exist" << endl;

    if(lru.getValue("mango") == NULL)
        cout << "mango doesn't exist" << endl;


    return 0;
}