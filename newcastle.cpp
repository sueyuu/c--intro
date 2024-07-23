#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

static vector<vector<int>> pascal(7, vector<int>(7, 0)); // 0-6

// return pascal(r,c)
int choose(int r, int c)
{
    if (pascal[r][c] == 0)
        pascal[r][c] = choose(r - 1, c) + choose(r - 1, c - 1);

    return pascal[r][c];
}
// calculate factor
int factorial(int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}
//find 
// all a and b are possible when calling this function
void counting(int a, int b, vector<int> remaining)
{
    // number of ways to select a
    int select_a_way = choose(remaining[0], a);

    // number of ways to select b
    int select_b_way = choose(remaining[0] - a + remaining[1], b);

    // iterate of choose b's corresponding cls
    // 2i+j = b
    // i's upper is min(r[2], b/2)
    // j's upper is min(r[2]+r[3], b)
    int i = 0;
    int j = min(b, remaining[2] + remaining[3]);

    int upper = b;

    while (j < upper)
    {
        i++;
        upper -= 2;
    }
    j = b - 2 * i;

    while (i <= min(b / 2, remaining[2]))
    {
        
        // possible corresponding cls to b
        //possible b's permutation
        int b_permu_cl = factorial(b) / pow(2,i);
        
        
        // from cl_r[0]+cl_r[1] choose remaining j
        // k1+k2 =j
        // k1 upper min(cl_r[0], j)
        // k2 upper min(cl_r[1], j)
        int k1 = 0;
        int k2 = min(j, remaining[3]);

        int upper = j;

        while (k2 < upper)
        {
            k1++;
            upper --;
        }
        k2 =upper;
        while (k1 <= min(remaining[2]-i, j))
        {
            vector<int> cl_r(remaining.begin() + 2, remaining.end());
            cl_r[0] -= i;
            cl_r[0] -= k1;
            cl_r[1] += k1;
            cl_r[1] -= k2;
            cout << " i "<<i << " k1 " << k1 << " k2 " << k2 << endl;
            cout << "r " << cl_r[0] << " " << cl_r[1] << endl;

            k1++;
            k2--;
        }

        // now for a chosen cls and its corresponding remaining
        // find corresponding a and remaining cls combination
        //find_a(a, new_r);
                
                i += 1;
                j -= 2;
    }
}

int main()
{
    // initiation pascal
    for (int i = 1; i < 7; i++)
    {
        pascal[i][0] = pascal[i][i] = 1;
        pascal[i][1] = pascal[i][i - 1] = i;
    }

    int n, k;
    cin >> n >> k;
    // first use and array to get each rw/cl's remaining counting
    vector<int> reverse_counting(2 * n, 2);

    int totalcount = 2 * n;

    while (k--)
    {
        int r, cl;
        cin >> r;
        reverse_counting[--r]--;

        cin >> cl;
        reverse_counting[--cl + n]--;

        totalcount--;
    }

    // set remaining rw2, rw1, cl2, cl1
    vector<int> remaining(4, 0);
    for (int i = 0; i < 2 * n; i++)
    {
        if (i < n)
        {
            if (reverse_counting[i] == 2)
                remaining[0]++;
            else if (reverse_counting[i] == 1)
                remaining[1]++;
        }
        else
        {
            if (reverse_counting[i] == 2)
                remaining[2]++;
            else if (reverse_counting[i] == 1)
                remaining[3]++;
        }
    }
    int maxnode = remaining[0] + remaining[1];
    // during each it, max selection is c
    // maxnode is b's final upperlimit
    // a's final upper limit is remaining[0]
    for (int c = 0; c <= totalcount; c++)
    {
        // 2*a+b = c
        // initiate a from 0, if b's possible max upper < c, increase a to proper size;

        int a = 0;
        int b = min(c, maxnode);
        int upper = c;

        while (b < upper)
        {
            a++;
            upper -= 2;
        }
        b = c - 2 * a;

        // increase a gradually
        // max a should be min(c/2, remaining[0])
        while (a <= min(c / 2, remaining[0]))
        {


counting(a, b, remaining);
a++;
b -= 2;
        }
    }
}