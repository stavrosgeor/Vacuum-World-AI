//Stavros Georgiou
#include <iostream>
#include <string>

using namespace std;

// Node structure for the linked list
struct Node {
    string data;
    Node* next;

    Node(const string& value) : data(value), next(nullptr) {}
};

// Custom linked list class
class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Function to add a node to the end of the list
    void append(const string& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Function to print the list
    void printList() {
        Node* current = head;
        while (current) {
            cout << current->data << endl;
            current = current->next;
        }
    }

    // Function to free the memory used by the list
    void deleteList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }
};

LinkedList findDirt(string inputArray[3][3]) {
    LinkedList commands;
    int rows = 3;
    int cols = 3;

    int robotRow = 0;
    int robotCol = 0;

    // Find the initial position of the robot
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (inputArray[i][j] == "R") {
                robotRow = i;
                robotCol = j;
                goto foundRobot;
            }
        }
    }
foundRobot:

    // Iterate through the array to find and clean dirt
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (inputArray[i][j] == "*") {
                // Move the robot to the dirt
                while (robotRow < i) {
                    commands.append("Down");
                    robotRow++;
                }
                while (robotRow > i) {
                    commands.append("Up");
                    robotRow--;
                }
                while (robotCol < j) {
                    commands.append("Right");
                    robotCol++;
                }
                while (robotCol > j) {
                    commands.append("Left");
                    robotCol--;
                }

                // Clean the dirt
                commands.append("Suck");
            }
        }
    }

    commands.append("Rooms are clean!");

    return commands;
}

int main() {
    string inputArray[3][3] = { {"_", "R", "_"},
                               {"_", "*", "*"},
                               {"_", "_", "*"} };

    LinkedList commands = findDirt(inputArray);

    // Print the commands
    commands.printList();

    // Delete the linked list to free memory
    commands.deleteList();

    return 0;
}