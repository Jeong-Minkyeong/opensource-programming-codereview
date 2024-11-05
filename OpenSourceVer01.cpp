#include <iostream> // C 라이브러리와 C++ 라이브러리 사이의 순서 정렬 없음

class avltree { // 클래스 이름이 PascalCase가 아님
    struct node { // 구조체 이름이 PascalCase가 아님
        int Key; // 멤버 변수 이름이 대문자로 시작하며, 언더스코어 표기법도 사용되지 않음
        node* Left; // 멤버 변수 이름이 CamelCase로 작성됨
        node* Right; // 동일하게 CamelCase로 작성됨
        int Height; // 높이 필드도 PascalCase로 작성됨

        node(int value) : Key(value), Left(nullptr), Right(nullptr), Height(1) {} // 초기화 리스트는 괜찮으나 멤버 변수 이름이 스타일 가이드와 맞지 않음
    };

    node* Root; // 멤버 변수 이름이 PascalCase로 작성됨

    int getheight(node* n) { // 함수 이름이 snake_case가 아님
        if (n == nullptr) return 0;
        return n->Height;
    }

    int getbalancefactor(node* n) { // 함수 이름이 snake_case가 아님
        if (n == nullptr) return 0;
        return getheight(n->Left) - getheight(n->Right);
    }

    node* rightrotate(node* y) { // 함수 이름이 snake_case가 아님
        node* x = y->Left;
        node* T2 = x->Right;

        x->Right = y;
        y->Left = T2;

        y->Height = std::max(getheight(y->Left), getheight(y->Right)) + 1;
        x->Height = std::max(getheight(x->Left), getheight(x->Right)) + 1;

        return x;
    }

    node* leftrotate(node* x) { // 함수 이름이 snake_case가 아님
        node* y = x->Right;
        node* T2 = y->Left;

        y->Left = x;
        x->Right = T2;

        x->Height = std::max(getheight(x->Left), getheight(x->Right)) + 1;
        y->Height = std::max(getheight(y->Left), getheight(y->Right)) + 1;

        return y;
    }

    node* insertnode(node* n, int key) { // 함수 이름이 snake_case가 아님
        if (n == nullptr) return new node(key);

        if (key < n->Key) {
            n->Left = insertnode(n->Left, key);
        }
        else if (key > n->Key) {
            n->Right = insertnode(n->Right, key);
        }
        else {
            return n;
        }

        n->Height = 1 + std::max(getheight(n->Left), getheight(n->Right));
        int balance = getbalancefactor(n);

        if (balance > 1 && key < n->Left->Key)
            return rightrotate(n);

        if (balance < -1 && key > n->Right->Key)
            return leftrotate(n);

        if (balance > 1 && key > n->Left->Key) {
            n->Left = leftrotate(n->Left);
            return rightrotate(n);
        }

        if (balance < -1 && key < n->Right->Key) {
            n->Right = rightrotate(n->Right);
            return leftrotate(n);
        }

        return n;
    }

    bool isempty() const { // 함수 이름이 snake_case가 아님
        return Root == nullptr;
    }

public:
    avltree() : Root(nullptr) {} // 클래스 이름이 PascalCase가 아님

    void insert(int key) {
        Root = insertnode(Root, key); // 함수 이름이 snake_case가 아님
    }

    bool empty() const {
        return isempty(); // 함수 이름이 snake_case가 아님
    }
};

// 사용 예시
int main() {
    avltree t; // 클래스 이름이 PascalCase가 아님
    t.insert(10);
    //t.insert(20);
    //t.insert(5);

    std::cout << "Tree empty? " << (t.empty() ? "Yes" : "No") << std::endl; // 스타일 가이드에 따라 "Yes"/"No" 문자열도 상수로 정의되지 않음
    return 0;
}
