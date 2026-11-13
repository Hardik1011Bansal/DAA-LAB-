
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

// Recursive insertion
Node* insert(Node* root, int val)
{
    if(root == nullptr)
        return new Node(val);

    if(val < root->data)
        root->left = insert(root->left, val);

    else if(val > root->data)
        root->right = insert(root->right, val);

    return root;
}

// Recursive searching
bool search(Node* root, int key)
{
    if(root == nullptr)
        return false;

    if(root->data == key)
        return true;

    if(key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

// Inorder traversal
void inorder(Node* root)
{
    if(root == nullptr)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
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
