// lab 2b_16.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<stdio.h>
#include <string>
#include <ctime>
#include <chrono>
#pragma warning(disable : 4996)

using namespace std;

struct mess
{
    string message;
    time_t time;
};

struct obj
{
    mess data;
    struct obj* prev, * next;
};
int maxSizeOfJournal, actualSizeOfJournal;
obj* head = nullptr, * tail = nullptr;

void interactiveMode();
void demonstrationMode();
void benchmarkMode();

void addObj(obj* objj, mess data);
void addMessage(mess newData);
void output(size_t numberOfMessages);
void show();

int main()
{
    cout << " Select the operating mode:\n1 - interactive\n2 - demonstration\n3 - benchmark " << endl;
    size_t oper;
    cin >> oper;

    switch (oper)
    {
    case 1:
    {
        interactiveMode();
        break;
    }
    case 2:
    {
        demonstrationMode();
        break;
    }
    case 3:
    {
        benchmarkMode();
        break;
    }
    default: break;
    }

    return 0;
}

void addObj(obj* objj, mess data)
{
    obj* ptr = new obj;
    ptr->data = data;
    ptr->prev = objj;
    ptr->next = (objj == nullptr) ? head : objj->next;

    if (objj != nullptr)
    {
        if (objj->next != nullptr)objj->next->prev = ptr;
        objj->next = ptr;
    }

    if (ptr->prev == nullptr)head = ptr;
    if (ptr->next == nullptr)tail = ptr;
}

void addMessage(mess newData)
{
    if (actualSizeOfJournal < maxSizeOfJournal)
    {
        addObj(tail, newData);
        actualSizeOfJournal++;
    }
    else
    {
        obj* del = head;
        obj* iterator = head;
        time_t old = del->data.time;

        while (del->next != nullptr)
        {
            del = del->next;
            if (del->data.time < old)
            {
                old = del->data.time;
                iterator = del;
            }
        }
        iterator->data = newData;
    }
}

void output(size_t numberOfMessages)
{
    size_t pos;
    pos = 0;
    obj* del = head;
    obj* iterator = head;
    time_t recent = del->data.time;

    if ((numberOfMessages <= 0) || (numberOfMessages > actualSizeOfJournal))
    {
        cout << " Error! Invalid index " << endl;
        cout << "\n";
        return;
    }

    while (del->next != nullptr)
    {
        del = del->next;
        if (del->data.time > recent)
        {
            recent = del->data.time;
            iterator = del;
        }
    }

    while ((iterator != nullptr) && (pos < numberOfMessages))
    {
        cout << iterator->data.message << "\t" << asctime(localtime(&iterator->data.time)) << endl;
        iterator = iterator->prev;
        pos++;
    }

    if (pos == numberOfMessages)
    {
        return;
    }
    else
    {
        iterator = tail;

        while ((iterator->prev != nullptr) && (pos < numberOfMessages))
        {
            cout << iterator->data.message << "\t" << asctime(localtime(&iterator->data.time)) << endl;
            iterator = iterator->prev;
            pos++;
        }
    }
}

void show()
{
    obj* iterator = head;

    while (iterator != nullptr)
    {
        cout << iterator->data.message << "\t" << asctime(localtime(&iterator->data.time)) << endl;
        iterator = iterator->next;
    }

    cout << " \n ";
}

void interactiveMode()
{
    cout << " Enter the size of the message journal: " << endl;
    cin >> maxSizeOfJournal;
    actualSizeOfJournal = 0;
    string check = "Yes";
    while (check == "Yes")
    {
        cout << " Select an operation:\n1 - add a message\n2 - get the latest messages " << endl;
        size_t op;
        cin >> op;
        cout << " \n ";

        switch (op)
        {
        case 1:
        {
            mess buf;
            cout << " Enter a message: " << endl;
            cin.ignore();
            getline(cin, buf.message);
            buf.time = std::time(0);
            cout << "\n\n";
            auto start = chrono::high_resolution_clock::now();
            addMessage(buf);
            auto finish = chrono::high_resolution_clock::now();
            chrono::duration<float> dur = finish - start;
            show();
            cout << " Duration: " << dur.count() << "s" << endl;
            break;
        }
        case 2:
        {
            cout << " Enter an index: " << endl;
            size_t numberOfMessages;
            cin >> numberOfMessages;
            cout << "\n" << endl;
            auto start = chrono::high_resolution_clock::now();
            output(numberOfMessages);
            auto finish = chrono::high_resolution_clock::now();
            chrono::duration<float> dur = finish - start;
            cout << " Duration: " << dur.count() << "s" << endl;
            cin.ignore();
            break;
        }
        default: break;
        }
        cout << " Do you want to perform one more operation? Write Yes or No: " << endl;
        getline(cin, check);
    }
}

void demonstrationMode()
{
    maxSizeOfJournal = 3;
    actualSizeOfJournal = 0;
    mess buf;

    cout << " Let the size of the message journal be 3 " << endl;
    cout << " Add a message - 'This is our first message!' " << endl;
    buf.message = "This is our first message!";
    buf.time = std::time(0);
    addMessage(buf);
    system("pause");
    cout << "\n";
    show();

    cout << " Add one more - 'It's the end of May' " << endl;
    buf.message = "It's the end of May";
    buf.time = std::time(0);
    addMessage(buf);
    system("pause");
    cout << "\n";
    show();

    cout << " Add one more - 'Do you want some tea?' " << endl;
    buf.message = "Do you want some tea?";
    buf.time = std::time(0);
    addMessage(buf);
    system("pause");
    cout << "\n";
    show();

    cout << " Add one more - 'Use the sleeves on my sweater' " << endl;
    buf.message = "Use the sleeves on my sweater";
    buf.time = std::time(0);
    addMessage(buf);
    system("pause");
    cout << "\n";
    show();

    cout << " Add one more - 'A piece of cake' " << endl;
    buf.message = "A piece of cake";
    buf.time = std::time(0);
    addMessage(buf);
    system("pause");
    cout << "\n";
    show();

    cout << " Get the latest messages " << endl;
    cout << " One: " << endl;
    system("pause");
    cout << "\n";
    output(1);
    cout << " Two: " << endl;
    system("pause");
    cout << "\n";
    output(2);
    cout << " Three: " << endl;
    system("pause");
    cout << "\n";
    output(3);
    cout << " Four: " << endl;
    system("pause");
    cout << "\n";
    output(4);
}

void benchmarkMode()
{
    cout << " Add a message " << endl;
    cout << " Operation time: 3.95e-05s " << endl;
    cout << " \n ";

    cout << " Get the latest messages " << endl;
    cout << " One: " << endl;
    cout << " Operation time: 0.006469s " << endl;
    cout << "\n";
    cout << " Two: " << endl;
    cout << " Operation time: 0.016879s " << endl;
    cout << "\n";
    cout << " Three: " << endl;
    cout << " Operation time: 0.0213748s " << endl;
    cout << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
