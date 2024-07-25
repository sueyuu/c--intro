#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

static int sum = 1;

vector<int> choose(vector<bool> select, vector<int> remain)
{
    vector<int> temp;
    int size = select.size();
    for (int i = 0; i < size; i++)
    {
        if (select[i])
            temp.push_back(remain[i]);
    }
    return temp;
}
// find second indx
int my_found(vector<int> &temp, int i)
{
    auto it = find(temp.begin() + i + 1, temp.end(), temp[i]);

    return distance(temp.begin(), it);
}
// find first ele
int my_found(vector<pair<int, int>> &temp, int t)
{
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i].first == t)
            return i;
    }
    return temp.size();
}

void my_count(vector<int> temprw, vector<int> tempcl, int n, bitset<36> &M)
{
    for (auto x : temprw)
        cout << x << " ";
    cout << endl;
    for (auto x : tempcl)
        cout << x << " ";
    cout << endl;
    int size = temprw.size();
    // put all repeatitive row in vector
    // put index pair into per
    vector<pair<int, int>> rep;
    for (int i = 0; i < size; i++)
    {
        int idx = my_found(temprw, i);
        if (idx != size)
            // first is larger one
            rep.push_back(pair(idx, i));
    }
    
    for (int i = 0; i < size; i++)
    {
        int rep_idx = my_found(rep, i);
        if (rep_idx != rep.size())
        {
            // if>= previous rwn's corresponding cl, break
            if (tempcl[rep[rep_idx].first] >= tempcl[rep[rep_idx].second])

                break;
            
        }
        // if in initial k, break
        if (M[temprw[i] * n + tempcl[i]])

            break;
        if (i == size - 1)
            sum++;
    }

    while (next_permutation(tempcl.begin(), tempcl.end()))
    {
        for (int i = 0; i < size; i++)
        {
            int rep_idx = my_found(rep, i);
            if (rep_idx != rep.size())
            {
                // if>= previous rwn's corresponding cl, break
                if (tempcl[rep[rep_idx].first] >= tempcl[rep[rep_idx].second])

                    break;
            }
            // if in initial k, break
            if (M[temprw[i] * n + tempcl[i]])

                break;
            if (i == size - 1)
                sum++;
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> k;

    int totalcount = 2 * n;

    vector<bool> rwcount(2 * n, 0);
    vector<bool> clcount(2 * n, 0);
    bitset<36> M;

    while (k--)
    {
        int r, cl;
        cin >> r >> cl;
        --r;
        --cl;
        M[r * n + cl] = 1;
        if (rwcount[r])
        {
            rwcount[r + n] = 1;
        }
        else
        {
            rwcount[r] = 1;
        }

        if (clcount[cl])
        {
            clcount[cl + n] = 1;
        }
        else
        {
            clcount[cl] = 1;
        }

        totalcount--;
    }

    vector<int> remain_rw;
    vector<int> remain_cl;

    // could be repeatitive
    for (int i = 0; i < n; i++)
    {
        if (!rwcount[i])
            remain_rw.push_back(i);
        if (!rwcount[i + n])
            remain_rw.push_back(i);
        if (!clcount[i])
            remain_cl.push_back(i);
        if (!clcount[i + n])
            remain_cl.push_back(i);
    }
    while (next_permutation(remain_rw.begin(), remain_rw.end()))
    {//if all different, w/ number counting
    //memoize previous used combo
    //if the same, goto next c
    }
    
    my_count(remain_rw, remain_cl, n, M);
    cout << sum;
}

