//Assignment 14
//Paolo Scattolin s1023775
//Johan Urban s1024726

#define NDEBUG
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
    assert (songs.size() == 0) ;
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
*   sorting functions:
************************************************************************/

void swap (vector <Track>& songs, int  pos1, int pos2)
{
    Track temp;
    temp = songs[pos1];
    songs[pos1] = songs [pos2];
    songs[pos2] = temp;
}

void dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
    red = first-1;         // index last red
    blue = last+1;         // index first blue
    int white = last+1;    // index first white
    const Track PIVOT = songs [first+(last-first)/2];
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

void special_dnf (vector<Track>& songs, int first, int last, int& red, int& blue)
{
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

void quicksort (vector<Track>& songs, int first, int last)
{
   // PRE:
   assert (0 <= first && last < size (songs)) ;
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

void special_quicksort (vector<Track>& songs, int first, int last)
{
   // PRE:
   assert (0 <= first && last < size (songs)) ;
   // POST: songs[first] ... songs[last] is sorted
   if (first >= last)
      return;
   else
    {
      int red, blue ;
      special_dnf(songs, first, last, red, blue) ;
      quicksort (songs, first, red) ;
      quicksort (songs, blue, last) ;
    }
}

/************************************************************************
*   the main structure of the program:
*       - read file
*       - sort data with insertion_sort / selection_sort / bubble_sort
*              and 'normal' order of Tracks
*              and increasing track length
************************************************************************/

int main()
{
    int first = 0;

	const int NO_OF_SONGS = read_file ("test.txt");

	if (NO_OF_SONGS < 0)
	{
        cout << "Reading file failed. Program terminates." << endl;
	    return NO_OF_SONGS;
    }
    int last = NO_OF_SONGS - 1;

    quicksort(songs,first,last);
    show_all_tracks(songs,NO_OF_SONGS);
    /*
     Now the algorithm are going to sort the track list by time.
     If you want to sort by track number in the album, just comment the .time part
     in these 2 functions and de-comment the rest.

     bool operator<(const Track& a, const Track& b)

     bool operator==(const Track& a, const Track& b)
    */

	return 0;
}
