//Assignment 14
//Paolo Scattolin s1023775
//Johan Urban s1024726


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <string.h>

using namespace std;


/*********************************************************************
*   type definitions and global array songs:
**********************************************************************/
struct Length
{
    int minutes;							// #minutes (0..)
    int seconds;							// #seconds (0..59)
};
struct Track
{
    string artist;                          // artist name
    string cd;                              // cd title
    int    year;                            // year of appearance
    int    track_no;						// track number
    string title;                           // track title
    string tags;                            // track tags (separated by ,)
    Length time;							// track length
    string country;                         // countr(y/ies) of artist (separated by ,)
};

const int MAX_NO_OF_SONGS = 6000;
vector<Track> songs ;

/************************************************************************
*   Ordering relations op Track:
*      define < and == for Length and Track yourself, the other
*      ordering relations (>, <=, >=, >) follow from these automatically.
************************************************************************/
bool operator<(const Length& a, const Length& b)
{
    if (a.minutes == b.minutes)
        return a.seconds < b.seconds;
    else return a.minutes < b.minutes;
}

bool operator==(const Length& a, const Length& b)
{
    return (a.minutes == b.minutes && a.seconds == b.seconds) ;   /* implement a correct == ordering on Track values */
}

bool operator>(const Length& a, const Length& b)
{
    return b < a ;
}

bool operator<=(const Length& a, const Length& b)
{
    return !(b < a) ;
}

bool operator>=(const Length& a, const Length& b)
{
    return b <= a ;
}

bool operator<(const Track& a, const Track& b)
{
    /*
    if(a.artist == b.artist)
    {
         if(a.cd == b.cd)
         {
             if(a.year == b.year)
             {
                return a.track_no < b.track_no;
             }else return a.year < b.year;
         }else return a.cd < b.cd;
   }else return a.artist < b.artist ;
   */
    return a.time < b.time ;
}

bool operator==(const Track& a, const Track& b)
{
    //return (a.artist == b.artist && a.cd == b.cd && a.year == b.year && a.track_no == b.track_no) ;
    return a.time == b.time;
}

bool operator>(const Track& a, const Track& b)
{
    return b < a ;
}

bool operator<=(const Track& a, const Track& b)
{
    return !(b < a) ;
}

bool operator>=(const Track& a, const Track& b)
{
    return b <= a ;
}

/************************************************************************
*   Reading Tracks.txt file:
************************************************************************/
istream& operator>> (istream& in, Length& length)
{// Pre-condition:
    assert (true) ;
/*  Post-condition:
    a value for length has been obtained from in: first minutes, followed by ':', followed by seconds.
*/
    char colon ;
    in >> length.minutes >> colon >> length.seconds ;
    return in ;
}

ostream& operator<< (ostream& out, const Length length)
{// Pre-condition:
    assert (true) ;
/*  Post-condition:
    length is sent to out as: minutes, ':', seconds (at least 2 digits)
*/
    out << length.minutes << ':';
    if (length.seconds < 10)
        out << '0';
    out << length.seconds;
    return out ;
}

void skip_to_next_newline (istream& infile)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    infile has been read up to and including the next newline character.
*/
    string remains ;
    getline (infile, remains) ;
}

istream& operator>> (istream& infile, Track& track)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    infile has been read up to and including all members of one Track entry, including the last separating newline.
    These members are stored in track.
*/
    getline(infile,track.artist);       // artist
    getline(infile,track.cd);           // cd
    infile >> track.year ;              // year
    skip_to_next_newline(infile) ;
    infile >> track.track_no ;          // track number
    skip_to_next_newline(infile) ;
    getline(infile,track.title);        // track title
    getline(infile,track.tags);         // track tags
    infile >> track.time ;              // track time
    skip_to_next_newline(infile) ;
    getline(infile,track.country);      // country
    skip_to_next_newline(infile) ;
    return infile ;
}

// not necessary for assignment (because of show_track function), but included anyway because of symmetry:
ostream& operator<< (ostream& out, const Track track)
{// pre-condition:
    assert (true) ;
/*  post-condition:
    out has emitted all members of track, including the last separating newline.
*/
    out << track.artist   << endl ;
    out << track.cd       << endl ;
    out << track.year     << endl ;
    out << track.track_no << endl ;
    out << track.title    << endl ;
    out << track.tags     << endl ;
    out << track.time     << endl ;
    out << track.country  << endl ;
    out << endl ;
    return out ;
}

// NOTE: this version uses *array* implementation, convert to vector yourself
int read_songs (ifstream& infile, vector <Track>& songs)
{// pre-condition:
    assert (infile.is_open ()) ;
/*  post-condition:
    All tracks in infile have been read and stored in the same order in songs.
    The result is the number of tracks that have been read.
*/
    int i = 0 ;
    do {
        Track song ;
        infile >> song ;

        songs.push_back(song);
        i++;
    }
    while (!infile.eof() && i < MAX_NO_OF_SONGS);

    return i-1 ;
}

int read_file (string filename)
{// pre-condition:
    assert (filename.size() > 4) ;
/*  post-condition:
    If the result is -1, then no file could be opened, and songs is unchanged.
    Otherwise, the result is zero or positive, and songs contains all the found tracks in the
    file that corresponds with filename.
*/
    ifstream songsDBS (filename.c_str());
    if (!songsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_SONGS = read_songs (songsDBS, songs);
    songsDBS.close();
    cout << "Read " << NO_OF_SONGS << " tracks." << endl;
    return NO_OF_SONGS;
}

// NOTE: this version uses *array* implementation, convert to vector yourself
void show_all_tracks (vector <Track> songs, int no_of_songs)
{// pre-condition:
    assert (no_of_songs < MAX_NO_OF_SONGS) ;
/*  post-condition:
    songs[0] ... songs[no_of_songs-1] have been displayed to cout.
*/
    for (int i = 0 ; i < no_of_songs ; i++)
    {
        cout << i+1 <<". "<< songs[i] << endl ;
    }
}

/************************************************************************
*   sorting functions: (actual assignment)
************************************************************************/

/**********
 * PART 1:
 *********/

void swap (vector <Track>& songs, int  pos1, int pos2)
{
    // PRE:
    assert(pos1 >= 0 && pos1 < songs.size());
    // POST: swaps the elements at the given indices.
    Track temp;
    temp = songs[pos1];
    songs[pos1] = songs [pos2];
    songs[pos2] = temp;
}

void dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    // PRE:
    assert(songs.size() > 0);
    // POST: applies the dutch national flag division to the vector.
    red = first-1;         // index last red
    blue = last+1;         // index first blue
    int white = last+1;    // index first white
    const Track PIVOT = songs [first+(last-first) / 2];
    while (red < white - 1) // orange not empty
    {
        const int NEXT = white - 1; // last orange
        if (songs[NEXT] < PIVOT) // belongs in red
        {
            red++; // swap with first orange
            swap (songs, red, NEXT) ;
        }
        else if (songs[NEXT] == PIVOT) // belongs in white
            white-- ; // white area one larger
        else // belongs in blue
        {
            white--;
            blue--; // swap with last white
            swap (songs, NEXT, blue);
        }
    }
}

void quicksort (vector<Track>& songs, int first, int last)
{
    // PRE:
    assert (0 <= first && last <= songs.size()) ;
    // POST: songs[first] ... songs[last] is sorted
    if (first >= last)
        return;
    else
    {
        int red, blue ;
        dnf(songs, first, last, red, blue) ;
        quicksort (songs, first, red) ;
        quicksort (songs, blue, last) ;
    }
}

/**********
 * PART 2
 *********/
void special_dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    // PRE:
    assert(songs.size() >= 0);
    // POST: applies the alternative dutch national flag division of the vector,
    // with the colors white and orange inverted.
    red = first - 1;                     // index last red
    blue = last + 1;                     // index first blue
    int white = first - 1;               // index last white
    const Track PIVOT = songs [first+(last-first)/2];
    while (white < blue - 1)             // orange not empty
    {
        const int NEXT = blue - 1;      // last orange
        if (songs[NEXT] < PIVOT)        // belongs in red
        {
            red++;                     //adjust last red
            white++;                   //adjust last white
            swap(songs, red, NEXT);    // swap with first orange
        }
        else if (songs[NEXT] == PIVOT)  // belongs in white
        {
            white++;                    // adjust last white
            swap(songs, NEXT, white);   // swap last orange with first orange
        }

        else                            // belongs in blue
        {
            blue--;                    // adjust first blue
            swap (songs, NEXT, blue);  // swap first blue with last orange
        }
    }
}


void special_quicksort (vector<Track>& songs, int first, int last)
{
    // PRE:
    assert (0 <= first && last < songs.size()) ;
    // POST: songs[first] ... songs[last] is sorted
    if (first >= last)
        return;
    else
    {
        int red, blue ;
        special_dnf(songs, first, last, red, blue) ;
        special_quicksort (songs, first, red) ;
        special_quicksort (songs, blue, last) ;
    }
}

/****************************************************************
 * PART 3: translating recursive algorithm to an iterative one
 ***************************************************************/
typedef int El;

void swap_p3 (vector <El>& v, int  pos1, int pos2)
{
    // PRE:
    assert(pos1 >= 0 && pos1 <= pos2);
    assert(pos2 > 0 && pos2 < v.size());
    // POST: swaps the elements from pos1 and pos2 with each other.
    El temp;
    temp = v[pos1];
    v[pos1] = v[pos2];
    v[pos2] = temp;
}


int largest(vector<El>&v, int low, int up)
{
    // PRE:
    assert(low >= 0 && low < v.size());
    assert(low <= up);
    // POST: returns the index of the highest value of considered elements.
    int pos = low;

    int i = low;
    while(i < up)
    {
        if (v[pos] < v[i])
            pos = i;
        i++;
    }
    return pos;
}

void sort(vector<El>& v, int n)
{
    // PRE:
    assert(v.size() > 0);
    assert(n == v.size());
    // POST: sorts a vector iteratively based on its values using functions largest() and swap().
    while(n > 1)
    {
        const int POS = largest(v, 0, n) ;
        swap_p3 (v, POS, n-1) ;
        n--;
    }
}

/************************************************************************
*   the main structure of the program:
*       - read file
*       - sort data with quicksort / "sort"
*              'normal' order of Tracks
*              and increasing track length
************************************************************************/

void quickdnf(int num_songs)
{
    // PRE:
    assert(num_songs > 0);
    // POST: calls the functions necessary to apply dnf quicksort and output the result.
    int first = 0;
    int last = num_songs - 1;

    quicksort(songs,first,last);
    show_all_tracks(songs,num_songs);

}

void quickdnf_alt(int num_songs)
{
    // PRE:
    assert(num_songs > 0);
    // POST: calls the functions necessary to apply alternative dnf quicksort and output the result.
    int first = 0;
    int last = num_songs - 1;

    special_quicksort(songs, first, last);
    show_all_tracks(songs, num_songs);
}

void iterative_sort()
{
    // PRE:
    assert(true);
    // POST: calls the function necessary to apply sorting algorithm.
    vector <El> v = {   68, 35, 53, 59, 45, 77, 72, 51, 58, 28, 82, 83, 90, 80, 43, 81, 55, 73, 20,
                        11, 3, 2, 16, 67, 88, 87, 23, 84, 86, 30, 25, 18, 37,  69, 21, 24, 89,  5, 31,
                        46, 19, 48, 29, 65, 32, 37, 74, 7, 63,17, 70, 47, 33, 27, 13, 10, 75, 36,
                        85, 38, 57, 42, 9, 76, 26, 6,78, 61, 79, 50, 15, 4, 34, 54, 40, 22, 56,
                        12, 49, 39, 64, 1, 66, 71, 44, 60, 41, 8, 62, 14, 52
                    };

    sort(v,v.size());

    // PRINTING OF THE VECTOR
    for (int i = 0 ; i < v.size(); i++)
        cout << v[i] << " ";
}


int main()
{
    bool run = true;

    const int NO_OF_SONGS = read_file ("Tracks.txt");

    if (NO_OF_SONGS < 0)
    {
        cout << "Reading file failed." << endl;
    }

    while(run == true)
    {
        int input;
        /*
        Now the algorithm are going to sort the track list by time.
        If you want to sort by track number in the album, just comment the .time part
        in these 2 functions and de-comment the rest.
        bool operator<(const Track& a, const Track& b)
        bool operator==(const Track& a, const Track& b)
        */
        cout << endl;
        cout << "Which part of the assignment would you like to execute?" << endl;
        cout << "1: PART 1 - standard DNF quicksort" << endl;
        cout << "2: PART 2 - alternative DNF quicksort" << endl;
        cout << "3: PART 3 - iterative sorting algorithm" << endl;
        cout << "4: Exit" << endl;

        cin >> input;

        cout << endl;

        switch (input) {
            case 1 :
                quickdnf(NO_OF_SONGS);
                break;
            case 2:
                quickdnf_alt(NO_OF_SONGS);
                break;
            case 3:
                iterative_sort();
                break;
            case 4 :
                cout << endl;
                cout << "Exiting..." << endl;
                run = false;
                break;
            default :
                cout << "Input not accepted!" << endl;
                break;
        }
        cout << endl;
    }

    return 0;
}


