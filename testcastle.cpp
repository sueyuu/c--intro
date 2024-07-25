
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    vector<pair<int, int>> M;
    M.push_back(pair(1, 2));
    cout << M[0].first << endl;
}

for (int c = 1; c <= totalcount; c++)
{
    vector<bool> clselect(totalcount, 0);
    vector<bool> rwselect(totalcount, 0);
    // initiate for each c
    for (int i = 0; i < c; i++)
    {
        clselect[totalcount - i - 1] = 1;
        rwselect[totalcount - i - 1] = 1;
    }
    vector<int> tempcl = choose(clselect, remain_cl);
    vector<int> temprw = choose(rwselect, remain_rw);
    // end of initiate
    my_count(temprw, tempcl, n, M);

    while (next_permutation(rwselect.begin(), rwselect.end()))
    { // cl1 to all rw
        temprw = choose(rwselect, remain_rw);
        my_count(temprw, tempcl, n, M);
    }

    while (next_permutation(clselect.begin(), clselect.end()))
    {
        // clnext
        tempcl = choose(clselect, remain_cl);

        // sort rwselect, offset
        sort(rwselect.begin(), rwselect.end());

        my_count(temprw, tempcl, n, M);

        while (next_permutation(rwselect.begin(), rwselect.end()))
        { // cl1 to all rw
            temprw = choose(rwselect, remain_rw);
            my_count(temprw, tempcl, n, M);
        }
    }
}