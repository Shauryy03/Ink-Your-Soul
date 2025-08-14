#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct User {
    string username;
    string password;
};

struct Story {
    string content;
};

struct Dream {
    string content;
};

struct Task {
    string description;
    bool completed;
};

const string USER_FILE = "users.txt";
const string STORY_FILE = "stories.txt";
const string DREAM_FILE = "dreams.txt";
const string TASK_FILE = "tasks.txt";

// ---------------- Utility ----------------
void saveUser(const User &user) {
    ofstream out(USER_FILE, ios::app);
    out << user.username << "|" << user.password << "\n";
    out.close();
}

bool authenticateUser(const string &username, const string &password) {
    ifstream in(USER_FILE);
    string line;
    while (getline(in, line)) {
        size_t pos = line.find("|");
        if (pos != string::npos) {
            string u = line.substr(0, pos);
            string p = line.substr(pos + 1);
            if (u == username && p == password) return true;
        }
    }
    return false;
}

// ---------------- Story ----------------
void addStory() {
    cin.ignore();
    cout << "Enter your story: ";
    string story;
    getline(cin, story);
    ofstream out(STORY_FILE, ios::app);
    out << story << "\n";
    cout << "Story saved!\n";
}

void viewStories() {
    ifstream in(STORY_FILE);
    string line;
    cout << "\n--- Stories ---\n";
    while (getline(in, line)) {
        cout << "- " << line << "\n";
    }
}

// ---------------- Dream ----------------
void addDream() {
    cin.ignore();
    cout << "Enter your dream: ";
    string dream;
    getline(cin, dream);
    ofstream out(DREAM_FILE, ios::app);
    out << dream << "\n";
    cout << "Dream saved!\n";
}

void viewDreams() {
    ifstream in(DREAM_FILE);
    string line;
    cout << "\n--- Dreams ---\n";
    while (getline(in, line)) {
        cout << "- " << line << "\n";
    }
}

// ---------------- Task ----------------
void addTask() {
    cin.ignore();
    cout << "Enter task description: ";
    string desc;
    getline(cin, desc);
    ofstream out(TASK_FILE, ios::app);
    out << desc << "|0\n"; // 0 = not completed
    cout << "Task saved!\n";
}

void viewTasks() {
    ifstream in(TASK_FILE);
    string line;
    cout << "\n--- Tasks ---\n";
    while (getline(in, line)) {
        size_t pos = line.find("|");
        if (pos != string::npos) {
            string desc = line.substr(0, pos);
            bool completed = (line.substr(pos + 1) == "1");
            cout << "- " << desc << " [" << (completed ? "Done" : "Pending") << "]\n";
        }
    }
}

// ---------------- Main Menu ----------------
void mainMenu() {
    while (true) {
        cout << "\n--- Ink Your Soul ---\n";
        cout << "1. Add Story\n2. View Stories\n3. Add Dream\n4. View Dreams\n5. Add Task\n6. View Tasks\n7. Logout\nChoose: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1: addStory(); break;
            case 2: viewStories(); break;
            case 3: addDream(); break;
            case 4: viewDreams(); break;
            case 5: addTask(); break;
            case 6: viewTasks(); break;
            case 7: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

// ---------------- Authentication Menu ----------------
int main() {
    while (true) {
        cout << "\n--- Welcome to Ink Your Soul ---\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            User u;
            cout << "Enter username: ";
            cin >> u.username;
            cout << "Enter password: ";
            cin >> u.password;
            saveUser(u);
            cout << "User registered successfully!\n";
        } else if (choice == 2) {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (authenticateUser(username, password)) {
                cout << "Login successful!\n";
                mainMenu();
            } else {
                cout << "Invalid credentials!\n";
            }
        } else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}