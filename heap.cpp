#include <iostream>
#include <vector>
using namespace std;

class min_heap
{
public:
    min_heap(vector<int> _data)
    {
        size = _data.size();
        data = (int*) malloc(size * sizeof(int));
        for(int i = 0; i<size; i++)
        {
            data[i] = _data[i];
            adjust_up(i);
        }
        cout<<"init ok..."<<endl;
        cout<<"heap size is "<<size<<endl;
    }

    ~min_heap()
    {
        delete data;
    }

//member
private:
    int size;
    int* data;

//member function
    void adjust_up(int pos)
    {
        if(pos == 0)
            return ;
        if(data[(pos-1)/2] > data[pos])
        {
            int temp = data[(pos-1)/2];
            data[(pos-1)/2] = data[pos];
            data[pos] = temp;
            adjust_up((pos-1)/2);
        }
    }

    void adjust_down(int pos)
    {
        int m_pos = pos;
        if(pos*2+1 < size && data[pos*2+1] < data[pos])
            m_pos = pos*2+1;
        
        if(pos*2+2 < size && data[pos*2+2] < data[m_pos])
            m_pos = pos*2+2;
        
        if(m_pos == pos)
            return ;
        else
            {
                int temp = data[pos];
                data[pos] = data[m_pos];
                data[m_pos] = temp;
                adjust_down(m_pos);
            }
    }

public:
    void sort()
    {
        int initial_size = size;
        while(size)
        {
            cout<<"size = "<<size<<endl;
            int temp = data[0];
            data[0] = data[size-1];
            data[size-1] = temp;
            size--;
            adjust_down(0);
        }
        size = initial_size;
    }

    void print()
    {
        for(int i = 0; i < size; i++)
            cout<<data[i]<<" ";
        cout<<endl;
    }
};

int main()
{
    vector<int> a = {9, 5, 4, 1, 6, 8, 0, 3, 1};
    min_heap heap = min_heap(a);
    heap.sort();
    heap.print();
    return 0;
}