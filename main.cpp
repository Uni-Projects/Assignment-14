#include <iostream>
#include <vector>

using namespace std;

typedef int El;

void swap (vector <El>& v, int  pos1, int pos2)
{
    El temp;
    temp = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = temp;
}

int largest(vector<El>&v, int low, int up)
{
    if ( low >= up )
        return low ;
    else
    {
        int POS = low;

        int i = low;

        while(i < up)
        {
            if (v[POS] < v[i])
                POS = i;
            i++;
        }
        return POS;
     }
}

void sort(vector<El>&v, int n)
{
    while(n > 1)
    {
        const int POS = largest(v, 0, n) ;
        swap (v, POS, n-1) ;
        n--;
     }
}

int main()
{
    vector <El> v = {68, 35, 53, 59, 45, 77, 72, 51, 58, 28, 82, 83, 90, 80, 43, 81, 55, 73, 20,
                     11, 3, 2, 16, 67, 88, 87, 23, 84, 86, 30, 25, 18, 69, 21, 24, 89, 5, 31, 46, 19, 48, 29, 65, 32, 37, 74, 7, 63,
                     17, 70, 47, 33, 27, 13, 10, 75, 36, 85, 38, 57, 42, 9, 76, 26, 6,
                     78, 61, 79, 50, 15, 4, 34, 54, 40, 22, 56, 12, 49, 39, 64, 1, 66,
                     71, 44, 60, 41, 8, 62, 14, 52};

    sort(v,v.size());

    for (int i = 0 ; i < v.size(); i++)
        cout << v[i] << " ";
    return 0;
}
