#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* head = NULL;

void add(int x) {
    Node* n = new Node;
    n->data = x;
    n->next = NULL;

    if (head == NULL) {
        head = n;
    } else {
        Node* t = head;
        while (t->next != NULL)
            t = t->next;
        t->next = n;
    }
}

void show() {
    Node* t = head;
    if (!t) {
        cout << "List is empty" << endl;
        return;
    }
    while (t) {
        cout << t->data << " ";
        t = t->next;
    }
    cout << endl;
}

void modify(int oldVal, int newVal) {
    Node* t = head;
    while (t) {
        if (t->data == oldVal) {
            t->data = newVal;
            cout << "Value modified" << endl;
            return;
        }
        t = t->next;
    }
    cout << "Value not found" << endl;
}

void removeNode(int val) {
    if (!head) {
        cout << "List is empty" << endl;
        return;
    }
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Node deleted" << endl;
        return;
    }
    Node* t = head;
    while (t->next && t->next->data != val)
        t = t->next;

    if (t->next) {
        Node* temp = t->next;
        t->next = t->next->next;
        delete temp;
        cout << "Node deleted" << endl;
    } else {
        cout << "Value not found" << endl;
    }
}

int* toArray(int& n) {
    n = 0;
    Node* t = head;
    while (t) {
        n++;
        t = t->next;
    }
    int* a = new int[n];
    t = head;
    for (int i = 0; i < n; i++) {
        a[i] = t->data;
        t = t->next;
    }
    return a;
}

void merge(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = a[l + i];
    for (int j = 0; j < n2; j++) R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        a[k++] = (L[i] < R[j]) ? L[i++] : R[j++];

    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int part(int a[], int l, int h) {
    int p = a[h];
    int i = l - 1;
    for (int j = l; j < h; j++) {
        if (a[j] < p) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[h]);
    return i + 1;
}

void quickSort(int a[], int l, int h) {
    if (l < h) {
        int p = part(a, l, h);
        quickSort(a, l, p - 1);
        quickSort(a, p + 1, h);
    }
}

int bSearch(int a[], int n, int x) {
    int l = 0, h = n - 1;
    while (l <= h) {
        int m = (l + h) / 2;
        if (a[m] == x)
            return m;
        else if (a[m] < x)
            l = m + 1;
        else
            h = m - 1;
    }
    return -1;
}

int main() {
    int ch, x, y;

    while (true) {
        cout << "1. Add" << endl;
        cout << "2. Show" << endl;
        cout << "3. Modify" << endl;
        cout << "4. Delete" << endl;
        cout << "5. Merge Sort" << endl;
        cout << "6. Quick Sort" << endl;
        cout << "7. Binary Search" << endl;
        cout << "8. Exit" << endl;
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) {
            cout << "Enter value: ";
            cin >> x;
            add(x);
        } else if (ch == 2) {
            show();
        } else if (ch == 3) {
            cout << "Enter value to modify: ";
            cin >> x;
            cout << "Enter new value: ";
            cin >> y;
            modify(x, y);
        } else if (ch == 4) {
            cout << "Enter value to delete: ";
            cin >> x;
            removeNode(x);
        } else if (ch == 5 || ch == 6) {
            int n;
            int* a = toArray(n);
            if (n == 0) {
                cout << "List is empty" << endl;
                continue;
            }
            if (ch == 5) {
                mergeSort(a, 0, n - 1);
                cout << "Merge Sort: ";
            } else {
                quickSort(a, 0, n - 1);
                cout << "Quick Sort: ";
            }
            for (int i = 0; i < n; i++)
                cout << a[i] << " ";
            cout << endl;
            delete[] a;
        } else if (ch == 7) {
            int n;
            int* a = toArray(n);
            if (n == 0) {
                cout << "List is empty" << endl;
                continue;
            }
            mergeSort(a, 0, n - 1);
            cout << "Enter number to search: ";
            cin >> x;
            int res = bSearch(a, n, x);
            if (res == -1)
                cout << "Not Found" << endl;
            else
                cout << "Found at index: " << res << endl;
            delete[] a;
        } else if (ch == 8) {
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
