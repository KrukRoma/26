#include <iostream>
using namespace std;

template <typename T>
class List 
{
private:
    struct Node 
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head; 
    Node* tail; 
    size_t size; 

public:
    List() : head(nullptr), tail(nullptr), size(0) {}

    ~List() 
    {
        clear();
    }

    void append(const T& value) 
    {
        Node* newNode = new Node(value);
        if (tail) 
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else 
        {
            head = tail = newNode;
        }
        size++;
    }

    T& operator[](size_t index) 
    {
        if (index >= size) 
        {
            cerr << "Index out of range" << endl;
            exit(1); 
        }
        Node* current = head;
        for (size_t i = 0; i < index; i++) 
        {
            current = current->next;
        }
        return current->data;
    }

    void deleteByValue(const T& value) 
    {
        Node* current = head;
        while (current) 
        {
            if (current->data == value) 
            {
                Node* toDelete = current;
                if (current->prev) 
                {
                    current->prev->next = current->next;
                }
                else 
                {
                    head = current->next;
                }
                if (current->next) 
                {
                    current->next->prev = current->prev;
                }
                else 
                {
                    tail = current->prev;
                }
                Node* nextNode = current->next;
                delete toDelete;
                current = nextNode;
                size--;
            }
            else 
            {
                current = current->next;
            }
        }
    }

    void removeDuplicates() 
    {
        Node* current = head;
        while (current) 
        {
            Node* runner = current->next;
            while (runner) 
            {
                if (current->data == runner->data) 
                {
                    Node* toDelete = runner;
                    if (runner->prev) 
                    {
                        runner->prev->next = runner->next;
                    }
                    else 
                    {
                        head = runner->next;
                    }
                    if (runner->next) 
                    {
                        runner->next->prev = runner->prev;
                    }
                    else 
                    {
                        tail = runner->prev;
                    }
                    runner = runner->next;
                    delete toDelete;
                    size--;
                }
                else 
                {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    T min() const 
    {
        if (!head) 
        {
            cerr << "List is empty" << endl;
            exit(1); 
        }
        Node* current = head;
        T minValue = current->data;
        while (current) 
        {
            if (current->data < minValue) 
            {
                minValue = current->data;
            }
            current = current->next;
        }
        return minValue;
    }

    T max() const 
    {
        if (!head) 
        {
            cerr << "List is empty" << endl;
            exit(1); 
        }
        Node* current = head;
        T maxValue = current->data;
        while (current) 
        {
            if (current->data > maxValue) 
            {
                maxValue = current->data;
            }
            current = current->next;
        }
        return maxValue;
    }

    void printReverse() const 
    {
        Node* current = tail;
        while (current) 
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void clear() 
    {
        Node* current = head;
        while (current) 
        {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    size_t getSize() const 
    {
        return size;
    }

    void print() const 
    {
        Node* current = head;
        while (current) 
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() 
{
    List<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);
    list.append(2);
    list.append(3);

    cout << "Initial list: ";
    list.print();

    list[2] = 42;
    cout << "List after changing value at index 2: ";
    list.print();

    list.deleteByValue(2);
    cout << "List after deleting value 2: ";
    list.print();

    list.removeDuplicates();
    cout << "List after removing duplicates: ";
    list.print();

    cout << "Minimum value: " << list.min() << endl;
    cout << "Maximum value: " << list.max() << endl;

    cout << "List in reverse order: ";
    list.printReverse();
}
