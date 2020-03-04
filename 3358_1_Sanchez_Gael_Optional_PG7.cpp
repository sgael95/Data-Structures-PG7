//      Roster Number: 37
//
//      Author : (Gael Sanchez)
//      Due Date: 04/30/18
//      Programming Assignment Number 7 Optional
//
//      Spring 2018 - CS 3358 - 261
//
//      Instructor: Husain Gholoom
//
//      The program starts by creating an empty hash table and populating half of the table
//       with randoom integer values between 125 and 425. Following that the program then
//       displays a list of options for the user to choose from such as adding, searching or
//       or deleting an integer. The program then takes the input and runs the correct function.

#include<iostream>

#include<cstdlib>
#include <ctime>

#ifndef HASHCLASS_H_
#define HASHCLASS_H_

using namespace std;


class Hash {
public:
    int static hashCount;
    int static collisions;
    Hash();
    void insert(int);
    void search(int);
    int hash(int);
    int reHash(int);
    void Delete(int);
    void Display();
    void Populate();
    int getHashCount();
    int getCollisionCount();
private:
    int hash_pos;
    int array[40];
};

int Hash::hashCount = 0;
int Hash::collisions = 0;

Hash::Hash(){
    for(int i=0; i < 30; i++)
        array[i] = '*';
    //hashCount = 0;
    //collisions = 0;
}

void Hash::insert(int data){
    hashCount++;
    int count = 0;
    hash_pos = hash(data);
    if(hash_pos > 30) {
        hash_pos = 0;
    }
    while(array[hash_pos] != '*') {
        hash_pos = reHash(hash_pos + 1);
        collisions++;
        count++;
        if(count >= 30) {
            cout <<"Memory Full!!No space is available for storage";
            break;
        }
    }
    if(array[hash_pos] == '*') {
        array[hash_pos] = data;
    }
}

int Hash::hash(int key){
    return key%30;
}

int Hash::reHash(int key) {
    return (key+1)%30;
}

void Hash::search(int data) {
    int key = data;
    int i = hash(data);
    bool isFound = false;
    while(isFound == false) {
        if(array[i] == data){
            isFound = true;
        }
        else if(i==30 && isFound == false || array[i] == '*') {
            break;
        } else {
            i = reHash(i++);
        }
    }
    if(isFound) {
        cout << "\nThe number " << data << " was found in element " << i << endl;
    }else{
        cout <<"\nNo record found!!" << endl;
    }
}

void Hash::Delete(int data){
    int key = data;
    int i = hash(data);
    bool isFound = false;
    while(isFound == false) {
        if(array[i] == data){
            isFound = true;
        }
        else if(i==30 && isFound == false || array[i] == '*') {
            break;
        } else {
            i = reHash(key++);
        }
    }
    if(isFound) {
        array[i] = '*';
        cout << "The key is deleted" << endl;
    }else{
        cout << "No key is Found!!";
    }
}

void Hash::Display(){

    for(int i=0; i<30; i++){
        if(i==15) {
            cout << endl;
        }
        if(array[i] == '*')
            cout << "*  ";
        else {
            cout << array[i] << " ";
        }
    }
}

void Hash::Populate(){
    int num;
    srand(time(NULL));
    for(int i=0; i<15;i++) {
        num = rand() % 300 + 125;
        insert(num);
    }
}

int Hash::getHashCount(){
    return hashCount;
}

int Hash::getCollisionCount(){
    return collisions;
}
#endif // HASHCLASS_H_

int main() {

    bool done;
    char answer;
    Hash h;
    int searchValue;
    int insertValue;
    int deleteValue;

    cout << "\n\nWelcome to my Hashing Program" << endl << endl;
    cout << "-----------------------------" << endl << endl;
    cout << "1.  Creates an integer array of size 30. Assigning * to each\n";
    cout << "    location in the array indicating that the array is empty.\n";
    cout << "2.  Populates half of the array with random integer values\n";
    cout << "    between 125 and 425 inclusive.\n";
    cout << "3.  If a collision occurs, linear probing will find the next\n";
    cout << "    available psoition / location.\n";
    cout << "4.  The generated array will be displayed in 2 lines.\n";
    cout << "    Each line contains 15 numbers separated by 2 spaces.\n";
    cout << "\nGenerated Array\n";
    cout << "-----------------------------" << endl << endl;

    h.Populate();
    h.Display();


    do {

        cout << "\n\nSelect from the following menu options\n\n";
        cout << "A.  Display the generated array.\n";
        cout << "B.  Search for a number (between 125-425) in the array.\n";
        cout << "C.  Insert a new number (between 125-425) in the array.\n";
        cout << "D.  Delete a number (between 125-425) from the array.\n";
        cout << "X.  End the program.\n\n";
        cout << "Select your option: ";

        try {
            cin >> answer;
            if(!cin) {
                cin.clear();
                cin.ignore();
                throw "*** Invalid Option ***\n";
            }
        } catch(const char* msg) {
                cout << endl << msg << endl;
                done = false;
            }

        switch(answer){
            case 'A': {
                cout << "\nDisplaying the generated array.\n\n";
                h.Display();
                done = false;
            } break;
            case 'a': {
                cout << "\nDisplaying the generated array.\n\n";
                h.Display();
            }break;
            case 'b': {
                cout << "\nEnter a number you want to search (between 125-425): ";
                try {
                    cin >> searchValue;
                    if(!cin) {
                        cin.clear();
                        cin.ignore();
                        throw "*** Invalid Value ***\n";
                    }
                } catch (const char* msg) {
                    cout << endl << msg << endl;
                    done = false;
                }
                h.search(searchValue);

            }break;
            case 'B': {
                 cout << "\nEnter a number you want to search (between 125-425): ";
                try {
                    cin >> searchValue;
                    if(!cin) {
                        cin.clear();
                        cin.ignore();
                        throw "*** Invalid Value ***\n";
                    }
                } catch (const char* msg) {
                    cout << endl << msg << endl;
                    done = false;
                }
                h.search(searchValue);

            } break;
            case 'C': {
                cout << "\nEnter a number you want to insert between (125-425): ";
                try {
                    cin >> insertValue;
                    if(!cin) {
                        cin.clear();
                        cin.ignore();
                        throw "*** Invalid Value ***\n";
                    }
                } catch (const char* msg) {
                    cout << endl << msg << endl;
                    done = false;
                }
                if(insertValue < 125 || insertValue > 425){
                    cout << "*** Invalid Number ***";
                }
                h.insert(insertValue);

            } break;
            case 'c': {
                cout << "\nEnter a number you want to insert between (125-425): ";
                try {
                    cin >> insertValue;
                    if(!cin) {
                        cin.clear();
                        cin.ignore();
                        throw "*** Invalid Value ***\n";
                    }
                } catch (const char* msg) {
                    cout << endl << msg << endl;
                    done = false;
                }
                if(insertValue < 125 || insertValue > 425){
                    cout << "*** Invalid Number ***";
                }
                h.insert(insertValue);

            } break;
            case 'D': {
                cout << "\nEnter a number you want to delete (between 125-425): ";
                try{
                    cin >> deleteValue;
                    if(!cin) {
                        cin.clear();
                        cin.ignore();
                        throw "*** Invalid Value ***";
                    }
                } catch (const char* msg) {
                    cout << endl << msg << endl;
                    done = false;
                }
                if(deleteValue < 125 || deleteValue > 425) {
                    cout << "*** Invalid Number ***";
                }
                h.Delete(deleteValue);

            } break;
            case 'd': {
                cout << "\nEnter a number you want to delete (between 125-425): ";
                try{
                    cin >> deleteValue;
                    if(!cin) {
                        cin.clear();
                        cin.ignore();
                        throw "*** Invalid Value ***";
                    }
                } catch (const char* msg) {
                    cout << endl << msg << endl;
                    done = false;
                }
                if(deleteValue < 125 || deleteValue > 425) {
                    cout << "*** Invalid Number ***";
                }
                h.Delete(deleteValue);


            } break;
            case 'X': {
                cout << "\nThe number of times each position / location is hashed when adding an element is the array is " << h.getHashCount();
                cout << "\n\nThe number of linear probes when each number is hashed and collision\noccurred\n";
                cout << "when adding an element in the array is " << h.getCollisionCount() << endl;
                cout << "\nThis Hashing Program was Implemented by" << endl;
                cout << "Gael Sanchez - April 30, 2018";
                return 0;
            }break;
            case 'x': {
                cout << "\nThe number of times each position / location is hashed when adding an element is the array is " << h.getHashCount();
                cout << "\n\nThe number of linear probes when each number is hashed and collision\noccurred\n";
                cout << "when adding an element in the array is " << h.getCollisionCount() << endl;
                cout << "\nThis Hashing Program was Implemented by" << endl;
                cout << "Gael Sanchez - April 30, 2018";
                return 0;
            }break;
            default: cout << "*** Invalid Option ***\n";
        }
        done = false;

    }while(done != true);


    return 0;
}
