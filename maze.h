#include<random>

class maze{
public:
    maze(size_t row=0,size_t col=0);
public:
    size_t size();
    void random_generate();

private:
    int* data;
    size_t logic_size;  //逻辑上迷宫占用的空间
    size_t read_isze;   //实际分配占用的空间
};