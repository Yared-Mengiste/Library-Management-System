#ifndef TREEM_H
#define TREEM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tree.h"
#include "membertype.h"

template <class T>
class TreeM {
public:
    TreeM();

    // Basic Tree Operations
    void insert(T value);
    void remove(T value);
    void display();
    Node<T>* search(int id);
    
    // File Operations
    void writeToFile(std::string filename);
    int readFromFile(std::string filename);
    int findMax();

private:
    Node<T>* root;

    // Helper functions for insertion, removal, and search
    Node<T>* insert(T value, Node<T>* temp);
    Node<T>* remove(T value, Node<T>* temp);
    Node<T>* search(int id, Node<T>* temp);

    // Helper for traversal
    void inorder(Node<T>* temp);
    Node<T>*inorderSuccessor(Node<T>* temp);
    // Helper for writing and reading to/from file
    void writeToFile(Node<T>* temp, std::ofstream& outfile);
};
template <class T>
TreeM<T>::TreeM() : root(nullptr) {}

template <class T>
Node<T>* TreeM<T>::insert(T value, Node<T>* temp) {
    if (temp == nullptr) {
        temp = new Node<T>();
        temp->data = value;
        temp->left = temp->right = nullptr;
    } else if (value.getId() < temp->data.getId()) {
        temp->left = insert(value, temp->left);
    } else {
        temp->right = insert(value, temp->right);
    }
    return temp;
}
template <class T>
int TreeM<T>::findMax() {
    Node<T> *temp = root;
    if (temp == nullptr) {
        return -1;  // The tree is empty
    }

    // Keep going to the right until the rightmost node is found
    while (temp->right != nullptr) {
        temp = temp->right;
    } 

    return temp->data.getId();  // This is the node with the maximum ID
}


template <class T>
void TreeM<T>::insert(T value) {
    root = insert(value, root);
}

template <class T>
Node<T>* TreeM<T>::remove(T value, Node<T>* temp) {
    if (temp == nullptr) {
        return nullptr; // Base case: value not found in the tree
    }

    // Compare the titles of the books
    if (value.getId() < temp->data.getId()) {
        // Search in the left subtree
        temp->left = remove(value, temp->left);
    } else if (value.getId() > temp->data.getId()) {
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
void TreeM<T>::remove(T value) {
    root = remove(value, root);
}

template <class T>
Node<T>* TreeM<T>::search(int id, Node<T>* temp) {
    if (temp == nullptr) {
        return nullptr;
    } else if (id < temp->data.getId()) {
        return search(id, temp->left);
    } else if (id > temp->data.getId()) {
        return search(id, temp->right);
    } else {
        return temp;
    }
}

template <class T>
Node<T>* TreeM<T>::search(int id) {
    return search(id, root);
}

template <class T>
void TreeM<T>::inorder(Node<T>* temp) {
    if (temp != nullptr) {
        inorder(temp->left);
        temp->data.print();
        inorder(temp->right);
    }
}
template <class T>
Node<T>* TreeM<T>::inorderSuccessor(Node<T>* temp) {
    temp = temp->right;
    while (temp != nullptr && temp->left != nullptr) {
        temp = temp->left;
    }
    return temp;
}

   
template <class T>
void TreeM<T>::display() {
    inorder(root);
}

// File I/O methods

template <class T>
void TreeM<T>::writeToFile(std::string filename) {
    std::ofstream outfile(filename);
    if (outfile.is_open()) {
        writeToFile(root, outfile);
        outfile.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

template <class T>
void TreeM<T>::writeToFile(Node<T>* temp, std::ofstream& outfile) {
    if (temp != nullptr) {
        writeToFile(temp->left, outfile);
        outfile << temp->data.getTitle() << "/"
                << temp->data.getId() << "\n";
        writeToFile(temp->right, outfile);
    }
}

template <class T>
int TreeM<T>::readFromFile(std::string filename) {
    std::ifstream infile(filename);
    int cntr = 0;
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            std::string name;
            int id;
            
            // Read and parse each field from the string
            std::getline(ss, name, '/');
            ss >> id;

            MemberType member(name,id);

            insert(member);
            cntr++;
        }
        infile.close();
        std::cout << "Tree created from file: " << filename << std::endl;
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    return cntr;
}


#endif // TREEM_H
