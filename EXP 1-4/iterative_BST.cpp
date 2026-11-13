
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

// Iterative insertion
Node* insert(Node* root, int val)
{
    Node* newNode = new Node(val);

    if(root == nullptr)
        return newNode;

    Node* curr = root;
    Node* parent = nullptr;

    while(curr != nullptr)
    {
        parent = curr;

        if(val < curr->data)
            curr = curr->left;

        else if(val > curr->data)
            curr = curr->right;

        else
        {
            delete newNode;
            return root;
        }
    }

    if(val < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Iterative searching
bool search(Node* root, int key)
{
    Node* curr = root;

    while(curr != nullptr)
    {
        if(curr->data == key)
            return true;

        if(key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    return false;
}

// Iterative inorder traversal
void inorder(Node* root)
{
    Node* stack[1000];
    int top = -1;
    Node* curr = root;

    while(curr != nullptr || top != -1)
    {
        while(curr != nullptr)
        {
            stack[++top] = curr;
            curr = curr->left;
        }

        curr = stack[top--];

        cout << curr->data << " ";

        curr = curr->right;
    }
}

int main()
{
    Node* root = nullptr;
    int n, val, key;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter elements: ";

    for(int i = 0; i < n; i++)
    {
        cin >> val;
        root = insert(root, val);
    }

    cout << "\nInorder Traversal: ";
    inorder(root);

    cout << "\nEnter element to search: ";
    cin >> key;

    auto start = high_resolution_clock::now();

    bool found = search(root, key);

    auto stop = high_resolution_clock::now();

    auto duration =
        duration_cast<nanoseconds>(stop - start);

    cout << "\nSearch Result: "
         << (found ? "Found" : "Not Found");

    cout << "\nExecution Time: "
         << duration.count() << " nanoseconds";

    return 0;
}
