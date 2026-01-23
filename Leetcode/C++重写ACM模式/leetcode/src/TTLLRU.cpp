// 带ttl的lru
// 首先先写出简单的lru lru是双向链表和哈希表
// 在此基础上新增两个变量time 和 ttl 和 两个辅助 gettime 和 isvalid 辅助函数

#include <iostream>
#include <unordered_map>
#include <chrono>
using namespace std;

struct Node {
    int key;
    int value;
    Node* next;
    Node* pre;
    long long time; //记录当前节点的创建时间
    Node(): key(0), value(0), next(nullptr), pre(nullptr) {};
    Node(int _key, int _value): key(_key), value(_value), time(GetTime()), next(nullptr), pre(nullptr) {};

    static long long GetTime() {
        return chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
    }
};

class LRU {
private:
    // 虚拟头尾节点 容量 哈希表
    Node* head;
    Node* tail;
    int cap;
    int len;
    int ttl; //设置最大过期时间
    unordered_map<int, Node*> umap; //key - node
public:
    //get(int key) 查询一个键 这个键存在返回value，而且也要判断这个键是否过期了，过期了返回-1 不存在返回-1 同时要移到最前面
    //void set(int key, int value) 设置一个键 设置的时候首先判断是否过期了，过期了就丢弃，不然的话这个键设置为v 不存在就插入 同时判断容量是否超出了
    LRU(int _cap, int _ttl) : cap(_cap), len(0), ttl(_ttl) {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->pre = head;
    }
    ~LRU() {
        Node* cur = head;
        while(cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }
    void DeleteNode(Node* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    void InsertHead(Node* node) {
        node->next = head->next;
        head->next->pre = node;
        head->next = node;
        node->pre = head;
    }
    bool IsVaild(Node* node) {
        //新增判断当前节点时间是否合法的函数
        long long now = Node::GetTime(); // 获取当前时间
        long long gap = now - node->time;
        if(gap > ttl) return false;
        else return true;
    }
    int get(int key) {
        // 1.没有找到
        if(umap.find(key) == umap.end()) {
            return -1;
        }
        // 2.找了但是过期了
        auto it = umap.find(key); //返回node
        if(IsVaild(it->second) == false) {
            DeleteNode(it->second);
            umap.erase(it->second->key);
            len--;
            return -1;
        } else {
            //3.找到了没有过期
            DeleteNode(it->second);
            InsertHead(it->second);
            return it->second->value;
        }
    }
    void set(int key, int value) {
        if(umap.find(key) == umap.end()) {
            // 1.没有找到直接插入
            Node* node = new Node(key, value);
            InsertHead(node);
            len++;
            umap[key] = node;
            // 判断是否超出了容量
            if(len > cap) {
                umap.erase(tail->pre->key);
                DeleteNode(tail->pre);
                len--;
            }
        } else {
            // 2.找到了但是过期了
            auto it = umap.find(key);
            if(IsVaild(it->second) == false) {
                DeleteNode(it->second);
                umap.erase(it->second->key);
                len--;

                //之后还需要插入新的key-value
                Node* node = new Node(key, value);
                InsertHead(node);
                umap[key] = node;
                len++;
            } else {
                // 3.找到了没有过期了
                it->second->value = value;
                it->second->time = Node::GetTime(); //记得更新时间
                DeleteNode(it->second);
                InsertHead(it->second);
            }
        }
    } 
};