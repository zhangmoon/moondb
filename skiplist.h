#include<string>
#include <stdlib.h>
#include<iostream>

using namespace std;
class SkipNode;
class NodeIndex
{
private:
    /* data */
public:
    SkipNode* node;
    int currentLevel;
    NodeIndex* nextNodeIndex;
    NodeIndex* downNodeIndex;

    NodeIndex(SkipNode* node, int level);
    ~NodeIndex();
};

class SkipNode
{
    public:
        string key;
        string value;
        int nodeLevel;
        NodeIndex* maxNodeIndex;
        SkipNode(string key, string value, int level);
        ~SkipNode();   
};

class SkipList
{
private:
    int randomlevel(int max_level, double ratio);
public:
    int MAX_LEVEL=10;
    SkipNode* head;
    double upratio = 0.5;
    SkipList(/* args */);
    ~SkipList();
    void insert(string key, string value);
    string search(string key);
    void del(string key);
};