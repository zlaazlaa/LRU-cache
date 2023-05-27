#include<unordered_map>
#include "iostream"
using namespace std;

class LRUCache {
public:
    explicit LRUCache(int capacity) {
        this->capacity = capacity;
        this->size = 0;
        head = new Node();
        tail = new Node();
        head->head = nullptr;
        head->tail = tail;
        tail->head = head;
        tail->tail = nullptr;
    }

    class Node {
    public:
        int key;
        int value;
        Node *tail;
        Node *head;
    };

    int get(int key) {
        if (hash_table.find(key) != hash_table.end()) {
            move_to_top(hash_table[key]);
            return hash_table[key]->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (hash_table.find(key) != hash_table.end()) {
            hash_table[key]->value = value;
            move_to_top(hash_table[key]);
        } else {
            if (size == capacity) {
                hash_table.erase(tail->head->key);
                remove(tail->head);
            }
            Node *new_node = new Node();
            new_node->key = key;
            new_node->value = value;
            insert_to_top(new_node);
            hash_table[key] = new_node;
        }
    }

private:
    unordered_map<int, Node *> hash_table;
    Node *head, *tail;
    int capacity;
    int size;

    void insert_to_top(Node *now) {
        now->head = head;
        now->tail = head->tail;
        head->tail->head = now;
        head->tail = now;
        size++;
    }

    void remove(Node *now) {
        if (now->head != nullptr) now->head->tail = now->tail;
        if (now->tail != nullptr) now->tail->head = now->head;
        delete now;
        size--;
    }

    void move_to_top(Node *now) {
        if (now->head != nullptr) now->head->tail = now->tail;
        if (now->tail != nullptr) now->tail->head = now->head;
        now->head = head;
        now->tail = head->tail;
        head->tail->head = now;
        head->tail = now;
    }
};

int main() {
    LRUCache* lRUCache = new LRUCache(2);
    lRUCache->put(1, 1); // 缓存是 {1=1}
    lRUCache->put(2, 2); // 缓存是 {1=1, 2=2}
    cout << endl << lRUCache->get(1);    // 返回 1
    lRUCache->put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    cout << endl << lRUCache->get(2);    // 返回 -1 (未找到)
    lRUCache->put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
    cout << endl << lRUCache->get(1);    // 返回 -1 (未找到)
    cout << endl << lRUCache->get(3);    // 返回 3
    cout << endl << lRUCache->get(4);    // 返回 4
}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */