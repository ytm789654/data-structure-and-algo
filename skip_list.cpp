#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <map>
using namespace std;

#define MAX_LEVEL 32
#define INT_MAX 0x7fffffff
#define NOT_FOUND -1
#define FOUND 0
#define NEW_NODE 1
#define LEVEL_UP_P 0.25
#define MILLION 1000000

class Node;
Node* pool_ptr;

class Node
{
public:
    Node(int key, string val, int level):_key(key),_val(val),_level(level)
    {
        _forward = vector<Node*>(level + 1, nullptr);
    }

    int _key;
    string _val;
    int _level;
    vector<Node*> _forward; //forward[i] points to next i+1 level node
};

class SkipList
{
public:
    Node* create_node(int key, string val, int level)
    {
        Node* ret = new(pool_ptr) Node(key, val, level);
        pool_ptr++;
        return ret;
    }
    SkipList()
    {
        _nil = create_node(INT_MAX, "nil", MAX_LEVEL);
        _head = create_node(-1, "head", MAX_LEVEL);
        for(int i = 0; i<MAX_LEVEL; i++)
            _head->_forward[i] = _nil;
        _level = 0;
    }

    int search(int key, string& result)
    {
        int search_level = _level;
        Node* x_node = _head;
        while(search_level>=0)
        {
            if( x_node->_forward[search_level]->_key < key)
                x_node = x_node->_forward[search_level];
            else
                search_level--;
        }
        x_node = x_node->_forward[0];
        if (key == x_node->_key)
        {
            result = x_node->_val;
            return FOUND;
        }
        else
        {
            return NOT_FOUND;
        };
    };

    int insert_node(int key, string val)
    {
        vector<Node*> update = vector<Node*>(_level+1, _head);
        int search_level = _level;
        Node* x_node = _head;
        while(search_level>=0)
        {
            if( x_node->_forward[search_level]->_key < key)
            {
                x_node = x_node->_forward[search_level];
            }
            else
            {
                update[search_level] = x_node;
                search_level--;
            }
        }
        x_node = x_node->_forward[0];
        if (key == x_node->_key)
        {
            x_node->_val = val;
            return FOUND;
        }
        else
        {
            int new_node_level = get_level();
            x_node = create_node(key, val, new_node_level);
            if(new_node_level>_level)
            {
                for(int i = _level + 1; i<=new_node_level; i++)
                    update.push_back(_head);
                _level = new_node_level;
            }

            for(int i = 0; i<=new_node_level; i++)
            {
                x_node->_forward[i] = update[i]->_forward[i];
                update[i]->_forward[i] = x_node;
            }
            return NEW_NODE;
        }
    }

    int delete_node(int key)
    {
        vector<Node*> update = vector<Node*>(_level+1, _head);
        int search_level = _level;
        Node* x_node = _head;
        while(search_level>=0)
        {
            if( x_node->_forward[search_level]->_key < key)
            {
                x_node = x_node->_forward[search_level];
            }
            else
            {
                update[search_level] = x_node;
                search_level--;
            }
        }
        x_node = x_node->_forward[0];
        if (key == x_node->_key)
        {
            for(int i = 0; i<=_level; i++)
            {
                if(update[i]->_forward[i] != x_node)
                    break;
                else
                {
                   update[i]->_forward[i] = x_node->_forward[i];
                }
            }
            x_node->~Node();
            while(_level>0 && _head->_forward[_level] == _nil)
                _level--;
            return FOUND;
        }
        else
        {
            return NOT_FOUND;
        }
    }

    int get_level()
    {
        random_device rd;
        default_random_engine e(rd());
        uniform_real_distribution<double> rand_generator(0, 1);
        int ret = 0;
        while(rand_generator(e) < LEVEL_UP_P && ret<MAX_LEVEL)
            ret++;
        if(ret>_level+1)
            ret = _level+1;
        return ret;
    }

    void print_list()
    {
        for(int i = 0; i<=_level; i++)
        {
            Node* p = _head->_forward[i];
            cout<<"level "<<i<<endl;
            while(p!=_nil)
            {
                cout<<'{'<<p->_key<<','<<p->_val<<"}->";
                p = p->_forward[i];
            }
            cout<<"nil\n";
        }
    }

    int _level;
    Node* _head;
    Node* _nil;
};

// --------------------------------------------------- test fun ----------------------------------------
string rand_str(int len)
{
    random_device rd;
    default_random_engine e(rd());
    string ret(len, 'a');
    for(int i = 0; i<len; i++)
        ret[i] = e()%26+'a';
    return ret;
}

void init_pool()
{
    pool_ptr = (Node*)malloc( (MILLION+10)*sizeof(Node));
}

int main()
{
    init_pool();
    SkipList sl;
    const int test_freq = MILLION;

    cout<<"start skip list insert\n";
    for(int i = 1; i<=test_freq; i++)
        sl.insert_node(i, rand_str(5));
    
    cout<<"skip list insert over\n";

    map<int, string> m;
    for(int i = 1; i<=test_freq; i++)
        m[i] = rand_str(5);
    cout<<"map insert over\n";
    return 0;
}