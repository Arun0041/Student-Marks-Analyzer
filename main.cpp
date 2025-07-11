#include <iostream>
#include <string>
using namespace std;

const int MAX = 100;

struct Student {
    string name;
    int marks;
};

void inputStudents(Student students[], int &n) {
    cout << "Enter number of students: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter name of student " << i + 1 << ": ";
        cin >> students[i].name;
        cout << "Enter marks of " << students[i].name << ": ";
        cin >> students[i].marks;
    }
}

float calculateAverage(Student students[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += students[i].marks;
    }
    return (float)sum / n;
}

int findMaximum(Student students[], int n) {
    int maxMarks = students[0].marks;
    for (int i = 1; i < n; i++) {
        if (students[i].marks > maxMarks)
            maxMarks = students[i].marks;
    }
    return maxMarks;
}

int findMinimum(Student students[], int n) {
    int minMarks = students[0].marks;
    for (int i = 1; i < n; i++) {
        if (students[i].marks < minMarks)
            minMarks = students[i].marks;
    }
    return minMarks;
}

void bubbleSort(Student students[], int n, bool ascending = true) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((ascending && students[j].marks > students[j + 1].marks) ||
                (!ascending && students[j].marks < students[j + 1].marks)) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void selectionSort(Student students[], int n, bool ascending = true) {
    for (int i = 0; i < n - 1; i++) {
        int selectedIndex = i;
        for (int j = i + 1; j < n; j++) {
            if ((ascending && students[j].marks < students[selectedIndex].marks) ||
                (!ascending && students[j].marks > students[selectedIndex].marks)) {
                selectedIndex = j;
            }
        }
        if (selectedIndex != i) {
            swap(students[i], students[selectedIndex]);
        }
    }
}

int partition(Student students[], int low, int high, bool ascending) {
    int pivot = students[high].marks;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if ((ascending && students[j].marks < pivot) || (!ascending && students[j].marks > pivot)) {
            i++;
            swap(students[i], students[j]);
        }
    }
    swap(students[i + 1], students[high]);
    return i + 1;
}

void quickSort(Student students[], int low, int high, bool ascending = true) {
    if (low < high) {
        int pi = partition(students, low, high, ascending);
        quickSort(students, low, pi - 1, ascending);
        quickSort(students, pi + 1, high, ascending);
    }
}

void displayStudents(Student students[], int n) {
    cout << "\n--- Student Marks ---\n";
    for (int i = 0; i < n; i++) {
        cout << students[i].name << ": " << students[i].marks << endl;
    }
}

void linearSearch(Student students[], int n, string keyName) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (students[i].name == keyName) {
            cout << keyName << " scored: " << students[i].marks << endl;
            found = true;
            break;
        }
    }
    if (!found)
        cout << "Student not found!" << endl;
}

int binarySearch(Student students[], int n, string keyName) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].name == keyName)
            return mid;
        else if (students[mid].name < keyName)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void sortByName(Student students[], int n) {

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (students[j].name > students[j + 1].name)
                swap(students[j], students[j + 1]);
}

int main() {
    Student students[MAX];
    int n = 0;
    int choice;

    do {
        cout << "\n--- Student Marks Analyzer ---\n";
        cout << "1. Input student data\n";
        cout << "2. Display student data\n";
        cout << "3. Calculate average, max, min\n";
        cout << "4. Sort marks (Bubble/Selection/Quick)\n";
        cout << "5. Search student by name (Linear/Binary)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputStudents(students, n);
                break;

            case 2:
                displayStudents(students, n);
                break;

            case 3:
                cout << "Average marks: " << calculateAverage(students, n) << endl;
                cout << "Maximum marks: " << findMaximum(students, n) << endl;
                cout << "Minimum marks: " << findMinimum(students, n) << endl;
                break;

            case 4: {
                int sortType, order;
                cout << "Choose Sorting Algorithm: 1. Bubble 2. Selection 3. Quick: ";
                cin >> sortType;
                cout << "Order? 1. Ascending  2. Descending: ";
                cin >> order;
                bool asc = (order == 1);

                switch (sortType) {
                    case 1: bubbleSort(students, n, asc); break;
                    case 2: selectionSort(students, n, asc); break;
                    case 3: quickSort(students, 0, n - 1, asc); break;
                    default: cout << "Invalid sort type\n"; break;
                }
                cout << "Sorted list:\n";
                displayStudents(students, n);
                break;
            }

            case 5: {
                int searchType;
                string name;
                cout << "Enter student name to search: ";
                cin >> name;
                cout << "Search method: 1. Linear  2. Binary: ";
                cin >> searchType;

                if (searchType == 1) {
                    linearSearch(students, n, name);
                } else if (searchType == 2) {
                    sortByName(students, n); 
                    int index = binarySearch(students, n, name);
                    if (index != -1)
                        cout << name << " scored: " << students[index].marks << endl;
                    else
                        cout << "Student not found!\n";
                } else {
                    cout << "Invalid search type!\n";
                }
                break;
            }

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
