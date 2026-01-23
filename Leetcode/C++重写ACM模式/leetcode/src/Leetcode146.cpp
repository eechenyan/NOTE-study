// 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
// 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

// 双向链表 + 哈希 哈希用来实现o1 查询
// 每次put和get的时候 需要把这个元素放在第一位

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node {
    int key;
    int value;
    Node* next;
    Node* pre;
    Node() : key(0), value(0), next(nullptr), pre(nullptr) {};
    Node(int _key, int _value) : key(_key), value(_value), next(nullptr), pre(nullptr) {};
};

class LRUCache {
private:
    int capacity;
    int size;
    Node* head;
    Node* tail;
    unordered_map<int, Node*> umap;
public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        // Node* head = new Node();
        // Node* tail = new Node();
        // 千万不能创一个局部变量 而是需要全局变量申请内存 !!!
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->pre = head;
    };
    void DeleteNode(Node* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    void InsertHead(Node* node) {
        node->next = head->next;
        head->next->pre = node;
        node->pre = head;
        head->next = node;
    }
    int get(int key){ //如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
        if(umap.find(key) == umap.end()) return -1; //没有找到返回-1
        Node* node = umap[key];
        DeleteNode(node);
        InsertHead(node);
        return node->value;
    }  
    void put(int key, int value) { //如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
        if(umap.find(key) != umap.end()) {
            // 找到了
            Node* node = umap[key];
            node->value = value;
            DeleteNode(node);
            InsertHead(node);
        } else {
            // 没有找到
            // 1.先插入
            Node* node = new Node(key, value);
            InsertHead(node);
            size++;
            umap[key] = node;
            // 判断是否找过了容量
            if(size > capacity) {
                Node* node = tail->pre;
                umap.erase(node->key);
                DeleteNode(node);
                size--;
                delete node;
                // 下面两行展示了典型的使用野指针的错误 ,应该是把node置空,而不是去访问已经释放的指针里面的东西
                // node->next = nullptr;
                // node->pre = nullptr;
                node = nullptr;
            }
        }
    }
};