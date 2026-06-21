/**
 * ProjectTwo.cpp
 * * This program implements an advising assistance tool for the Computer Science department.
 * It utilizes a Binary Search Tree (BST) to load, store, and manage course data,
 * providing efficient retrieval and alphanumeric sorting capabilities.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Represents a single course in the curriculum
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;
};

// Represents a node in the Binary Search Tree
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() : left(nullptr), right(nullptr) {}
    Node(Course aCourse) : Node() {
        course = aCourse;
    }
};

/**
 * Utility: Converts a string to uppercase.
 * Used for case-insensitive searching.
 */
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

/**
 * Utility: Splits a string by a delimiter.
 * Handles potential carriage returns from file input.
 */
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        if (!token.empty() && token.back() == '\r') {
            token.pop_back();
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

/**
 * Binary Search Tree class to manage Course objects.
 */
class BinarySearchTree {
private:
    Node* root;

    void addNode(Node* node, Course newCourse);
    void inOrderTraversal(Node* node);
    void searchTree(Node* node, string courseNumber);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert(Course newCourse);
    void PrintAllCourses();
    void PrintCourse(string courseNumber);
};

BinarySearchTree::BinarySearchTree() { root = nullptr; }

BinarySearchTree::~BinarySearchTree() { destroyTree(root); }

void BinarySearchTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void BinarySearchTree::Insert(Course newCourse) {
    if (root == nullptr) {
        root = new Node(newCourse);
    }
    else {
        addNode(root, newCourse);
    }
}

void BinarySearchTree::addNode(Node* node, Course newCourse) {
    if (newCourse.courseNumber < node->course.courseNumber) {
        if (node->left == nullptr) node->left = new Node(newCourse);
        else addNode(node->left, newCourse);
    }
    else {
        if (node->right == nullptr) node->right = new Node(newCourse);
        else addNode(node->right, newCourse);
    }
}

void BinarySearchTree::PrintAllCourses() {
    if (root == nullptr) {
        cout << "Error: No data loaded." << endl;
        return;
    }
    inOrderTraversal(root);
}

void BinarySearchTree::inOrderTraversal(Node* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);
        cout << node->course.courseNumber << ": " << node->course.title << endl;
        inOrderTraversal(node->right);
    }
}

void BinarySearchTree::PrintCourse(string courseNumber) {
    searchTree(root, toUpper(courseNumber));
}

void BinarySearchTree::searchTree(Node* node, string courseNumber) {
    if (node == nullptr) {
        cout << "Course " << courseNumber << " not found." << endl;
        return;
    }
    if (node->course.courseNumber == courseNumber) {
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        cout << "Prerequisites: ";
        if (node->course.prerequisites.empty()) cout << "None";
        for (const auto& p : node->course.prerequisites) cout << p << " ";
        cout << endl;
    }
    else if (courseNumber < node->course.courseNumber) {
        searchTree(node->left, courseNumber);
    }
    else {
        searchTree(node->right, courseNumber);
    }
}

/**
 * Loads course data from the specified CSV file.
 */
void loadCourses(const string& filename, BinarySearchTree* bst) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<string> tokens = split(line, ',');
        if (tokens.size() < 2) continue;

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            course.prerequisites.push_back(tokens[i]);
        }
        bst->Insert(course);
    }
    file.close();
    cout << "Data loaded successfully." << endl;
}

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    int choice = 0;
    string filename = "CS 300 ABCU_Advising_Program_Input.csv";

    while (choice != 9) {
        cout << "\nMenu Options:\n"
            << "1. Load Data\n"
            << "2. Print Course List\n"
            << "3. Print Course Details\n"
            << "9. Exit\n"
            << "Selection: ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourses(filename, bst);
            break;
        case 2:
            bst->PrintAllCourses();
            break;
        case 3: {
            string id;
            cout << "Enter course ID: ";
            cin >> id;
            bst->PrintCourse(id);
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
    delete bst;
    return 0;
}