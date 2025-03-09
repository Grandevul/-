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

void f(vector <pair <int, int> > &a, int current_W, int value, stack <int> &cur, int deep)
{
    int i = 0;
    if (!cur.empty())
    {
        i = cur.top();
    }
    cout << deep << " " << i << endl;
    int n = a.size();
    i += 1;
    for (i; i < n; i++)                                    /// look for branches
    {
        if (current_W + a[i].second > W) continue;                  /// using bound limit 2
        cur.push(i);
        f(a, current_W + a[i].second, value + a[i].first, cur, deep+1);     /// recursion - repeat branching
        cur.pop();
    }
    if (value > ans_value)
    {
        //ans = cur;
        ans_value = value;
    }
}

int main()
{
    W = 0;
    ifstream in("data/ks_100_1");

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
    f(a, current_W, value, current_stack, 0);

    cout << "Answer: " << ans_value << endl;
//    cout << "List:" << endl;
//    while (!ans.empty())
//    {
//        cout << ans.top() << " ";
//        ans.pop();
//    }
//    cout << endl;
    return ans_value;
}
