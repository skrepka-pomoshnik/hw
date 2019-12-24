#include <iostream>

//procedural hell 4ever

typedef struct Node {
    int data;
    bool color; //1 = red
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

struct Node  SentinelNode;
Node* Sent = &SentinelNode;

Node **Root = NULL;

Node* newNode(int data) {
    Node *temp   = (Node*) new Node;
    temp->data    = data;
    temp->color  = 1;
    temp->left   = NULL;
    temp->right  = NULL;
    temp->parent = NULL;

    return temp;
}

void rotateL( Node** T, Node* x) {
    Node *y  = x->right;    // set y
    x->right = y->left;     // turn y's left subtree into x's right subtree{
    if (y->left != Sent)
        y->left->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == Sent)
        *T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;            // put x on y's left
    x->parent = y;
}

void rotateR(Node** T, Node* y) {
    Node *x  = y->left;     // set x
    y->left  = x->right;    // turn x's right subtree into y's left subtree{
    if (x->right != Sent)
        x->right->parent = y;
    x->parent = y->parent;  // link y's parent to x
    if (y->parent == Sent)
        *T = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left  = x;
    x->right  = y;         // put y on x's right
    y->parent = x;
}



void rbFix(Node** Root, Node* New) {
    Node* temp;
    while (New->parent->color == 1) {
        if (New->parent == New->parent->parent->left) {
            temp = New->parent->parent->right;
            if (temp->color == 1) {
                New->parent->color = 0;
                temp->color = 0;
                New->parent->parent->color = 1;
                New = New->parent->parent;
            }
            else {
                if (New == New->parent->right) {
                    New = New->parent;
                    rotateL(Root, New);
                }
                New->parent->color = 0;
                New->parent->parent->color = 1;
                rotateR(Root, New->parent->parent);
            }
        }
        else {
            temp = New->parent->parent->left;
            if (temp->color == 1) {
                New->parent->color = 0;
                New->color = 0;
                New->parent->parent->color = 1;
                New = New->parent->parent;
            }
            else {
                if (New == New->parent->left) {
                    New = New->parent;
                    rotateR(Root, New);
                }
                New->parent->color = 0;
                New->parent->parent->color = 1;
                rotateL(Root, New->parent->parent);
            }
        }
    }
    Root[0]->color = 0;
}

void rbInsert(Node** T, int data) {
    Node* z =  newNode(data);
    Node* y =  Sent;
    Node* x = *T;

    // find a free place
    while (x != Sent) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == Sent)
        *T = z;
    else if (z->data < y->data)
        y->left  = z;
    else
        y->right = z;

    z->left  = Sent;
    z->right = Sent;
    z->color = 1;

    // fix rb 
    rbFix(T, z);
}

void printTree(Node* root) {
    if (root != Sent ) {
    if (root->left != Sent)
        printTree(root->left);
    std::cout << root->data << ", ";
    if (root->right != Sent)
        printTree(root->right);
    } else 
    printf("NULL");
}


Node* search(struct Node* root, int que) { 
    if (root == NULL || root->data == que) 
        return root; 

    if (root->data < que) 
        return search(root->right, que); 

    return search(root->left, que); 
}

void setInsert (Node** T, int data) {
    if (!search(*T, data)) {
        rbInsert(T, data);
    }
}

class Set {
    public:
        Node* content = Sent;
        
        Set() {}
        Set(int size, int list[]) {
            for (int i = 0; i < size; i++) {
                setInsert(&content, list[i]);
            }
        }

        //Set operator=(const Set &set)

        void insert(int i) {
                setInsert(&content, i);
            ;}

        bool contains(int i) {
            return search(content, i);
            ;}


        void print() {
            printTree(content)
                ;}
};

//i wish it workd
//void SetTraversal(struct Node* root, Set a, Set &c, void (*check)(Set,Set &,int)) 
//{ 
//    struct Node *current, *pre; 
//  
//    if (root == NULL) 
//        return; 
//  
//    current = root; 
//    while (current != NULL) { 
//  
//        if (current->left == NULL) { 
//            check(a,c,current->data); 
//            current = current->right; 
//        } 
//        else { 
//  
//            /* Find the inorder predecessor of current */
//            pre = current->left; 
//            while (pre->right != NULL && pre->right != current) 
//                pre = pre->right; 
//  
//            /* Make current as right child of its inorder  
//               predecessor */
//            if (pre->right == NULL) { 
//                pre->right = current; 
//                current = current->left; 
//            } 
//  
//            /* Revert the changes made in if part to restore  
//               the original tree i.e., fix the right child 
//               of predecssor */
//            else { 
//                pre->right = NULL; 
//                check(a,c,current->data); 
//                current = current->right; 
//            }
//        }
//    }
//}


void Rtraverse(Node* root, Set a, Set &c, void (*check)(Set,Set &,int)) {
    if (root->left != Sent)
        Rtraverse(root->left, a, c, check); 
    check(a,c,root->data);
    if (root->right != Sent)
        Rtraverse(root->right, a, c, check);
}


void InsertifNotcontains(Set a, Set &c, int t) {
if (!a.contains(t)) 
    c.insert(t);
}

void Insertifcontains(Set a, Set &c, int t) {
if (a.contains(t)){
        c.insert(t);
}
}

Set SetMerge(Set a, Set b) {
    //SetTraversal(b.content, a, a, Insertifcontains);
    //Set c = a; //reload
    Set c;
    Rtraverse(a.content, a, c, Insertifcontains); //copy c to a in an ugly way
    Rtraverse(b.content, c, c, InsertifNotcontains);
        return c;
}

Set SetIntersect(Set a, Set b) {
    Set c;
    Rtraverse(b.content, a, c, Insertifcontains);
        return c;
}


Set SetDiff(Set a, Set b) {
    Set c;
    Rtraverse(b.content, a, c, InsertifNotcontains);
        return c;
}


Set operator+(Set const & a, Set const & b)
{
    return SetMerge(a,b);
}

Set operator*(Set const & a, Set const & b)
{
    return SetIntersect(a,b);
}

Set operator-(Set const & a, Set const & b)
{
    return SetDiff(a,b);
}

int main() {
    //Sets of 5 elements
    int list1[5] = {2, 4, 8, 900, 900};
    int list2[5] = {1,3,5,7,900};
    Set Set1(5, list1);
    Set Set2(5, list2);

    Set Set3;
    Set3 = Set1 + Set2;
    std::cout << "Set1:" << std::endl;
    Set1.print();
    std::cout << std::endl << "Set2:" << std::endl;
    Set2.print();
    std::cout << std::endl << "Set1+Set2:" << std::endl;
    Set3.print();
    std::cout << std::endl << "Set1*Set2:" << std::endl;
    Set3 = Set1 * Set2;
    Set3.print();
    std::cout << std::endl << "Set1-Set2:" << std::endl;
    Set3 = Set1 - Set2;
    Set3.print();
    std::cout <<  std::endl;
}


