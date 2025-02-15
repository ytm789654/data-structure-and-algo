#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <random>
#include <map>
#include <chrono>
using namespace std;

#define MAX_LEVEL 32
#define INT_MAX 0x7fffffff
#define NOT_FOUND -1
#define FOUND 0
#define NEW_NODE 1
#define LEVEL_UP_P 0.25

class Node
{
public:
    Node(int key, string& val, int level):_key(key),_val(val),_level(level)
    {
        _forward = vector<Node*>(level + 1, nullptr);
    }

    Node(int key, string&& val, int level):_key(key),_val(val),_level(level)
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
    SkipList()
    {
        _nil = new Node(INT_MAX, "nil", MAX_LEVEL);
        _head = new Node(-1, "head", MAX_LEVEL);
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

    int insert_node(int key, string& val)
    {
        Node* update[MAX_LEVEL];
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
            x_node = new Node(key, val, new_node_level);
            if(new_node_level>_level)
            {
                for(int i = _level + 1; i<=new_node_level; i++)
                    update[i] = _head;
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
        Node* update[MAX_LEVEL];
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
            delete x_node;
            while(_level>0 && _head->_forward[_level] == _nil)
                _level--;
            return FOUND;
        }
        else
        {
            return NOT_FOUND;
        }
    }

    int get_level() {
        static std::random_device rd;  // 静态初始化，避免重复创建
        static std::mt19937 gen(rd()); // 静态初始化，避免重复创建
        static std::uniform_real_distribution<> dis(0.0, 1.0); // 静态初始化

        int level = 0;
        while (dis(gen) < LEVEL_UP_P && level < MAX_LEVEL) {
            level++;
        }
        return level;
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

int main()
{
    SkipList sl;
    const int test_freq = 1000000;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 1; i<=test_freq; i++)
    {
        string s = rand_str(5);
        sl.insert_node(i, s);
    }
    auto end = std::chrono::high_resolution_clock::now();
    // 计算时间差
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // 输出运行时间
    std::cout << "Time taken by skip_list insert: "
              << duration.count() << " microseconds" << std::endl;

    map<int, string> m;
    start = std::chrono::high_resolution_clock::now();
    for(int i = 1; i<=test_freq; i++)
        m[i] = rand_str(5);
    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // 输出运行时间
    std::cout << "Time taken by std::map insert: "
              << duration.count() << " microseconds" << std::endl;
    return 0;
}