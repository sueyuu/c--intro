#include <iostream>
#include <algorithm>
#include <vector>
#include <valarray>
#include <cmath>

using namespace std;

static vector<vector<int>> pascal(7, vector<int>(7, 0));  // 0-6
static vector<int> factor(13, 1);                         // 0-12
static vector<vector<int>> table(49, vector<int>(49, 0)); // a = 0..6, b = 0..6
static int sum = 0;

// return pascal(r,c)
int choose(int r, int c)
{
    if (r < c)
    {
        throw "error";
    }
    if (r == 0 && c == 0)
        return pascal[r][c];
    if (pascal[r][c] == 0)
        pascal[r][c] = choose(r - 1, c) + choose(r - 1, c - 1);

    return pascal[r][c];
}
// calculate factor
int factorial(int n)
{
    if (n == 0 || n == 1)
        return factor[n];
    if (factor[n] == 1)
        factor[n] = n * factorial(n - 1);
    return factor[n];
}
// 2*a+b =c
vector<int> generate_permu(int a, int b)
{
    vector<int> permu;
    int c = 2;
    while (c--)
    {
        for (int i = 1; i <= a; i++)
        {
            permu.push_back(i);
        }
    }
    for (int i = a + 1; i <= a + b; i++)
    {
        permu.push_back(i);
    }
    return permu;
}

int my_permutation(int d, int e, vector<int> permu)
{
    // first sort
    // need to iterate all possible combo
    sort(permu.begin(), permu.end());
    int p = 0;
    while (next_permutation(permu.begin(), permu.end()))
    {
        // check for 1...d, d+1...d+2d
        //  1. any i, d+i repeat
        // 2. if permu[i] > permu[d + i], just exchange existing permu, break
        bool ok = true;
        for (int i = 0; i < d; i++)
        {

            if (permu[i] >= permu[d + i])
            {
                ok = false;
                break;
            }
        }
        if (ok)
            p++;
    }
    return p;
}

int main()
{ // initiation pascal
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

    // during each it, max selection is c
    // maxnode is b's final upperlimit
    // a's final upper limit is remaining[0]
    for (int c = 0; c <= totalcount; c++)
    {
        // 2*a+b = c

        int a = 0;
        int b = min(c, remaining[0] + remaining[1]);
        // initiate a from 0, if b's possible max upper < c, increase a to proper size;
        // check for both a's upper limit and b's upper limit
        while (2 * a + b < c && a <= min(c / 2, remaining[0]))
        {
            a++;
            b = remaining[0] - a + remaining[1];
        }

        // increase a gradually
        // max a should be min(c/2, remaining[0])
        while (a <= min(c / 2, remaining[0]))
        { // possible select way
            int select_a_way = choose(remaining[0], a);

            int select_b_way = choose(remaining[0] - a + remaining[1], b);

            // then choose cls=>2d+e = c
            int d = 0;
            int e = min(c, remaining[2] + remaining[3]);

            while (2 * d + e < c && d <= min(c / 2, remaining[2]))
            {
                d++;
                e = remaining[2] - d + remaining[3];
            }

            while (d <= min(c / 2, remaining[2]))
            {
                // now all possible abcd

                int select_d_way = choose(remaining[2], d);

                int select_e_way = choose(remaining[2] - d + remaining[3], e);

                cout << a << " " << b << " " << d << " " << e << endl;

                // if b ==0 and e ==0
                // number of permu(d), then permu(d)*permu(d)-1)/1

                // first search table
                // if found, go to next abcd combo

                if (table[6 * a + b][6 * d + e] != 0)
                {
                    sum += select_a_way * select_b_way * select_d_way * select_e_way * table[6 * a + b][6 * d + e];
                    d++;
                    e -= 2;
                    continue;
                }
                if (table[6 * d + e][6 * a + b] != 0)
                {

                    sum += select_a_way * select_b_way * select_d_way * select_e_way * table[6 * d + e][6 * a + b];
                    d++;
                    e -= 2;
                    continue;
                }
                
                // if a>= d, permu a and check for interchange or same
                // or d>a
                if (a >= d)
                {
                    vector<int> permu = generate_permu(a, b);
                    table[6 * a + b][6 * d + e] = my_permutation(d, e, permu);
                    cout << table[6 * a + b][6 * d + e] << endl;
                    sum += select_a_way * select_b_way * select_d_way * select_e_way * table[6 * a + b][6 * d + e];
                }
                else
                {
                    vector<int> permu = generate_permu(d, e);
                    table[6 * a + b][6 * d + e] = my_permutation(a, b, permu);
                    //cout << table[6 * a + b][6 * d + e] << endl;
                    sum += select_a_way * select_b_way * select_d_way * select_e_way * table[6 * a + b][6 * d + e];
                }

                d++;
                e -= 2;
            }

            a++;
            b -= 2;
        }
    }

    cout << sum;
}