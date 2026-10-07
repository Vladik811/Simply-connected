
#include <iostream>
using namespace std;


struct element {
    int data;
    element* next;
};

class list {
    element* head, * tail;
    int size;
public:
    list() {
        head = tail = nullptr;
        size = 0;
    }
    list(int size) {
        for (int i = 0; i < size; i++)
        {
            //add_head(rand() % 101 - 50);
            add_tail(rand() % 101 - 50);
        }
        this->size = size;
    }
    list(const list& obj) {
        head = tail = nullptr;
        size = 0;
        *this = obj;
    }

    int get_size()const { return size; }
    bool is_empty()const { return !size; }

    void add_head(int value) {
        element* new_element = new element;
        new_element->data = value;
        new_element->next = nullptr;

        if (size == 0) {
            head = tail = new_element;
        }
        else {
            new_element->next = head;
            head = new_element;
        }
        size++;
    }

    void add_tail(int value) {
        element* new_element = new element;
        new_element->data = value;
        new_element->next = nullptr;

        if (!size) {
            head = tail = new_element;
        }
        else {
            tail->next = new_element;
            tail = new_element;
        }
        size++;
    }

    void add_position(int pos, int value) {
        if (pos > size) {
            return;
        }

        element* new_element = new element;
        new_element->data = value;
        new_element->next = nullptr;

        if (!pos) {
            add_head(value);
        }
        else {
            element* ptr = head;
            int i = 0;
            while (i++ < pos - 1) {
                ptr = ptr->next;
            }
            new_element->next = ptr->next;
            ptr->next = new_element;

            if (pos == size) {
                tail = new_element;
            }
            size++;
        }

    }


    void delete_head() {
        if (!size) {
            return;
        }

        element* tmp = head;
        head = head->next;
        delete tmp;
        size--;
    }

    void delete_tail() {
        if (!size) {
            return;
        }

        if (head == tail) {
            delete_head();
        }
        else {
            element* tmp = head;
            while (tmp) {
                if (tmp->next == tail) {
                    delete tail;
                    tail = tmp;
                    tail->next = nullptr;
                    break;
                }
                tmp = tmp->next;
            }
            size--;
        }
    }


    void delete_pos(int pos) {
        if (pos > size) {
            return;
        }

        if (!pos) {
            delete_head();
        }
        else {
            element* ptr = head;
            int i = 0;
            while (i++ < pos - 1) {
                ptr = ptr->next;
            }
            element* temp = ptr->next;
            ptr->next = ptr->next->next;

            delete temp;
            size--;
        }
    }

    int search(int value) {
        int pos = 0;
        element* ptr = head;

        while (ptr->data != value) {
            pos++;
            ptr = ptr->next;
            if (pos == size) {
                return -1;
            }
        }
        return pos;
    }

    int search_replace(int value, int new_value) {
        int count = 0;
        element* ptr = head;

        while (ptr != nullptr) {
            if (ptr->data == value) {
                ptr->data = new_value;
                count++;
            }
            ptr = ptr->next;
        }
        return count;
    }

    void delete_search(int value) {
        element* ptr = head;
        element* prev = nullptr;

        while (ptr != nullptr) {
            if (ptr->data == value) {
                element* tmp = ptr;
                ptr = ptr->next;
                if (prev == nullptr) {
                    prev = head;
                }
                else {
                    prev->next = ptr;
                }
                delete tmp;
                size--;
            }
            else {
                prev = ptr;
                ptr = ptr->next;
            }
        }
    }

    void reverse() {
        element* next_el = nullptr;
        element* current_el = head;
        element* prev_el = nullptr;

        while (current_el != nullptr) {
            next_el = current_el->next;
            current_el->next = prev_el;
            prev_el = current_el;
            current_el = next_el;
        }
        head = prev_el;
    }

    void clear() {
        while (head) {
            delete_head();
        }
    }

    void print()const {
        cout << string(100, '=') << "\n";

        element* tmp = head;
        while (tmp) {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }

        cout << "\n" << string(100, '=') << "\n";


    }
    ~list() {
        clear();
    }

    list& operator=(const list& other) {
        if (this == &other) {
            return *this;
        }
        
        delete head;
        delete tail;
        this->head = other.head;
        this->tail = other.tail;
        this->size = other.size;

        return *this;
    }

    int& operator[](int index)const {
        element* number = head;
        for (int i = 0; i < size; i++) {
            if (i == index) {
                return number->data;
            }
            number = number->next;
        }
        return number->data;
    }
};


int menu(const list& l) {
    cout << "==========\n";
    cout << "Count: " << l.get_size() << "\n";
    l.print();
    cout << "------------------------\n";
    cout << "0 - Exit               |\n";
    cout << "1 - Add head           |\n";
    cout << "2 - Add tail           |\n";
    cout << "3 - Delete head        |\n";
    cout << "4 - Delete tail        |\n";
    cout << "5 - Add pos            |\n";
    cout << "6 - Delete pos         |\n";
    cout << "7 - Search             |\n";
    cout << "8 - Search and replace |\n";
    cout << "9 - Search delete      |\n";
    cout << "10 - Clear             |\n";
    cout << "11 - Reverse           |\n";
    cout << "------------------------\n";
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    return choice;
}

int main()
{
    srand(time(NULL));

    list l(5);
    bool is_continue = true;
    while (is_continue) {
        system("cls");
        int choice = menu(l);
        int pos, index, value, new_value, zaglushka;
        switch (choice) {
        case 0:
            is_continue = false;
            break;
        case 1 :
            cout << "Enter value: ";
            cin >> value;
            l.add_head(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            l.add_tail(value);
            break;
        case 3:
            l.delete_head();
            break;
        case 4:
            l.delete_tail();
            break;
        case 5:
            cout << "Enter value: ";
            cin >> value;
            cout << "Enter pos: ";
            cin >> pos;
            l.add_position(pos, value);
            break;
        case 6:
            cout << "Enter pos: ";
            cin >> pos;
            l.delete_pos(pos);
            break;
        case 7:
            cout << "Enter value: ";
            cin >> value;
            cout << l.search(value);
            cin >> zaglushka;
            break;
        case 8:
            cout << "Enter value: ";
            cin >> value;
            cout << "Enter new value: ";
            cin >> new_value;
            l.search_replace(value, new_value);
            break;
        case 9:
            cout << "Enter value: ";
            cin >> value;
            l.delete_search(value);
            break;
        case 10:
            l.clear();
            break;
        case 11:
            l.reverse();
            break;
        }
    }
    
}
