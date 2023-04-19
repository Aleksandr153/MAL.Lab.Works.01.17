#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

#include "pch.h" 
#include<iostream>

//#include<string>
//#include<vector> 

using namespace std;
using namespace System;

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

/*


*/

template <typename T>

class dynamic_array
{
private:
    int m_size;
    int m_capacity;
    T* m_data;

public:
    dynamic_array()
    {
        m_size = 0;
        m_capacity = 0;
        m_data = NULL;
    }

    dynamic_array(const dynamic_array<T>& a)
    {
        m_size = a.m_size;
        m_capacity = m_size;
        m_data = NULL;
        if (m_size != 0)
            m_data = new T[m_size];
        else
            m_data = 0;
        for (int i = 0; i < m_size; ++i)
            m_data[i] = a.m_data[i];
    }

    dynamic_array(int size)
    {
        m_size = size;
        m_capacity = size;
        if (size != 0)
            m_data = new T[size];
        else
            m_data = 0;
    }

    ~dynamic_array()
    {
        if (m_data)
            delete[] m_data;
    }

    void resize(int size)
    {
        if (size > m_capacity)
        {
            int new_capacity = max(size, m_size * 2);
            T* new_data = new T[new_capacity];
            for (int i = 0; i < m_size; ++i)
                new_data[i] = m_data[i];
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
        }
        m_size = size;
    }

    void push_back(T val)
    {
        resize(m_size + 1);
        m_data[m_size - 1] = val;
    }

    int size() const
    {
        return m_size;
    }

    T& operator[] (int i)
    {
        return m_data[i];
    }
};

template<typename T>

ostream& operator << (ostream& out, dynamic_array<T> a)
{
    for (int i = 0; i < a.size(); ++i)
        out << a[i] << " ";
    return out;
}


char search_in_array(dynamic_array<int> array, int number_of_elements, int search_number)
{

    int j = 0;
    int k = 0;
    char awr;

    for (int i = 0; i < number_of_elements; i++) {

        if (search_number == array[i]) {
            j = j + 1;
        }
    };

    if (j > 0) {
        dynamic_array<int> new_arr;
        new_arr.resize(j);

        for (int i = 0; i < number_of_elements; i++) {

            if (search_number == array[i]) {
                new_arr[k] = i;
                k = k + 1;
            }

        };

        for (int k = 0; k < new_arr.size(); k++) {

            cout << "Искомый элемент найден в массиве под номером: " << new_arr[k] << " " << endl;

        }
    }
    else {
        cout << "Искомый элемент найден в массиве не найден" << endl;
        cout << "Хотите добавить элемент в массив? y/n" << endl;
        cin >> awr;
    };

    return awr;

}


int main()
{
    setlocale(LC_ALL, "Russian");

    dynamic_array<int> arr; 
    
    int sizeDA;

    cout << "Введите размер массива: ";
    cin >> sizeDA;                             // получение от пользователя размера массива

    arr.resize(sizeDA);

    for (int i = 0; i < arr.size(); i++)
    {
        printf("Введите значение №%d: ", i);
        cin >> arr[i];
    }

    printf("Значения массива\n");

    for (int i = 0; i < arr.size(); i++) {
        printf("dynamic_array [%d] \n", arr[i]);
    }

    int searchDA;

    cout << "Введите значение, которое вы хотите найти в массиве: " << endl;
    cin >> searchDA;                           // получение от пользователя искомог элемента массива

    char answer;

    answer = search_in_array(arr, arr.size(), searchDA);


    if (answer == 'y' || answer == 'Y') {
        arr.push_back(searchDA);

        printf("Значения массива\n");

        for (int i = 0; i < arr.size(); i++) {
            printf("dynamic_array [%d] \n", arr[i]);
        }
    }
    
    char answer_copy;

    cout << "Хотите сделать копию массива dynamic_array? y/n" << endl;
    cin >> answer_copy;

    if (answer_copy == 'y' || answer_copy == 'Y') {

        dynamic_array<int> arr_copy = arr;

        printf("Значения массива\n");

        for (int i = 0; i < arr_copy.size(); i++) {
            printf("dynamic_array_copy [%d] \n", arr_copy[i]);
        }
    }

    return 0;

}
