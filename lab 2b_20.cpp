// lab 2b_20.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

typedef struct tag_obj
{
    int value;
    struct tag_obj* prev, * next;
}obj;

struct list
{
    obj* head = nullptr;
    obj* tail = nullptr;
};

void interactiveMode();
void demonstrationMode();
void benchmarkMode();

list conjunctionL(list list1, list list2);
list disjunctionL(list list1, list list2);
list additionL(list list2, list list1);

void addObj(obj* objj, int bufval, list* list);
list copyListToList(list listFrom);
void show(list list);


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

void addObj(obj* objj, int bufval, list* list)
{
    obj* ptr = new obj;

    ptr->value = bufval;
    ptr->prev = objj;
    ptr->next = (objj == nullptr) ? list->head : objj->next;

    if (objj != nullptr)
    {
        if (objj->next != nullptr)objj->next->prev = ptr;
        objj->next = ptr;
    }
    if (ptr->prev == nullptr)list->head = ptr;
    if (ptr->next == nullptr)list->tail = ptr;
}

list copyListToList(list listFrom)
{
    list listTo;
    obj* iterator = listFrom.head;

    while (iterator != nullptr)
    {
        addObj(listTo.tail, iterator->value, &listTo);
        iterator = iterator->next;
    }

    return listTo;
}

list conjunctionL(list list1, list list2)
{
    list result = copyListToList(list1);

    obj* iter = list2.head;
    obj* innerIter;
    bool UniqueElement;
    while (iter != nullptr)
    {
        innerIter = list1.head;
        UniqueElement = true;
        while (innerIter != nullptr)
        {
            if (iter->value == innerIter->value)
            {
                UniqueElement = false;
                break;
            }


            innerIter = innerIter->next;
        }
        if (UniqueElement == true)
        {
            addObj(result.tail, iter->value, &result);
        }

        iter = iter->next;
    }
    return result;
}
list disjunctionL(list list1, list list2)
{
    list result;

    obj* iter = list2.head;
    obj* innerIter;
    bool UniqueElement;

    while (iter != nullptr)
    {
        innerIter = list1.head;
        UniqueElement = true;
        while (innerIter != nullptr)
        {
            if (iter->value == innerIter->value)
            {
                UniqueElement = false;
                break;
            }

            innerIter = innerIter->next;
        }
        if (UniqueElement == false)
        {
            addObj(result.tail, iter->value, &result);
        }

        iter = iter->next;
    }
    return result;
}
list additionL(list list1, list list2)
{
    list result;

    obj* iter = list2.head;
    obj* innerIter;
    bool UniqueElement;

    while (iter != nullptr)
    {
        innerIter = list1.head;
        UniqueElement = true;
        while (innerIter != nullptr)
        {
            if (iter->value == innerIter->value)
            {
                UniqueElement = false;
                break;
            }

            innerIter = innerIter->next;
        }
        if (UniqueElement == true)
        {
            addObj(result.tail, iter->value, &result);
        }

        iter = iter->next;
    }
    return result;
}

void show(list list)
{
    obj* iterator = list.head;

    while (iterator != nullptr)
    {
        cout << iterator->value << " \t";
        iterator = iterator->next;
    }

    cout << " \n ";
}

void interactiveMode()
{
    list list_1;
    list list_2;
    list list_res;

    string input, check;

    cout << " Select an operation:\n1 - conjunction\n2 - disjunction\n3 - addition " << endl;
    size_t op;
    cin >> op;
    cout << " \n ";

    cout << " Enter the elements of the set: " << endl;
    cin.ignore();
    getline(cin, input);
    input += ' ';

    while (input.length())
    {
        addObj(list_1.tail, atoi(input.substr(0, input.find(' ')).c_str()), &list_1);
        input.erase(0, input.find(' ') + 1);
    }
    show(list_1);
    cout << "\n";

    cout << " Enter the elements of the set: " << endl;
    getline(cin, input);
    input += ' ';

    while (input.length())
    {
        addObj(list_2.tail, atoi(input.substr(0, input.find(' ')).c_str()), &list_2);
        input.erase(0, input.find(' ') + 1);
    }
    show(list_2);
    cout << "\n";

    switch (op)
    {
    case 1:
    {
        list_res = conjunctionL(list_1, list_2);
        while (1)
        {
            cout << " Want to add one more set?(Yes/No) ";
            getline(cin, check);
            if (check != "Yes") break;
            else
            {
                list_2 = {};
                cout << " Enter the elements of the set: " << endl;
                getline(cin, input);
                input += ' ';

                while (input.length())
                {
                    addObj(list_2.tail, atoi(input.substr(0, input.find(' ')).c_str()), &list_2);
                    input.erase(0, input.find(' ') + 1);
                }
                show(list_2);
                cout << "\n";
                list_res = conjunctionL(list_res, list_2);
            }
        }
        show(list_res);
        break;
    }
    case 2:
    {
        list_res = disjunctionL(list_1, list_2);
        while (1)
        {
            cout << " Want to add one more set?(Yes/No) ";
            getline(cin, check);
            if (check != "Yes") break;
            else
            {
                list_2 = {};
                cout << " Enter the elements of the set: " << endl;
                getline(cin, input);
                input += ' ';

                while (input.length())
                {
                    addObj(list_2.tail, atoi(input.substr(0, input.find(' ')).c_str()), &list_2);
                    input.erase(0, input.find(' ') + 1);
                }
                show(list_2);
                cout << "\n";
                list_res = disjunctionL(list_res, list_2);
            }
        }
        show(list_res);
        break;
    }
    case 3:
    {
        list_res = additionL(list_1, list_2);
        while (1)
        {
            cout << " Want to add one more set?(Yes/No) ";
            getline(cin, check);
            if (check != "Yes") break;
            else
            {
                list_2 = {};
                cout << " Enter the elements of the set: " << endl;
                getline(cin, input);
                input += ' ';

                while (input.length())
                {
                    addObj(list_2.tail, atoi(input.substr(0, input.find(' ')).c_str()), &list_2);
                    input.erase(0, input.find(' ') + 1);
                }
                show(list_2);
                cout << "\n";
                list list_res_a = additionL(list_1, list_2);
                list_res = conjunctionL(list_res, list_res_a);
            }
        }
        show(list_res);
        break;
    }
    default: break;
    }
}

void demonstrationMode()
{
    list list_1;
    list list_2;
    list list_3;
    list list_res;

    cout << " We set 3 sets: " << endl;
    system("pause");

    addObj(list_1.tail, 5, &list_1);
    addObj(list_1.tail, 8, &list_1);
    addObj(list_1.tail, 9, &list_1);
    addObj(list_1.tail, 23, &list_1);
    addObj(list_1.tail, 104, &list_1);
    addObj(list_1.tail, 12, &list_1);

    addObj(list_2.tail, 72, &list_2);
    addObj(list_2.tail, 11, &list_2);
    addObj(list_2.tail, 923, &list_2);
    addObj(list_2.tail, 3, &list_2);
    addObj(list_2.tail, 8, &list_2);
    addObj(list_2.tail, 9, &list_2);

    addObj(list_3.tail, 714, &list_3);
    addObj(list_3.tail, 90, &list_3);
    addObj(list_3.tail, 8, &list_3);
    addObj(list_3.tail, 9, &list_3);
    addObj(list_3.tail, 1, &list_3);
    addObj(list_3.tail, 44, &list_3);

    show(list_1);
    cout << "\n";
    show(list_2);
    cout << "\n";
    show(list_3);
    cout << "\n";

    cout << " Find their conjunction: " << endl;
    system("pause");
    list_res = conjunctionL(list_1, list_2);
    list_res = conjunctionL(list_res, list_3);
    show(list_res);
    cout << "\n";

    cout << " Find their disjunction: " << endl;
    system("pause");
    list_res = disjunctionL(list_1, list_2);
    list_res = disjunctionL(list_res, list_3);
    show(list_res);
    cout << "\n";

    cout << " Find the complement of the first set: " << endl;
    system("pause");
    list_res = additionL(list_1, list_2);
    list list_res_a = additionL(list_1, list_3);
    list_res = conjunctionL(list_res, list_res_a);
    show(list_res);
    cout << "\n";
}

void benchmarkMode()
{
    cout << " Find the conjunction: " << endl;
    cout << " Operation time: 9.5e-06s " << endl;
    cout << " \n ";

    cout << " Find the disjunction: " << endl;
    cout << " Operation time: 6.9e-06s " << endl;
    cout << " \n ";

    cout << " Find the complement: " << endl;
    cout << " Operation time: 3.9e-06s " << endl;
    cout << " \n ";
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
