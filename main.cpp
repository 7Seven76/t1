#include "Pet.h"
#include "Cat.h"
#include "Dog.h"
#include "IntrestedAdopter.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int CAP = 10;

//Loads the file and reads the contents of it.
void load_shelter(const string& file, Pet **&data, int &size) {
    ifstream ifs(file);
    if (ifs.fail()) {
        cout << "Failed to open file" << endl;
        return;
    }
    string line;
    while (getline(ifs, line)) {
        if (size >= CAP) {
            CAP = CAP + CAP / 2;
            Pet **new_data = new Pet*[CAP];
            for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }

            delete[] data;
            data = new_data;
        }
        data[size] = new Pet();
        stringstream ss(line);
        string num_str;
        getline(ss, num_str, ',');
        data[size]->setName(num_str);
        getline(ss, num_str, ',');
        data[size]->setID(stoi(num_str));
        getline(ss, num_str, ',');
        data[size]->setDays_in_shelter(stoi(num_str));
        getline(ss, num_str, ',');
        data[size]->setColor(num_str);
        getline(ss, num_str, ',');
        data[size]->setAnimal_Type(num_str);
        cout << endl;
        size++;
    }
}

void print(Pet**& pets, int& numPets) {
    cout << "Animals in shelter:" << endl << endl;
    for (int i = 0; i < numPets; ++i) {
        pets[i]->getInfo();
    }
}
/*
//Prints whatever is in the selected csv file
void print(Pet **&data, int &size) {
    for (int i = 0; i < size; ++i) {
        cout << "Already in file: " << endl
             << "Name: " << data[i]->getName() << " " << endl
             << "ID: " << data[i]->getID() << " " << endl
             << "Days in shelter: " << data[i]->getDays_in_shelter() << " " << endl
             << "Color: " << data[i]->getColor() << " " << endl
             << "Animal_Type: " << data[i]->getAnimal_Type() << endl;
    }
}*/

//Adds a pet into the selected file
void add_pet(Pet **&data, int &size) {
    if (size >= CAP) {
        CAP = CAP + CAP / 2;
        Pet **new_data = new Pet*[CAP];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
    }
    data[size] = new Pet();
    int id, days_in_shelter;
    string name, color, Animal_Type;
    cout << endl << "Enter name:" << endl;
    cin >> name;
    cout << "Enter id:" << endl;
    cin >> id;
    cout << "Enter days in shelter:" << endl;
    cin >> days_in_shelter;
    cout << "Enter color:" << endl;
    cin >> color;
    cout << "Enter Animal_Type:" << endl;
    cin >> Animal_Type;
    data[size]->setName(name);
    data[size]->setID(id);
    data[size]->setDays_in_shelter(days_in_shelter);
    data[size]->setColor(color);
    data[size]->setAnimal_Type(Animal_Type);
    size++;
}

//Finds the oldest pet inside the file
void find_oldest(Pet **data, int size) {
    if (size == 0) {
        cout << "No pets available to find the oldest resident." << endl;
        return;
    }
    int max_days = data[0]->getDays_in_shelter();
    int index = 0;
    for (int i = 1; i < size; ++i) {
        if (data[i]->getDays_in_shelter() > max_days) {
            max_days = data[i]->getDays_in_shelter();
            index = i;
        }
    }
    cout << endl << "The oldest resident is " << data[index]->getName() << " with " << data[index]->getDays_in_shelter() << " days in shelter." << endl;
}

//Saves the the edited changes of the file.
void save(const string file, Pet **&data, int &size) {
    ofstream ofs(file);
    if (ofs.fail()) {
        cout << "Failed to open file" << endl;
    } else {
        for (int i = 0; i < size; i++) {
            //This is what Days in shelter gets incremented. Assuming the user will save everytime they edit the file.
            data[i]->setDays_in_shelter(data[i]->getDays_in_shelter() + 1);
            ofs << data[i]->getName() << ","
                << data[i]->getID() << ","
                << data[i]->getDays_in_shelter() << ","
                << data[i]->getColor() << ","
                << data[i]->getAnimal_Type() << "\n";
        }
        cout << endl << "Saved!" << endl;
    }
}




int main() {
    Pet** data = new Pet*[CAP];
    int size = 0;
    string use_program;
    //Intro to the program
    cout << "Welcome User" << endl
         << "This is a program that manages and stores a community of pets!"
         << "Would you like to use the program?" << endl
         << "Enter: yes or no" << endl;
    cin >> use_program;
    if (use_program == "yes") {
        string answer;
        string file;
        cout << "What file would you like to use?" << endl;
        cin >> file;
        load_shelter(file, data, size);

        //Main page of the program where users can interact with it.
        while (true) {
            cout << endl << endl
                 << "What would you like to do?" << endl
                 << "1. Load Shelter" << endl
                 << "2. Add Pet" << endl
                 << "3. Oldest Resident" << endl
                 << "4. Save" << endl
                 << "5. Exit" << endl;
            cin >> answer;
            if (answer == "1") {
                print(data, size);
            } else if (answer == "2") {
                add_pet(data, size);
            } else if (answer == "3") {
                find_oldest(data, size);
            } else if (answer == "4") {
                save(file, data, size);
            } else if (answer == "5") {
                cout << "Thank you for using the program!" << endl;
                break;
            } else {
                cout << "Invalid option. Please try again!" << endl;
            }
        }
    } else {
        cout << "Thank you for using the program!" << endl;
    }

    delete[] data;
    return 0;
}