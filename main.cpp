#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <utility>
#include <queue>

using namespace std;

vector <string> a;

struct Point
{
    int x,y;
    int father;
    char move;
};

bool visit[10000][10000];

int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};
char dmove[4]={'L','R','U','D'};

std::vector<Point*> q;

Point* find_begin()
{
//    int row = a.size();
//
//    int column0[row];
//    for (int r = 0; r < row-1; ++r)
//    {
//        column0[r] = a[r].size();
//    }
//
//    int column = a[0].size();
//    for (int r = 1; r < row-1; ++r)
//    {
//        if (column <= column0[r])
//            column = column0[r];
//    }

    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < a[i].size(); ++j)
        {
            char now_char = a[i][j];

            if (now_char == '+')
            {
                return NULL;
            }
            if (now_char == '@')
            {
                struct Point* p;
                p = (struct Point*) malloc (sizeof(struct Point));
                memset(p, 0, sizeof(struct Point));
                p->x = i;
                p->y = j;
                p->father = -1;
                return p;
            }
        }
    }
    return 0;
}

void get_ans (Point* p)
{
    std::vector<char> v;
    while(p->father != -1)
    {
        v.push_back(p->move);
        p = q[p->father];
    }
    for (int i = v.size()-1; i > 0; --i)
    {
        cout << v[i] << ' ';
    }
    cout << v[0] << endl;
}

int main()
{
    for (string line; getline(cin, line);)
    {
        a.push_back(line);
    }

//    for (int i= 0; i < a.size(); ++i)
//    {
//        for (int j = 0; j < a[i].size(); ++j)
//        {
//            cout << a[i][j];
//        }
//        cout << endl;
//    }

    int row = a.size();

    int column0[row];
    for (int r = 0; r < row-1; ++r)
    {
        column0[r] = a[r].size();
    }

    int column = a[0].size();
    for (int r = 1; r < row-1; ++r)
    {
        if (column <= column0[r])
            column = column0[r];
    }

    Point* begin = find_begin();
    if (begin == NULL)
        return 0;

    memset(visit, 0, sizeof(visit));

    int head = -1, tail = 0;
    q.push_back(begin);

    visit[begin->x][begin->y]=true;

    while (head < tail)
    {
        head++;
        Point* p = q[head];

        for (int i = 0; i < 4; ++i)
        {
            int xx = p->x + dx[i];
            int yy = p->y + dy[i];
            if ((xx<0)||(xx>=row)||(yy<0)||(yy>=column))continue;
            char now_char = a[xx][yy];

            if ((now_char == '#')||(now_char == '$')||(now_char == '*')||visit[xx][yy])continue;
            tail++;
            struct Point* now_p;
            now_p = (struct Point*) malloc (sizeof(struct Point));
            memset(now_p, 0, sizeof(struct Point));
            now_p->x = xx;
            now_p->y = yy;
            now_p->father = head;
            now_p->move = dmove[i];
            q.push_back(now_p);
            visit[xx][yy]=true;
            if (now_char == '.')
            {
                get_ans(now_p);
                return 0;
            }

        }
    }
    cout << "no path" << endl;

    return 0;
//    int i, j;
//
//    for (i = 0; i < a.size(); ++i)
//    {
//        for (j = 0; j < a[i].size(); ++j)
//        {
//            const auto& map = a[i][j];
//        }
//    }
//
//    for (i= 0; i < a.size(); ++i)
//    {
//        for (int j = 0; j < a[i].size(); ++j)
//        {
//            cout << a[i][j];
//        }
//        cout << endl;
//    }
//
//    return 0;
}