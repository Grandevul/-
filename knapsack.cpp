#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
#include <stack>
#include <filesystem>
#include <chrono>

using namespace std;
using namespace std::filesystem;

const long double PI = 3.14159265359, INF = 100000;
int W;

//stack <int> ans;
int ans_value;
std::chrono::steady_clock::time_point begin0;

void f(vector <pair <int, int> > &a, int current_W, int value, stack <int> &cur)
{

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    //cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin0).count() << endl;
    if (std::chrono::duration_cast<std::chrono::seconds>(end - begin0).count() > 20) return;

    int i = 0;
    if (!cur.empty())
    {
        i = cur.top();
    }
    int n = a.size();
    i += 1;
    for (i; i < n; i++)                                    /// look for branches
    {
        if (current_W + a[i].second > W) continue;                  /// using bound limit
        cur.push(i);
        f(a, current_W + a[i].second, value + a[i].first, cur);     /// recursion - repeat branching
        cur.pop();
    }
    if (value > ans_value)
    {
        //ans = cur;
        ans_value = value;
    }
}

int code(basic_ifstream<char, char_traits<char>> &in)
{
    W = 0;

    int n, w;
    vector <pair <int, int> > a;

    if (in.is_open())
    {
        in >> n >> w;
        W = w;
//        cout << n << " " << w << endl;

        for (int i = 0; i < n; i++)
        {
            int vi, wi;
            in >> vi >> wi;
            a.push_back(make_pair(vi, wi));
//            cout << vi << " " << wi << endl;
        }

//        cout << endl;
    }
    in.close();

///--------------------------

    int current_W = 0;
    int value = 0;
    ans_value = 0;
    stack <int> current_stack;
    f(a, current_W, value, current_stack);

    //cout << "Answer: " << ans_value << endl;
//    cout << "List:" << endl;
//    while (!ans.empty())
//    {
//        cout << ans.top() << " ";
//        ans.pop();
//    }
//    cout << endl;
    return ans_value;
}

int main()
{
//    ifstream in("data/ks_4_0");

    vector <string> data;

    std::string path = "data/"; // ѕуть к папке
    for (auto& entry : directory_iterator(path))
    {
        std::string path_string{entry.path().u8string()};
        cout << path_string.size() << " ";
        //if (path_string.size() > 13) continue;
        data.push_back(path_string);
    }
    cout << endl;

    std::ofstream out("table.txt", std::ios::app);

    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << " -- ";
        ifstream in(data[i]);
        begin0 = std::chrono::steady_clock::now();
        int value = code(in);
        cout << "Answer: " << value << endl;
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        out << data[i] << "   " << value << "       " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin0).count() << endl;
    }
}
