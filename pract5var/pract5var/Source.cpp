#include <iostream>
#include<iomanip>//для setw
#define RE "\x1B[31m"//для вывода цвета узлов в консоль 
#define GRN "\x1B[32m"
#define RESET "\x1B[0m"


using namespace std;

//цвет узла
enum Color { RED, BLACK };


 //структура узла
struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k) : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};
//левый поворот
void rotateLeft(Node*& root, Node* x) {
    Node* y = x->right;

    x->right = y->left;

    if (y->left != nullptr)
    {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}
//правый поворот
void rotateRight(Node*& root, Node* y) {
    Node* x = y->left;

    y->left = x->right;

    if (x->right != nullptr)
    {
        x->right->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == nullptr)
    {
        root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}
//балансировка
void fixViolation(Node*& root, Node* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;

            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(root, z->parent->parent);
            }
        }
        else {
            Node* y = z->parent->parent->left;

            if (y != nullptr && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }

    root->color = BLACK;
}
//вставка числа
void insert(Node*& root, int key) {
    Node* z = new Node(key);//новый узел
    Node* y = nullptr;
    Node* x = root;

    while (x != nullptr) {
        y = x;

        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    z->parent = y;

    if (y == nullptr)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    fixViolation(root, z); // в конце вставки вызываем балансировку
}

//вывод красивого дерева 
void postorder(Node* p, int indent)
{
    if (p != NULL) {
        if (p->right) {
            postorder(p->right, indent + 4);
        }
        if (indent) {
            cout << setw(indent) << ' ';
        }
        if (p->right) cout << " /\n" << setw(indent) << ' ';
        if (p->color==RED) {
            cout << RE << p->key << RESET << "\n ";
        }
        else {
            cout << GRN << p->key << RESET << "\n ";
        }

        if (p->left) {
            cout << setw(indent) << ' ' << " \\\n";
            postorder(p->left, indent + 4);
        }
    }
}

int main() {
    Node* root = nullptr;//корень
    setlocale(LC_ALL, "Russian");//вывод нормального русского языка
    int sum = 0,value;//колличество элементов и сам элемент
    while (1) {
        cout << "Введите число:" << endl;
        cin >> value;
        insert(root, value);
        sum++;
        system("cls");
        postorder(root, sum);
    }
    return 0;
}
