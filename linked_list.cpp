#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    Node(int _val):val(_val), next(nullptr){}
    ~Node()
    {
        cout<<"Node with value "<<val<<" deleted."<<endl;
    }
// member variable
    int val;
    Node* next;
};

class LinkedList
{
public:
    void print_list()
    {
        Node* p = head;
        while(p!=nullptr)
        {
            cout<<p->val<<"->";
            p = p->next;
        }
        cout<<"tail"<<endl;
    }

    void add_new_node(int val)
    {
        Node* new_node = new Node(val);

        // special handle for first node
        if(head == nullptr)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void delete_node(int val)
    {
        if(head == nullptr)  return;

        Node* p = head;
        if(head->val == val)
        {
            head = p->next;
            delete p;
        }

        p = p->next;
        Node* last = head;
        while(p != nullptr)
        {
            if(p->val == val)
            {
                last->next = p->next;
                if(p == tail)
                    tail = last;
                delete p;
                break;
            }
            last = p;
            p = p->next;
        }
    }

    void reverve_list()
    {
        if(head == nullptr) return;
        if(head == tail) return;

        Node* p = head -> next;
        Node* last = head;

        while(p!=nullptr)
        {
            Node* q = p;
            p = p->next;
            q->next = last;
            last = q;
        }

        //update head and tail
        head -> next = nullptr;
        tail = head;
        head = last;
    }
    //default constructor
    LinkedList():head(nullptr), tail(nullptr){}
// member variable
private:
    Node* head;
    Node* tail;
};

int main()
{
    LinkedList L;
    for(int i = 0;i<10; i++)
        L.add_new_node(i);
    L.print_list();
    L.delete_node(5);
    L.delete_node(0);
    L.print_list();
    L.reverve_list();
    L.print_list();
    return 0;
}