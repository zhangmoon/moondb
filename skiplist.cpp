#include"skiplist.h"

SkipNode::SkipNode(string key, string value, int level)
{
    this->key = key;
    this->value = value;
    this->nodeLevel = level ;
    this->maxNodeIndex = NULL;
}
SkipNode::~SkipNode()
{
}



NodeIndex::NodeIndex(SkipNode* node, int level)
{
    this->node = node;
    this->currentLevel = level;
    this->nextNodeIndex = NULL;
    this->downNodeIndex = NULL;
}

NodeIndex::~NodeIndex()
{
}

int SkipList::randomlevel(int max_level, double ratio)
{
        int level = 1;
        for (size_t i = 1; i < max_level; i++)
        {
            if (rand() % 100 <ratio*100)
            {
                level++;
            }
        }
        return level;
}

SkipList::SkipList(/* args */)
{
    this->head = new SkipNode(NULL,NULL,this->MAX_LEVEL);
}

SkipList::~SkipList()
{
}

void SkipList::insert(string key, string value) {
    SkipNode* node = new SkipNode(key, value, randomlevel(this->MAX_LEVEL, this->upratio));
    SkipNode* currentNode = this->head;
    NodeIndex* currentNodeIndex = currentNode->maxNodeIndex;
    NodeIndex **lastNodes = new NodeIndex*[node->nodeLevel]();
    NodeIndex **nextNodes = new NodeIndex*[node->nodeLevel]();

    while (currentNodeIndex != NULL)
    {
        if (currentNodeIndex->nextNodeIndex != NULL)
        {
            int compare_flag = currentNodeIndex->nextNodeIndex->node->key.compare(key);
            if (compare_flag >0)
            {
                currentNodeIndex = currentNodeIndex->nextNodeIndex;
                currentNode = currentNodeIndex->node;
            } else if (compare_flag <0)
            {
                if (currentNodeIndex->currentLevel <= node->nodeLevel)
                {
                    lastNodes[currentNodeIndex->currentLevel-1] = currentNodeIndex;
                    nextNodes[currentNodeIndex->currentLevel-1] = currentNodeIndex->nextNodeIndex;
                }
                currentNodeIndex = currentNodeIndex->downNodeIndex;
            } else {
                cout << "node:" << key << " already exists "<<endl;
                return;
            }   
        } else {
            if (currentNodeIndex->currentLevel <= node->nodeLevel)
            {
                lastNodes[currentNodeIndex->currentLevel-1] = currentNodeIndex;
                nextNodes[currentNodeIndex->currentLevel-1] = NULL;
            }
            currentNodeIndex = currentNodeIndex->downNodeIndex;
        }
        /* code */
    }
    NodeIndex* head =  new NodeIndex(node, node->nodeLevel);
    node->maxNodeIndex = head;
    head->nextNodeIndex = nextNodes[node->nodeLevel-1];
    lastNodes[node->nodeLevel-1]->nextNodeIndex = head;
    NodeIndex* last = head;
    for (size_t i = node->nodeLevel-1; i >= 1; i--)
    {
        NodeIndex* current = new NodeIndex(node, i);
        last->downNodeIndex = current;
        current->nextNodeIndex = nextNodes[i-1];
        lastNodes[i-1]->nextNodeIndex = current;
        last = current;
    }
    return;
}

string SkipList::search(string key) {

    NodeIndex* currentIndex  = this->head->maxNodeIndex;
    while (currentIndex != NULL)
    {
        if (currentIndex->nextNodeIndex != NULL)
        {
            int compare_flag = currentIndex->nextNodeIndex->node->key.compare(key);
            if (compare_flag >0)
            {
                currentIndex = currentIndex->nextNodeIndex;
            } else if (compare_flag <0)
            {
                currentIndex = currentIndex->downNodeIndex;
            } else {
                return currentIndex->nextNodeIndex->node->value;
            }
        } else {
            currentIndex = currentIndex->downNodeIndex;
        } 
    }
    return NULL;
}

void SkipList::del(string key) {
    NodeIndex* currentIndex  = this->head->maxNodeIndex;
    NodeIndex* lastIndex = NULL;
    NodeIndex* toDeleteIndex = NULL;
    while (currentIndex != NULL)
    {
        if (currentIndex->nextNodeIndex != NULL)
        {
            int compare_flag = currentIndex->nextNodeIndex->node->key.compare(key);
            if (compare_flag >0)
            {
                currentIndex = currentIndex->nextNodeIndex;
            } else if (compare_flag <0)
            {
                currentIndex = currentIndex->downNodeIndex;
            } else {
                lastIndex = currentIndex;
                toDeleteIndex = currentIndex->nextNodeIndex;
                break;
            }
        } else {
            currentIndex = currentIndex->downNodeIndex;
        } 
    }

    if (toDeleteIndex != NULL)
    {
        NodeIndex **lastNodes = new NodeIndex*[toDeleteIndex->currentLevel]();
        NodeIndex* cindex = lastIndex;
        for (int i = toDeleteIndex->currentLevel; i >= 1 ; i--)
        {

            NodeIndex* cindex2 = cindex;
            while (cindex2->nextNodeIndex->node != toDeleteIndex->node)
            { 
                cindex2 = cindex2->nextNodeIndex;
            }
            NodeIndex* tmp = cindex2->nextNodeIndex;
            cindex2->nextNodeIndex = cindex2->nextNodeIndex->nextNodeIndex;
            delete tmp;
            lastNodes[i] = cindex2;
            cindex = cindex->downNodeIndex; 
        }
        delete toDeleteIndex;
    }
}