#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "bookType.h"

template <class T>
class Node {
public:
    T data;
    Node* left;
    Node* right;
};

template <class T>
class Tree {
public:
    Tree();
    void insert(T value);
    void remove(T value);
    void display();
    void displayBorrowed(int x);
    void displayBorrowedBooks();
    Node<T>* search(std::string title);
    
    // File Operations
    void writeToFile(std::string filename);
    void readFromFile(std::string filename);

private:
    Node<T>* root;
    void inorder(Node<T>* temp, int id);

    // Helper functions for insertion, removal, and search
    Node<T>* insert(T value, Node<T>* temp);
    Node<T>* remove(T value, Node<T>* temp);
    Node<T>* search(std::string title, Node<T>* temp);

    // Helper for traversal
    void inorder(Node<T>* temp);
    void inorderBorrowed(Node<T>* temp);
    Node<T> *inorderSuccessor(Node<T>* temp);
    // Helper for writing and reading to/from file
    void writeToFile(Node<T>* temp, std::ofstream& outfile);
};

template <class T>
Tree<T>::Tree() : root(nullptr) {}


template <class T>
Node<T>* Tree<T>::insert(T value, Node<T>* temp) {
    if (temp == nullptr) {
        temp = new Node<T>();
        temp->data = value;
        temp->left = temp->right = nullptr;
    } else if (value.getTitle() < temp->data.getTitle()) {
        temp->left = insert(value, temp->left);
    } else {
        temp->right = insert(value, temp->right);
    }
    return temp;
}

template <class T>
void Tree<T>::insert(T value) {
    root = insert(value, root);
}

template <class T>
Node<T>* Tree<T>::remove(T value, Node<T>* temp) {
    if (temp == nullptr) {
        return nullptr; // Base case: value not found in the tree
    }

    // Compare the titles of the books
    if (value.getTitle() < temp->data.getTitle()) {
        // Search in the left subtree
        temp->left = remove(value, temp->left);
    } else if (value.getTitle() > temp->data.getTitle()) {
        // Search in the right subtree
        temp->right = remove(value, temp->right);
    } else {
        // Node to be deleted found
        if (temp->left == nullptr && temp->right == nullptr) {
            // Case 1: Node is a leaf (no children)
            delete temp;
            return nullptr;
        } else if (temp->left == nullptr) {
            // Case 2: Node has only a right child
            Node<T>* rightChild = temp->right;
            delete temp;
            return rightChild;
        } else if (temp->right == nullptr) {
            // Case 2: Node has only a left child
            Node<T>* leftChild = temp->left;
            delete temp;
            return leftChild;
        } else {
            // Case 3: Node has two children
            // Find the inorder successor (smallest node in the right subtree)
            Node<T>* successor = inorderSuccessor(temp);
            // Replace the node's data with the successor's data
            temp->data = successor->data;
            // Remove the inorder successor
            temp->right = remove(successor->data, temp->right);
        }
    }
    return temp;
}

template <class T>
void Tree<T>::remove(T value) {
    root = remove(value, root);
}


template <class T>
Node<T>* Tree<T>::search(std::string title, Node<T>* temp) {
    if (temp == nullptr) {
        return nullptr;
    } else if (title < temp->data.getTitle()) {
        return search(title, temp->left);
    } else if (title > temp->data.getTitle()) {
        return search(title ,temp->right);
    } else {
        return temp;
    }
}

template <class T>
Node<T>* Tree<T>::search(std::string title) {
    return search(title, root);
}

template <class T>
void Tree<T>::inorder(Node<T>* temp) {
    if (temp != nullptr) {
        inorder(temp->left);
        temp->data.print();
        inorder(temp->right);
    }
}
template <class T>
void Tree<T>::inorder(Node<T>* temp, int id) 
{
    if (temp != nullptr) {
        inorder(temp->left, id);
        if (temp->data.getBorrowerId() == id)
            temp->data.print();
        inorder(temp->right, id);
    }
}
template <class T>
void Tree<T>::inorderBorrowed(Node<T>* temp) 
{
    if (temp != nullptr) {
        inorderBorrowed(temp->left);
        if (temp->data.getBorrowerId() != -1)
            temp->data.print();
        inorderBorrowed(temp->right);
    }
}

template <class T>
Node<T>* Tree<T>::inorderSuccessor(Node<T>* temp) {
    temp = temp->right;
    while (temp != nullptr && temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}

template <class T>
void Tree<T>::displayBorrowed(int x)
{
    inorder(root, x);
}
template <class T>
inline void Tree<T>::displayBorrowedBooks()
{
    inorderBorrowed(root);
}
template <class T>
void Tree<T>::display()
{
    inorder(root);
}

// File I/O methods

template <class T>
void Tree<T>::writeToFile(std::string filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        writeToFile(root, outfile);
        outfile.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

template <class T>
void Tree<T>::writeToFile(Node<T>* temp, std::ofstream& outfile) {
    if (temp != nullptr) {
        writeToFile(temp->left, outfile);
        outfile << temp->data.getTitle() << "/"
                << temp->data.getAuthor() << "/"
                << temp->data.getPublisher() << "/"
                << temp->data.getPrice() << "/"
                << temp->data.getPubYear() << "/"
                << temp->data.isBorrowed() << "/"
                << temp->data.getBorrowerId() << "\n";
        writeToFile(temp->right, outfile);
    }
}

template <class T>
void Tree<T>::readFromFile(std::string filename) {
    std::ifstream infile(filename);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string title, author, publisher;
            double price;
            int pubYear;
            bool borrowed;
            int borrower_id;

            // Read and parse each field from the string
            std::getline(ss, title, '/');
            std::getline(ss, author, '/');
            std::getline(ss, publisher, '/');
            ss >> price;
            ss.ignore(); // Ignore '/'
            ss >> pubYear;
            ss.ignore(); 
            ss >> borrowed;
            ss.ignore(); 
            ss >> borrower_id;

            BookType book(title, author, publisher, price, pubYear, borrowed, borrower_id);

            insert(book);
        }
        infile.close();
        std::cout << "Tree created from file: " << filename << std::endl;
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}


#endif // TREE_H
