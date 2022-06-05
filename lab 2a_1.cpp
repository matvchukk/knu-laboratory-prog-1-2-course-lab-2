// lab 2a_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <stdio.h>
#include <chrono>

using namespace std;

struct coordinates 
{
    float x;
    float y;
    float z;
};

struct obj 
{
    coordinates data;
    struct obj* prev, * next;
};
obj* head = NULL, * tail = NULL;

void interactiveMode();
void demonstrationMode();
void benchmarkMode();

//list
void create_empty();
void append(obj* objj, coordinates bufval);
void insert(coordinates data, size_t nextElId);
void remove(size_t nextElId);
obj* get(size_t nextElId);
void set(coordinates bufval, size_t nextElId);
void length();
void show();

//array
void append(coordinates* array[501], float x, float y, float z);
void insert(coordinates* array[501], float x, float y, float z, int nextElId);
void remove(coordinates* array[501], size_t nextElId);
coordinates get(coordinates* array[501], size_t nextElId); 
void set(coordinates* array[501], float x, float y, float z, size_t nextElId);
void length(coordinates* array[501]);
void show(coordinates* array[501]);

//vector
void append(vector<coordinates>* arrayList, coordinates bufval);
void insert(vector<coordinates>* arrayList, coordinates bufval, size_t nextElId);
void remove(vector<coordinates>* arrayList, size_t nextElId);
coordinates get(vector<coordinates>* arrayList, size_t nextElId);
void set(vector<coordinates>* arrayList, coordinates bufval, size_t nextElId); 
void length(vector<coordinates>* arrayList);
void show(vector<coordinates>* arrayList);

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

//list

void create_empty()
{
    coordinates bufval = { 0, 0, 0 };
    append(tail, bufval);
}

void append(obj* objj, coordinates bufval)
{
    obj* ptr = new obj;
    ptr->data = bufval;
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

void insert(coordinates data, size_t nextElId)
{
    obj* iterator = head;
    size_t pos = 1;
    while ((iterator->next != nullptr) && (pos < nextElId))
    {
        iterator = iterator->next;
        pos++;
    }
    
    if (pos != nextElId)
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        append(iterator->prev, data);
    }
}

void remove(size_t nextElId)
{
    obj* iterator = head;
    size_t pos = 1;
    while ((iterator->next != nullptr) && (pos < nextElId))
    {
        iterator = iterator->next;
        pos++;
    }

    if (pos != nextElId)
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        if (iterator == nullptr) return;
        obj* prev_obj = iterator->prev;
        obj* next_obj = iterator->next;
        delete[] iterator;

        if (prev_obj != nullptr)
        {
            prev_obj->next = next_obj;
        }
        else
        {
            head = next_obj;
            next_obj->prev = nullptr;
        }

        if (next_obj != nullptr)
        {
            next_obj->prev = prev_obj;
        }
        else
        {
            tail = prev_obj;
            prev_obj->next = nullptr;
        }
    }
}

obj* get(size_t nextElId)
{
    obj* iterator = head;
    size_t pos = 1;
    while ((iterator->next != nullptr) && (pos < nextElId))
    {
        iterator = iterator->next;
        pos++;
    }

    if (pos != nextElId)
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        cout << " Your element: " << endl;
        cout << iterator->data.x << "\t" << iterator->data.y << "\t" << iterator->data.z << endl;
        cout << "\n";
        return iterator;
    }
}

void set(coordinates bufval, size_t nextElId)
{
    obj* iterator = head;
    size_t pos = 1;
    while ((iterator->next != nullptr) && (pos < nextElId))
    {
        iterator = iterator->next;
        pos++;
    }

    if (pos != nextElId)
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        iterator->data = bufval;
    }
}

void length()
{
    obj* iterator = head;
    size_t i = 1;

    while (iterator->next != nullptr)
    {
        iterator = iterator->next;
        i++;
    }

    cout << " List length: " << i << endl;
    cout << "\n";
}

void show() 
{
    obj* iterator = head;

    while (iterator != nullptr) 
    {
        cout << iterator->data.x << "\t" << iterator->data.y << "\t" << iterator->data.z << endl;
        iterator = iterator->next;
    }

    cout << " \n ";
}

//array

void append(coordinates* array[501], float x, float y, float z) 
{
    for (int i = 0; i < 501; i++) 
    {
        if (array[i] == nullptr && i + 1 != 501) 
        {
            array[i] = new coordinates;
            array[i]->x = x;
            array[i]->y = y;
            array[i]->z = z;

            array[i + 1] = nullptr;
            return;
        }
    }

    cout << "Error! Out of array's range" << endl;
}

void insert(coordinates* array[501], float x, float y, float z, int nextElId)
{
    if (array[500] == nullptr) 
    {
        cout << "Error! Out of array's range" << endl;
    }
    else 
    {
        coordinates* buf1 = array[nextElId];
        coordinates* buf2;

        for (int i = nextElId+1; i < 501; i++)
        {
            buf2 = array[i];
            array[i] = buf1;
            buf1 = buf2;
        }

        array[nextElId] = new coordinates;
        array[nextElId]->x = x;
        array[nextElId]->y = y;
        array[nextElId]->z = z;
    }
}

void remove(coordinates* array[501], size_t nextElId)
{
    if ((array[500] == nullptr) || (array[nextElId] == nullptr))
    {
        cout << "Error! Out of array's range" << endl;
    }
    else
    {
        if ((nextElId < 0) || (nextElId > 501))
        {
            cout << " Error! Invalid index " << endl;
        }
        else
        {
            coordinates* buf1 = array[nextElId];
            coordinates* buf2;

            for (int i = nextElId; i < 501; i++)
            {
                array[i] = array[i + 1];
            }
        }
    }
}

coordinates get(coordinates* array[501], size_t nextElId)
{
    coordinates get;

    if ((array[500] == nullptr) || (array[nextElId] == nullptr))
    {
        cout << "Error! Out of array's range" << endl;
    }
    else
    {
        if ((nextElId < 0) || (nextElId > 501))
        {
            cout << " Error! Invalid index " << endl;
        }
        else
        {
            get.x = array[nextElId]->x;
            get.y = array[nextElId]->y;
            get.z = array[nextElId]->z;
            cout << " Your element: " << endl;
            cout << get.x << "\t" << get.y << "\t" << get.z << endl;
            cout << "\n";

            return get;
        }
    }
}

void set(coordinates* array[501], float x, float y, float z, size_t nextElId)
{
    if ((array[500] == nullptr) || (array[nextElId] == nullptr))
    {
        cout << "Error! Out of array's range" << endl;
    }
    else
    {
        if ((nextElId < 0) || (nextElId > 501))
        {
            cout << " Error! Invalid index " << endl;
        }
        else
        {
            array[nextElId]->x = x;
            array[nextElId]->y = y;
            array[nextElId]->z = z;
        }
    }
}

void length(coordinates* array[501])
{
    size_t i = 0;
    size_t length = 0;

    while (array[i] != nullptr)
    {
        length++;
        i++;
    }

    cout << " Array length: " << length << endl;
    cout << "\n";
}

void show(coordinates* array[501])
{
    for (size_t i = 0; i < 501; i++)
    {
        if (array[i] == nullptr)
        {
            break;
        }
        cout << array[i]->x << "\t";
        cout << array[i]->y << "\t";
        cout << array[i]->z << endl;
    }
    cout << "\n";
}

//vector

void append(vector<coordinates>* arrayList, coordinates bufval)
{
    (*arrayList).push_back(bufval);
}

void insert(vector<coordinates>* arrayList, coordinates bufval, size_t nextElId)
{
    if ((nextElId < 0) || (nextElId > (*arrayList).size() - 1))
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        vector<coordinates>::iterator iter = (*arrayList).begin();
        (*arrayList).insert(iter + nextElId, bufval);
    }
}

void remove(vector<coordinates>* arrayList, size_t nextElId)
{
    if ((nextElId < 0) || (nextElId > (*arrayList).size() - 1))
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        vector<coordinates>::iterator iter = (*arrayList).begin();
        (*arrayList).erase(iter + nextElId);
    }
}

coordinates get(vector<coordinates>* arrayList, size_t nextElId)
{
    coordinates get;
    if ((nextElId < 0) || (nextElId > (*arrayList).size() - 1))
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        get = (*arrayList)[nextElId];
        cout << " Your element: " << endl;
        cout << get.x << "\t" << get.y << "\t" << get.z << endl;
        cout << "\n";

        return get;
    }

}

void set(vector<coordinates>* arrayList, coordinates bufval, size_t nextElId)
{
    if ((nextElId < 0) || (nextElId > (*arrayList).size() - 1))
    {
        cout << " Error! Invalid index " << endl;
    }
    else
    {
        (*arrayList)[nextElId] = bufval;
    }
}

void length(vector<coordinates>* arrayList)
{
    cout << " Vector length: " << (*arrayList).size() << endl;
    cout << "\n";
}

void show(vector<coordinates>* arrayList)
{
    for (size_t i = 0; i < (*arrayList).size(); i++)
    {
        cout << (*arrayList)[i].x << "\t" << (*arrayList)[i].y << "\t" << (*arrayList)[i].z << "\t" << endl;
    }
    cout << " \n ";
}

void interactiveMode()
{
    coordinates* array[501];
    array[0] = nullptr;
    coordinates bufval;
    vector<coordinates> arrayList;
    float x, y, z;
    size_t filling, k;
    obj* takeL;
    coordinates takeA;
    coordinates takeV;

    string check = "Yes";
    while (check == "Yes")
    {
        cout << " Select an operation:\n1 - create an empty list\n2 - add an item to the end of the list\n3 - insert an element before an element with the index\n4 - delete the element with the index\n5 - get the element with the index\n6 - set the element with the index\n7 - the length of the list " << endl;
        size_t op;
        cin >> op;
        cout << " \n ";

        cout << " Select an type of realization:\n1 - list\n2 - array\n3 - vector " << endl;
        size_t tp;
        cin >> tp;
        cout << " \n ";

        if (op == 2 || op == 3 || op == 6)
        {
            cout << " Choose a data entry method:\n1 - self-filling\n2 - random filling " << endl;
            cin >> filling;
            if (tp == 1 || tp == 3)
            {
                switch (filling)
                {
                case 1:
                {
                    cout << " Enter x: ";
                    cin >> bufval.x;
                    cout << " Enter y: ";
                    cin >> bufval.y;
                    cout << " Enter z: ";
                    cin >> bufval.z;
                    cout << "\n" << endl;
                    break;
                }
                case 2:
                {
                    bufval.x = static_cast<float>(-500 + rand() % 1000);
                    cout << " x = " << bufval.x;
                    bufval.y = static_cast<float>(-500 + rand() % 1000);
                    cout << " y = " << bufval.y;
                    bufval.z = static_cast<float>(-500 + rand() % 1000);
                    cout << " z = " << bufval.z;
                    cout << "\n" << endl;
                    break;
                }
                default: break;
                }
            }
            else if (tp == 2)
            {
                switch (filling)
                {
                case 1:
                {
                    cout << " Enter x: ";
                    cin >> x;
                    cout << " Enter y: ";
                    cin >> y;
                    cout << " Enter z: ";
                    cin >> z;
                    cout << "\n" << endl;
                    break;
                }
                case 2:
                {
                    x = static_cast<float>(-500 + rand() % 1000);
                    cout << " x = " << x;
                    y = static_cast<float>(-500 + rand() % 1000);
                    cout << " y = " << y;
                    z = static_cast<float>(-500 + rand() % 1000);
                    cout << " z = " << z;
                    cout << "\n" << endl;
                    break;
                }
                default: break;
                }
            }
        }

        if (op == 3 || op == 4 || op == 5 || op == 6)
        {
            cout << " Enter an index: " << endl;
            cin >> k;
            cout << "\n" << endl;
        }

        switch (op)
        {
        case 1:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                create_empty();
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show();
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                append(array, 0, 0, 0);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(array);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                bufval = { 0, 0, 0 };
                auto start = chrono::high_resolution_clock::now();
                append(&arrayList, bufval);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(&arrayList);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            return;
        }
        case 2:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                append(tail, bufval);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show();
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                append(array, x, y, z);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(array);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                auto start = chrono::high_resolution_clock::now();
                append(&arrayList, bufval);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(&arrayList);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            break;
        }
        case 3:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                insert(bufval, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show();
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                insert(array, x, y, z, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(array);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                auto start = chrono::high_resolution_clock::now();
                insert(&arrayList, bufval, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(&arrayList);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            break;
        }
        case 4:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                remove(k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show();
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                remove(array, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(array);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                auto start = chrono::high_resolution_clock::now();
                remove(&arrayList, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(&arrayList);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            break;
        }
        case 5:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                takeL = get(k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                takeA = get(array, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                auto start = chrono::high_resolution_clock::now();
                takeV = get(&arrayList, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            break;
        }
        case 6:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                set(bufval, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show();
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                set(array, x, y, z, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(array);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                auto start = chrono::high_resolution_clock::now();
                set(&arrayList, bufval, k);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                show(&arrayList);
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            break;
        }
        case 7:
        {
            switch (tp)
            {
            case 1:
            {
                auto start = chrono::high_resolution_clock::now();
                length();
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 2:
            {
                auto start = chrono::high_resolution_clock::now();
                length(array);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            case 3:
            {
                auto start = chrono::high_resolution_clock::now();
                length(&arrayList);
                auto finish = chrono::high_resolution_clock::now();
                chrono::duration<float> dur = finish - start;
                cout << " Duration: " << dur.count() << "s" << endl;
                break;
            }
            default: break;
            }
            break;
        }
        default: break;
        }
        cout << " Do you want to perform one more operation? Write Yes or No: " << endl;
        cin >> check;
        cin.ignore();
    }

}

void demonstrationMode()
{
    coordinates* array[501];
    array[0] = nullptr;
    coordinates bufval;
    vector<coordinates> arrayList;
    float x, y, z;
    size_t filling, k;
    obj* takeL;
    coordinates takeA;
    coordinates takeV;

    cout << " Create an empty list " << endl;
    cout << " List: " << endl;
    system("pause");
    create_empty();
    show();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    append(array, 0, 0, 0);
    show(array);
    remove(array, 0);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    bufval = { 0, 0, 0 };
    append(&arrayList, bufval);
    show(&arrayList);
    remove(&arrayList, 0);
    cout << " \n\n ";

    cout << " Add an item to the end of the list " << endl;
    cout << " List: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    append(tail, bufval);
    remove(1);
    show();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << x;
    y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << y;
    z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << z;
    cout << "\n" << endl;
    system("pause");
    append(array, x, y, z);
    show(array);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    append(&arrayList, bufval);
    show(&arrayList);
    cout << " \n\n ";

    cout << " Add one more " << endl;
    cout << " List: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    append(tail, bufval);
    show();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << x;
    y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << y;
    z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << z;
    cout << "\n" << endl;
    system("pause");
    append(array, x, y, z);
    show(array);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    append(&arrayList, bufval);
    show(&arrayList);
    cout << " \n\n ";

    cout << " Insert an element before an element with the index (For example, the index is 1) " << endl;
    cout << " List: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    insert(bufval, 1);
    show();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << x;
    y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << y;
    z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << z;
    cout << "\n" << endl;
    system("pause");
    insert(array, x, y, z, 1);
    show(array);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    insert(&arrayList, bufval, 1);
    show(&arrayList);
    cout << " \n\n ";

    cout << " Delete the element with the index (For example, the index is 1) " << endl;
    cout << " List: " << endl;
    system("pause");
    remove(1);
    show();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    remove(array, 1);
    show(array);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    remove(&arrayList, 1);
    show(&arrayList);
    cout << " \n\n ";

    cout << " Get the element with the index (For example, the index is 1) " << endl;
    cout << " List: " << endl;
    system("pause");
    takeL = get(1);
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    takeA = get(array, 1);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    takeV = get(&arrayList, 1);
    cout << " \n\n ";

    cout << " Set the element with the index (For example, the index is 1) " << endl;
    cout << " List: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    set(bufval, 1);
    show();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << x;
    y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << y;
    z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << z;
    cout << "\n" << endl;
    system("pause");
    set(array, x, y, z, 1);
    show(array);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    bufval.x = static_cast<float>(-500 + rand() % 1000);
    cout << " x = " << bufval.x;
    bufval.y = static_cast<float>(-500 + rand() % 1000);
    cout << " y = " << bufval.y;
    bufval.z = static_cast<float>(-500 + rand() % 1000);
    cout << " z = " << bufval.z;
    cout << "\n" << endl;
    system("pause");
    set(&arrayList, bufval, 1);
    show(&arrayList);
    cout << " \n\n ";

    cout << " The length of the list " << endl;
    cout << " List: " << endl;
    system("pause");
    length();
    cout << " \n\n ";
    cout << " Array: " << endl;
    system("pause");
    length(array);
    cout << " \n\n ";
    cout << " Vector: " << endl;
    system("pause");
    length(&arrayList);
    cout << " \n\n ";
}

void benchmarkMode()
{
    cout << " Create an empty list " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 2.47e-05s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 6.4e-06s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 1.93e-05s " << endl;
    cout << " \n ";

    cout << " Add an item to the end of the list " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 5.3e-06s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 7.4e-06s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 1.35e-05s " << endl;
    cout << " \n";

    cout << " Insert an element before an element with the index " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 9.6e-06s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 1.36e-05s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 0.0001864s " << endl;
    cout << " \n";

    cout << " Delete the element with the index " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 8.2e-06s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 5.7e-06s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 1.67e-05s " << endl;
    cout << " \n";

    cout << " Get the element with the index " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 0.0092154s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 0.0103505s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 0.0093538s " << endl;
    cout << " \n";

    cout << " Set the element with the index " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 2.2e-06s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 1.8e-06s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 2.3e-06s " << endl;
    cout << " \n";

    cout << " The length of the list " << endl;
    cout << " List: " << endl;
    cout << " Operation time: 0.0059434s " << endl;
    cout << " \n ";
    cout << " Array: " << endl;
    cout << " Operation time: 0.0054444s " << endl;
    cout << " \n";
    cout << " Vector: " << endl;
    cout << " Operation time: 0.0053568s " << endl;
    cout << " \n";
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
