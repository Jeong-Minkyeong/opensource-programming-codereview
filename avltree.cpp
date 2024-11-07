#include <iostream>

using namespace std;

class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    int height;
    int depth;

    AVLNode(int value, AVLNode* p = nullptr)
        : key(value), left(nullptr), right(nullptr), parent(p), height(1), depth(0) {}
};

class AVLTree {
private:
    AVLNode* root;
    int nodeCount;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    void updateHeightAndDepth(AVLNode* node) {
        if (node) {
            node->height = 1 + max(getHeight(node->left), getHeight(node->right));
            node->depth = (node->parent ? node->parent->depth + 1 : 0);
        }
    }

    int getBalanceFactor(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* node) {
        AVLNode* newRoot = node->left;
        node->left = newRoot->right;
        if (newRoot->right) newRoot->right->parent = node;
        newRoot->right = node;
        newRoot->parent = node->parent;
        node->parent = newRoot;

        updateHeightAndDepth(node);
        updateHeightAndDepth(newRoot);
        return newRoot;
    }

    AVLNode* rotateLeft(AVLNode* node) {
        AVLNode* newRoot = node->right;
        node->right = newRoot->left;
        if (newRoot->left) newRoot->left->parent = node;
        newRoot->left = node;
        newRoot->parent = node->parent;
        node->parent = newRoot;

        updateHeightAndDepth(node);
        updateHeightAndDepth(newRoot);
        return newRoot;
    }

    AVLNode* balance(AVLNode* node) {
        updateHeightAndDepth(node);
        int balance = getBalanceFactor(node);

        if (balance > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balance < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* insert(int key) {
        // 새로운 노드를 루트에서부터 삽입
        AVLNode* newNode = new AVLNode(key);
        if (!root) {
            root = newNode;
            nodeCount++;
            return root;
        }

        AVLNode* currentNode = root;
        AVLNode* parentNode = nullptr;

        // 적절한 위치를 찾아 삽입
        while (currentNode) {
            parentNode = currentNode;
            if (key < currentNode->key) {
                currentNode = currentNode->left;
            }
            else if (key > currentNode->key) {
                currentNode = currentNode->right;
            }
        }

        // 새 노드를 삽입
        if (key < parentNode->key) {
            parentNode->left = newNode;
        }
        else {
            parentNode->right = newNode;
        }
        newNode->parent = parentNode; // 부모 설정
        nodeCount++;

        AVLNode* nodeToBalance = newNode;
        while (nodeToBalance) {
            nodeToBalance = balance(nodeToBalance);
            nodeToBalance = nodeToBalance->parent; // 부모 노드로 올라감
        }

        return newNode;
    }

    AVLNode* find(int key) {
        AVLNode* currentNode = root; // 루트에서 시작
        while (currentNode) {
            if (key == currentNode->key) {
                return currentNode; // 키를 찾으면 노드 반환
            }
            currentNode = key < currentNode->key ? currentNode->left : currentNode->right; // 왼쪽 또는 오른쪽으로 이동
        }
        return nullptr; // 노드를 찾지 못하면 nullptr 반환
    }

    AVLNode* minNode(AVLNode* node) {
        return node->left ? minNode(node->left) : node;
    }

    AVLNode* successor(AVLNode* node) {
        if (node->right) return minNode(node->right);
        AVLNode* p = node->parent;
        while (p && node == p->right) {
            node = p;
            p = p->parent;
        }
        return p;
    }

    AVLNode* remove(AVLNode* node, int key) {
        if (!node) return node;

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    nodeCount--;
                    delete node;
                    return nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                AVLNode* temp = successor(node);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }
        return balance(node);
    }

    int height(AVLNode* node) {
        return node ? node->height : -1;
    }

public:
    AVLTree() : root(nullptr), nodeCount(0) {}


    void ancestor(int key) {
        AVLNode* targetNode = find(key);
        int sum = targetNode->depth + targetNode->height;
        cout << sum << " ";
        if (targetNode == root) {
            cout << "0" << endl;
        }
        else {
            AVLNode* ancestorNode = targetNode->parent;
            sum = 0;
            while (ancestorNode) {
                sum += ancestorNode->key;
                ancestorNode = ancestorNode->parent;
            }
            cout << sum << endl;
        }

    }

    void average(int key) {
        AVLNode* targetNode = find(key); // 주어진 key를 가진 노드를 찾음


        // 서브트리의 최소값과 최대값을 찾기 위한 변수
        int minKey = targetNode->key, maxKey = targetNode->key;

        // 최소값을 찾기 위해 왼쪽 서브트리를 탐색
        AVLNode* currentNode = targetNode;
        while (currentNode) {
            minKey = min(minKey, currentNode->key);
            currentNode = currentNode->left; // 왼쪽 자식으로 이동
        }

        // 최대값을 찾기 위해 오른쪽 서브트리를 탐색
        currentNode = targetNode;
        while (currentNode) {
            maxKey = max(maxKey, currentNode->key);
            currentNode = currentNode->right; // 오른쪽 자식으로 이동
        }

        // 최소값과 최대값의 평균을 계산하여 출력

        cout << (minKey + maxKey) / 2 << endl; // 평균 출력

    }


};

int main() {
    AVLTree tree;

    string command;
    while (cin >> command) {


        if (command == "Ancestor") {
            int x;
            cin >> x;
            tree.ancestor(x);
        }
        else if (command == "Average") {
            int x;
            cin >> x;
            tree.average(x);
        }
    }
}}