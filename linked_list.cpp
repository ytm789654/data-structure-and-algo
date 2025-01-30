#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename T>
class Node
{
public:
    Node(T _val):val(_val), next(nullptr){}
    ~Node()
    {
        cout<<"Node with value "<<val<<" deleted."<<endl;
    }
// member variable
    T val;
    Node<T>* next;
};

template <typename T>
class LinkedList
{
public:
    void print_list()
    {
        Node<T>* p = head;
        while(p!=nullptr)
        {
            cout<<p->val<<"->";
            p = p->next;
        }
        cout<<"tail"<<endl;
    }

    void add_new_node(T val)
    {
        Node<T>* new_node = new Node<T> (val);

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

    void delete_node(T val)
    {
        if(head == nullptr)  return;

        Node<T>* p = head;
        if(head->val == val)
        {
            head = p->next;
            delete p;
        }

        p = p->next;
        Node<T>* last = head;
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

    void reverse_recuise()
    {
        if(head == nullptr)
            return ;
        do_reverse(head, head->next);
        head->next = nullptr;
        auto tmp = head;
        head = tail;
        tail = tmp;
    }

    void do_reverse(Node<T>* p, Node<T>* q)
    {
        if(q == nullptr)
            return ;
        Node<T> *tmp = q->next;
        q->next = p;
        do_reverse(q, tmp);
    }

    void reverse_list()
    {
        if(head == nullptr) return;
        if(head == tail) return;

        Node<T>* p = head -> next;
        Node<T>* last = head;

        while(p!=nullptr)
        {
            Node<T>* q = p;
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
    Node<T>* head;
    Node<T>* tail;
};

int main()
{
    LinkedList<int> L;
    for(int i = 0;i<10; i++)
        L.add_new_node(i);
    L.print_list();
    L.delete_node(5);
    L.delete_node(0);
    L.print_list();
    L.reverse_list();
    L.print_list();

    string num[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    LinkedList<string> StringList;
    for(int i = 0; i<10; i++)
        StringList.add_new_node(num[i]);
    StringList.print_list();
    StringList.delete_node("five");
    StringList.print_list();
    StringList.reverse_list();
    StringList.print_list();
    StringList.reverse_recuise();
    StringList.print_list();
    return 0;
}