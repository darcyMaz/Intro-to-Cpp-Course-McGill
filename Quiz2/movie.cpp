#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class Movie
{
    float duration;
    string name;
    int year;
    char* stream;

    public:
        Movie(float pDur, string pName, int pYear, string pStream)
        {
            duration = pDur;
            name = pName;
            year = pYear;
            //stream = pStream;
            
            char charArr[pStream.length() + 1];
            strcpy(charArr,pStream.c_str());
            stream = charArr;

        }
        Movie() {}
        ~Movie()
        {
            delete [] stream;
        }
        
        /*
        Movie& operator=(const Movie &pMovie)
        {
            //duration = pMovie.duration;
            //name = pMovie.name;
            //year = pMovie.year;
            //stream = pMovie.stream;
            return *this;
            //cout << "copy const" << endl;
        }
        */
       
        void SetData(float pDur, string pName, int pYear, string pStream)
        {
            duration = pDur;
            name = pName;
            year = pYear;
            
            char charArr[pStream.length() + 1];
            strcpy(charArr,pStream.c_str());
            stream = charArr;
        }
        float getDuration()
        {return duration;}

        string getName()
        {return name;}

        int getYear()
        {return year;}

        char* getStream()
        {return stream;}
};

int main()
{
    Movie movie(200, "My life without C++", 2022,"f651270d6011098375db09912b03e5e7");
    
    Movie movie2(150, "Want You Gone", 1987, "db6fd7d74393b375344010a0c9cc4535");
    
    Movie movie3;
    movie3 = movie2;

    cout << movie3.getName();

    // set new data
    movie2.SetData(120, "My life after C++", 2001, "ac6fd7d74393b375344010a0c9cc4535");

    cout << movie3.getName();
/*
    cout << "movie 1" << endl;
    cout << "Year = " << movie.getYear() << endl;
    cout << "movie Name = " << movie.getName() << endl;
    cout << "movie Duration = " << movie.getDuration() << endl;
    cout << "movie Stream = " << movie.getStream() << endl;
    cout << endl;
    cout << "movie 2" << endl;
    cout << "Artist = " << movie2.getYear() << endl;
    cout << "movie Name = " << movie2.getName() << endl;
    cout << "movie Duration = " << movie2.getDuration() << endl;
    cout << "movie Stream = " << movie2.getStream() << endl;
    cout << endl;
    cout << "movie 3" << endl;
    cout << "Artist = " << movie3.getYear() << endl;
    cout << "movie Name = " << movie3.getName() << endl;
    cout << "movie Duration = " << movie3.getDuration() << endl;
    cout << "movie Stream = " << movie3.getStream() << endl;
    */
    return 0;
}