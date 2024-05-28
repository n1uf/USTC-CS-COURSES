#include<vector>
#include<iostream>
#include<queue>
#include<map>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

struct Map_Cell
{
    int type;
    // TODO: 定义地图信息

};

struct Search_Cell
{
    int h;
    int g;
    // TODO: 定义搜索状态
    int x, y;   // 当前坐标
    int T; // 身上的补给
    Search_Cell *parent; // 父节点
};

// 自定义比较函数对象，按照 Search_Cell 结构体的 g + h 属性进行比较
struct CompareF {
    bool operator()(const Search_Cell *a, const Search_Cell *b) const {
        return (a->g + a->h) > (b->g + b->h); 
    }
};

// TODO: 定义启发式函数(曼哈顿距离)
int Heuristic_Funtion(int nowx, int nowy, int endx, int endy)
{
    return abs(nowx - endx) + abs(nowy - endy);
}

void Astar_search(const string input_file, int &step_nums, string &way)
{
    ifstream file(input_file);
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }

    string line;
    getline(file, line); // 读取第一行
    stringstream ss(line);
    string word;
    vector<string> words;
    while (ss >> word) {
        words.push_back(word);
    }
    int M = stoi(words[0]);
    int N = stoi(words[1]);
    int T = stoi(words[2]);

    pair<int, int> start_point; // 起点
    pair<int, int> end_point;   // 终点
    Map_Cell **Map = new Map_Cell *[M];
    // 加载地图
    for(int i = 0; i < M; i++)
    {
        Map[i] = new Map_Cell[N];
        getline(file, line);
        stringstream ss(line);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        for(int j = 0; j < N; j++)
        {
            Map[i][j].type = stoi(words[j]);
            if(Map[i][j].type == 3)
            {
                start_point = {i, j};
            }
            else if(Map[i][j].type == 4)
            {
                end_point = {i, j};
            }
        }
    }
    // 以上为预处理部分
    // ------------------------------------------------------------------

    Search_Cell *search_cell = new Search_Cell;
    search_cell->g = 0;
    search_cell->x = start_point.first;
    search_cell->y = start_point.second;
    search_cell->h = Heuristic_Funtion(search_cell->x, search_cell->y, end_point.first, end_point.second); // Heuristic_Funtion();
    search_cell->T = T;
    search_cell->parent = nullptr;
    

    priority_queue<Search_Cell *, vector<Search_Cell *>, CompareF> open_list;
    vector<Search_Cell *> close_list;
    open_list.push(search_cell);

    while(!open_list.empty())
    {
        // TODO: A*搜索过程实现
        Search_Cell *now_cell = open_list.top();

        if(now_cell->x == end_point.first && now_cell->y == end_point.second)
        {
            // 到达终点
            // 生成路径
            std::vector<Search_Cell *> output_way;
            Search_Cell *temp = now_cell;
            int steps = 0;
            while(temp != nullptr)
            {
                output_way.push_back(temp);
                temp = temp->parent;
            }
            while(output_way.size() != 0)
            {
                way += to_string(output_way.back()->x) + " " + to_string(output_way.back()->y) + "\n";
                output_way.pop_back();
                steps ++;
            }
            step_nums = steps - 1;
            break;
        }

        open_list.pop();
        close_list.push_back(now_cell);
        // 生成新节点
        int dx[] = {-1, 1, 0, 0}; // 上下左右四个方向
        int dy[] = {0, 0, -1, 1};
        for(int i = 0; i < 4; i++)
        {
            int new_x = now_cell->x + dx[i];
            int new_y = now_cell->y + dy[i];
            
            // 判断坐标是否合法
            // 判断新节点是否越界
            if(new_x < 0 || new_x >= M || new_y < 0 || new_y >= N)
            {
                continue;
            }
            // 判断新节点是否是障碍物
            if(Map[new_x][new_y].type == 1)
            {
                continue;
            }

            // 给新节点赋值
            Search_Cell *new_cell = new Search_Cell;
            new_cell->x = new_x;
            new_cell->y = new_y;
            new_cell->g = now_cell->g + 1;
            new_cell->h = Heuristic_Funtion(new_x, new_y, end_point.first, end_point.second);
            if(Map[new_x][new_y].type == 2)
            {
                new_cell->T = T;
            }
            else
            {
                new_cell->T = now_cell->T - 1;
            }
            new_cell->parent = now_cell;

            // 当食物为0时，如果当前不是终点
            if(new_cell->T == 0 && Map[new_x][new_y].type != 4)
            {
                continue;
            }

            // 可以走到新节点
            
            // 分别检查节点是否在openlist和closelist中
            // 待检验(open_list)
            bool in_open_list = false;

            // 由于open_list是优先队列，无法直接查找，创建向量将队头插入查找后再插回队尾
            std::vector<Search_Cell *> temp_open_vec;
            for(int i = 0; i < open_list.size(); i++)
            {
                temp_open_vec.push_back(open_list.top());
                open_list.pop();
                if(temp_open_vec.front()->x == new_x && temp_open_vec.front()->y == new_y)
                {
                    in_open_list = true;
                }
                open_list.push(temp_open_vec.front());
                temp_open_vec.pop_back();
            }

            // 已检查(close_list)
            bool in_close_list = false;

            for(auto cell : close_list)
            {
                if(cell->x == new_x && cell->y == new_y)
                {
                    in_close_list = true;
                    break;
                }
            }

            // 不同情况对节点进行处理
            if(!in_open_list && !in_close_list)
            {   // 既不在open_list也不在close_list
                open_list.push(new_cell);
            }
            
            // 根据g值判断是否更新
            else if(in_open_list && new_cell->g < now_cell->g)
            {   // 在open_list中，且新节点的g值更小，找到这个节点并更新
                std::vector<Search_Cell *> temp_open_vec;
                for(int i = 0; i < open_list.size(); i++)
                {
                    temp_open_vec.push_back(open_list.top());
                    open_list.pop();
                    if(temp_open_vec.front()->x == new_x && temp_open_vec.front()->y == new_y)
                    {
                        temp_open_vec.front()->g = new_cell->g;
                        temp_open_vec.front()->parent = new_cell->parent;
                    }
                    open_list.push(temp_open_vec.front());
                    temp_open_vec.pop_back();
                }
            }
            else if(in_close_list && new_cell->g < now_cell->g)
            {   // 在close_list中，且新节点的g值更小，从close_list中删除，并加入open_list
                for(auto cell = close_list.begin(); cell != close_list.end(); cell++)
                {
                    if((*cell)->x == new_x && (*cell)->y == new_y)
                    {
                        close_list.erase(cell);
                        break;
                    }
                }
                open_list.push(new_cell);
            }

            // 根据T值判断是否更新
            else if(in_close_list && !in_open_list)
            {   // 在close_list中，且T值更大，加入open_list
                for(auto cell : close_list)
                {
                    if(cell->x == new_x && cell->y == new_y && new_cell->T > cell->T)
                    {
                        open_list.push(new_cell);
                        break;
                    }
                }
            }
            else
            {
                delete new_cell;
            }
        }
    }

    // ------------------------------------------------------------------
    // 释放动态内存
    for(int i = 0; i < M; i++)
    {
        delete[] Map[i];
    }
    delete[] Map;
    while(!open_list.empty())
    {
        auto temp = open_list.top();
        delete[] temp;
        open_list.pop();
    }
    for(int i = 0; i < close_list.size(); i++)
    {
        delete[] close_list[i];
    }

    return;
}

void output(const string output_file, int &step_nums, string &way)
{
    ofstream file(output_file);
    if(file.is_open())
    {
        file << step_nums << endl;
        if(step_nums >= 0)
        {
            file << way << endl;
        }

        file.close();
    }
    else
    {
        cerr << "Can not open file: " << output_file << endl;
    }
    return;
}

int main(int argc, char *argv[])
{
    string input_base = "../input/input_";
    string output_base = "../output/output_";
    // input_0为讲义样例，此处不做测试
    for(int i = 1; i < 11; i++)
    {
        int step_nums = -1;
        string way = "";
        Astar_search(input_base + to_string(i) + ".txt", step_nums, way);
        output(output_base + to_string(i) + ".txt", step_nums, way);
    }
    return 0;
}