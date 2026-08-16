//============================================================================
// Name        : ProjectTwo.cpp
// Author      : David Alawoe
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : ABCU Advising Assistance Program
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

/**
 * Structure used to store course information.
 */
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

/**
 * Internal structure for a binary search tree node.
 */
struct Node {
    Course course;
    Node* left;
    Node* right;

    /**
     * Initialize a node with a course.
     *
     * @param aCourse Course to store in the node
     */
    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree of courses.
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void destroyTree(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();

    void Insert(Course course);
    Course Search(string courseNumber);
    void InOrder();
};

/**
 * Default constructor.
 */
BinarySearchTree::BinarySearchTree() {

    // Initialize an empty binary search tree.
    root = nullptr;
}

/**
 * Destructor.
 */
BinarySearchTree::~BinarySearchTree() {

    // Recursively delete every node beginning at the root.
    destroyTree(root);

    root = nullptr;
}

/**
 * Recursively delete all nodes in the binary search tree.
 *
 * @param node Current node in the tree
 */
void BinarySearchTree::destroyTree(Node* node) {

    // Stop when an empty branch is reached.
    if (node == nullptr) {
        return;
    }

    // Delete both subtrees before deleting the current node.
    destroyTree(node->left);
    destroyTree(node->right);

    delete node;
}

/**
 * Insert a course into the binary search tree.
 *
 * @param course Course to insert
 */
void BinarySearchTree::Insert(Course course) {

    // If the tree is empty, the new course becomes the root.
    if (root == nullptr) {
        root = new Node(course);
    }
    else {

        // Recursively find the correct position for the new course.
        addNode(root, course);
    }
}

/**
 * Add a course to a node recursively.
 *
 * @param node Current node in the tree
 * @param course Course to be inserted
 */
void BinarySearchTree::addNode(Node* node, Course course) {

    // Smaller course numbers are stored in the left subtree.
    if (course.courseNumber < node->course.courseNumber) {

        // Insert the course if the left position is available.
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {

            // Continue searching down the left subtree.
            addNode(node->left, course);
        }
    }
    else {

        // Insert the course if the right position is available.
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {

            // Continue searching down the right subtree.
            addNode(node->right, course);
        }
    }
}

/**
 * Search for a course using its course number.
 *
 * @param courseNumber Course number to search for
 * @return Course matching the requested course number
 */
Course BinarySearchTree::Search(string courseNumber) {

    // Start searching at the root.
    Node* current = root;

    // Continue until the course is found or an empty branch is reached.
    while (current != nullptr) {

        // Return the course when a match is found.
        if (courseNumber == current->course.courseNumber) {
            return current->course;
        }

        // Search the left subtree for smaller course numbers.
        if (courseNumber < current->course.courseNumber) {
            current = current->left;
        }
        else {

            // Search the right subtree for larger course numbers.
            current = current->right;
        }
    }

    // Return an empty Course if no matching course is found.
    Course course;
    return course;
}

/**
 * Traverse the binary search tree in order.
 */
void BinarySearchTree::InOrder() {

    // Begin the in-order traversal at the root.
    inOrder(root);
}

/**
 * Recursively traverse and print courses in alphanumeric order.
 *
 * @param node Current node in the tree
 */
void BinarySearchTree::inOrder(Node* node) {

    // Stop when an empty branch is reached.
    if (node == nullptr) {
        return;
    }

    // Visit the left subtree first.
    inOrder(node->left);

    // Display the current course.
    cout << node->course.courseNumber << ", "
         << node->course.courseTitle << endl;

    // Visit the right subtree.
    inOrder(node->right);
}

//============================================================================
// Utility methods
//============================================================================

/**
 * Remove leading and trailing whitespace from a string.
 *
 * @param value String to trim
 * @return Trimmed string
 */
string trim(const string& value) {

    size_t first = value.find_first_not_of(" \t\r\n");

    // Return an empty string if no non-whitespace characters exist.
    if (first == string::npos) {
        return "";
    }

    size_t last = value.find_last_not_of(" \t\r\n");

    return value.substr(first, last - first + 1);
}

/**
 * Convert a string to uppercase.
 *
 * @param value String to convert
 * @return Uppercase version of the string
 */
string toUpper(string value) {

    transform(
        value.begin(),
        value.end(),
        value.begin(),
        [](unsigned char character) {
            return toupper(character);
        }
    );

    return value;
}

//============================================================================
// Course data methods
//============================================================================

/**
 * Load course data from a comma-separated file into the
 * binary search tree.
 *
 * The file is validated before any courses are inserted.
 *
 * @param fileName Name of the course data file
 * @param tree Binary search tree used to store courses
 * @return true when the file is loaded successfully
 */
bool loadCourses(string fileName, BinarySearchTree& tree) {

    ifstream file(fileName);

    // Verify that the requested file can be opened.
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << fileName << endl;
        return false;
    }

    vector<Course> parsedCourses;
    string line;

    // Read each course from the input file.
    while (getline(file, line)) {

        line = trim(line);

        // Ignore completely empty lines.
        if (line.empty()) {
            continue;
        }

        stringstream ss(line);

        string courseNumber;
        string courseTitle;

        // Every valid line must contain a course number and title.
        if (!getline(ss, courseNumber, ',') ||
            !getline(ss, courseTitle, ',')) {

            cout << "Error: Invalid course data format." << endl;

            file.close();
            return false;
        }

        // Standardize the course number and remove extra whitespace.
        courseNumber = toUpper(trim(courseNumber));
        courseTitle = trim(courseTitle);

        // Course number and title are required fields.
        if (courseNumber.empty() || courseTitle.empty()) {

            cout << "Error: Course number or title is missing." << endl;

            file.close();
            return false;
        }

        // Create the Course object.
        Course course;

        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        string prerequisite;

        // Read zero or more prerequisite course numbers.
        while (getline(ss, prerequisite, ',')) {

            prerequisite = toUpper(trim(prerequisite));

            // Ignore empty trailing fields.
            if (!prerequisite.empty()) {
                course.prerequisites.push_back(prerequisite);
            }
        }

        // Verify that the course number has not already been loaded.
        for (const Course& existingCourse : parsedCourses) {

            if (existingCourse.courseNumber == course.courseNumber) {

                cout << "Error: Duplicate course number "
                     << course.courseNumber
                     << "." << endl;

                file.close();
                return false;
            }
        }

        // Store the parsed course temporarily for validation.
        parsedCourses.push_back(course);
    }

    file.close();

    // Verify that at least one course was read.
    if (parsedCourses.empty()) {

        cout << "Error: No course data was found in the file." << endl;

        return false;
    }

    // Validate every prerequisite before inserting courses into the tree.
    for (const Course& course : parsedCourses) {

        for (const string& prerequisite : course.prerequisites) {

            bool found = false;

            // Search the parsed course collection for the prerequisite.
            for (const Course& possibleCourse : parsedCourses) {

                if (possibleCourse.courseNumber == prerequisite) {
                    found = true;
                    break;
                }
            }

            // Reject the file if a prerequisite course does not exist.
            if (!found) {

                cout << "Error: Prerequisite "
                     << prerequisite
                     << " for "
                     << course.courseNumber
                     << " does not exist." << endl;

                return false;
            }
        }
    }

    // Insert all validated courses into the binary search tree.
    for (const Course& course : parsedCourses) {
        tree.Insert(course);
    }

    return true;
}

/**
 * Print information about an individual course.
 *
 * The course title and each prerequisite course number
 * and title are displayed.
 *
 * @param tree Binary search tree containing the courses
 * @param courseNumber Course number requested by the user
 */
void printCourseInformation(
    BinarySearchTree& tree,
    string courseNumber) {

    // Standardize the user's course number.
    courseNumber = toUpper(trim(courseNumber));

    // Search the binary search tree for the requested course.
    Course course = tree.Search(courseNumber);

    // Display an error when the requested course does not exist.
    if (course.courseNumber.empty()) {

        cout << courseNumber
             << " was not found." << endl;

        return;
    }

    // Display the selected course.
    cout << course.courseNumber << ", "
         << course.courseTitle << endl;

    // Courses may have no prerequisites.
    if (course.prerequisites.empty()) {

        cout << "Prerequisites: None" << endl;

        return;
    }

    cout << "Prerequisites:" << endl;

    // Find and display each prerequisite course.
    for (const string& prerequisiteNumber : course.prerequisites) {

        Course prerequisiteCourse =
            tree.Search(prerequisiteNumber);

        if (!prerequisiteCourse.courseNumber.empty()) {

            cout << prerequisiteCourse.courseNumber << ", "
                 << prerequisiteCourse.courseTitle << endl;
        }
    }
}

//============================================================================
// Main program
//============================================================================

/**
 * The one and only main() method.
 */
int main() {

    // Define a binary search tree to hold all courses.
    BinarySearchTree tree;

    // Track whether course data has been loaded successfully.
    bool dataLoaded = false;

    string choice;

    cout << "Welcome to the course planner." << endl;

    // Continue displaying the menu until the user chooses to exit.
    do {

        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        getline(cin, choice);

        //====================================================================
        // Option 1: Load course data
        //====================================================================

        if (choice == "1") {

            // Prevent duplicate loading into the current tree.
            if (dataLoaded) {

                cout << "Course data has already been loaded." << endl;

                continue;
            }

            string fileName;

            cout << "Enter the course data file name: ";

            getline(cin, fileName);

            fileName = trim(fileName);

            // Load and validate the requested course data file.
            if (loadCourses(fileName, tree)) {

                dataLoaded = true;

                cout << "Course data loaded successfully." << endl;
            }
        }

        //====================================================================
        // Option 2: Print all courses
        //====================================================================

        else if (choice == "2") {

            // Course data must be loaded before it can be displayed.
            if (!dataLoaded) {

                cout << "Please load the course data first." << endl;
            }
            else {

                cout << endl;
                cout << "Here is a sample schedule:" << endl;

                // In-order traversal produces alphanumeric course order.
                tree.InOrder();
            }
        }

        //====================================================================
        // Option 3: Print information about one course
        //====================================================================

        else if (choice == "3") {

            // Course data must be loaded before searching.
            if (!dataLoaded) {

                cout << "Please load the course data first." << endl;
            }
            else {

                string courseNumber;

                cout << "What course do you want to know about? ";

                getline(cin, courseNumber);

                printCourseInformation(tree, courseNumber);
            }
        }

        //====================================================================
        // Option 9: Exit
        //====================================================================

        else if (choice == "9") {

            cout << "Thank you for using the course planner!" << endl;
        }

        //====================================================================
        // Invalid menu option
        //====================================================================

        else {

            cout << choice
                 << " is not a valid option." << endl;
        }

    } while (choice != "9");

    return 0;
}
