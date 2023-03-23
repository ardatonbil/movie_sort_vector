#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;


struct film {
    int year;
    string name, genre;
};

int owncount_film(vector<film> y, film obj) {
    if (y.size() == 0) {
        return 0;
    }
    else if (y.size() > 0) {
        int x = 0;
        for (int i = 0; i < y.size(); i++) {
            if (y[i].name == obj.name) {
                x++;
            }
        }
        return x;
    }
    return -1;
}

int owncount(vector<int> y, int obj) {
    if (y.size() == 0) {
        return 0;
    }
    else if (y.size() > 0){
        int x = count(y.begin(), y.end(), obj);
        return x;
    }
    return -1;
}

void insert(vector<int>& a, int newnum) {  		// NOT const vector
    // pre: a[0] <= … <= a[a.size()-1], a is sorted
    // post: newnum inserted into a, a still sorted
    int count = a.size();  // size before insertion
    a.push_back(newnum);   // increase size –newnum is inserted at the
    // end but inserted value is not important
    int loc = count;      // start searching insertion loc from end

    while (loc > 0 && a[loc - 1] < newnum) {
        a[loc] = a[loc - 1];
        loc--;        // shift right until the proper insertion cell
    }
    a[loc] = newnum;  //actual insertion
}


void alphabet(vector<film>& x, film newobj) { //function from the lecture
    int count = x.size();
    x.push_back(newobj);
    int loc = count;
    while (loc > 0 && x[loc - 1].name > newobj.name) {
        x[loc] = x[loc - 1];
        loc--;
    }

    x[loc] = newobj;
}

void sorting(vector<film>& x, film newobj) { //function from the lecture
    int count = x.size();
    x.push_back(newobj);
    int loc = count;
    while (loc > 0 && x[loc - 1].year > newobj.year) {
        x[loc] = x[loc - 1];
        loc--;
    }

    x[loc] = newobj;
}



int main()
{
    vector <film> films;
    string list;
    cout << "Welcome to the movie recommender program!" << endl << endl
         << "Please enter the movie, year and genre list:" << endl;
    cin >> list;
    string element;
    while (list != "") {
        element = list.substr(0, list.find("|"));
        film film_add;
        film_add.name= element.substr(0, list.find(";"));
        film_add.year = stoi(element.substr(list.find(";") + 1, list.find(";", list.find(";") + 1) - list.find(";") - 1),0,10);
        film_add.genre = element.substr(list.find(";", list.find(";") + 1)+1);
        films.push_back(film_add);
        list.erase(0, element.size()+1);
    }

    cout << endl << "Please select your action:" << endl << "1. Select the genre of the movie that you want to watch" << endl
         << "2. Select the year of the movie that you want to watch" << endl << "3. Choose a random movie" << endl <<
         "4. Exit program" << endl << endl;
    while (true){
        cout << "Enter your choice: ";
        string choice;
        cin >> choice;
        if (choice == "1") {
            cout << "Please enter the genre of the movie you want to watch: ";
            string genre_search;
            vector <film> filmofgenre{};
            vector<vector <film>> filmofgenresorted{};
            vector <int> yearssorted{};
            cin >> genre_search;
            cout << endl;
            string genre_search_original = genre_search;
            for (int i = 0; i < genre_search.size(); i++) {
                genre_search[i] = toupper(genre_search[i]);
            }
            for (int i = 0; i < films.size(); i++) {
                for (int u = 0; u < films[i].genre.size(); u++) {
                    films[i].genre[u] = toupper(films[i].genre[u]);
                    genre_search[u] = toupper(genre_search[u]);

                    if (films[i].genre == genre_search && owncount_film(filmofgenre,films[i])==0) {
                        filmofgenre.push_back(films[i]);
                    }
                }
            }
            for (int u = 0; u < filmofgenre.size(); u++) {
                if (owncount(yearssorted, filmofgenre[u].year) < 0) {
                    continue;
                }
                else if (owncount(yearssorted, filmofgenre[u].year) == 0){
                    vector<film> newvector{};
                    film x = filmofgenre[u];
                    insert (yearssorted, x.year);
                    filmofgenresorted.push_back(newvector);
                }
            }

            for (int u = 0; u < yearssorted.size(); u++) {
                for (int i = 0; i < films.size(); i++) {
                    if (films[i].year == yearssorted[u] && owncount_film(filmofgenre, films[i]) == 1) {
                        alphabet(filmofgenresorted[u], films[i]);
                    }
                }
            }

            if (filmofgenresorted.size() == 0) {
                cout << "There are no " << genre_search_original << " movies!" << endl << endl;
            }
            else {
                cout << genre_search_original << " movies from newest to oldest:" << endl;
                for (int u = 0; u < yearssorted.size(); u++) {
                    for (int i = 0; i < filmofgenresorted[u].size(); i++) {
                        cout << "Movie name: " << filmofgenresorted[u][i].name << " Release Year: " << filmofgenresorted[u][i].year << endl;
                    }
                }
                cout << endl;
                continue;
            }
        }

        else if (choice == "2") {
            cout << "Please enter the year of the movie you want to watch: ";
            string years;
            vector<int> yearssorted{};
            vector<film> filmofyears{};
            vector<vector<film>> filmofyearssorted{};
            cin >> years;
            if (years.size() == 9 && years[4] == '-') {
                int firstyear, secondyear;
                firstyear = stoi(years.substr(0, 4), 0, 10);
                secondyear = stoi(years.substr(5, 4), 0, 10);
                for (int i = 0; i < films.size(); i++) {
                    if (films[i].year >= firstyear && films[i].year <= secondyear) {
                        filmofyears.push_back(films[i]);
                    }
                }
            }
            else if (years.size() == 4) {
                int years_int = stoi(years);
                for (int i = 0; i < films.size(); i++) {
                    if (films[i].year == years_int) {
                        filmofyears.push_back(films[i]);
                    }
                }
            }

            for (int i = 0; i < filmofyears.size(); i++) {
                if (owncount(yearssorted, filmofyears[i].year) == 0) {
                    vector<film> newvector{};
                    insert(yearssorted, filmofyears[i].year);
                    filmofyearssorted.push_back(newvector);
                }
            }

            for (int n = 0; n < filmofyears.size(); n++) {
                for (int m = 0; m < yearssorted.size(); m++) {
                    if ((owncount_film(filmofyearssorted[m], filmofyears[n]) == 0) && (filmofyears[n].year == yearssorted[m])) {
                        alphabet(filmofyearssorted[m], filmofyears[n]);
                    }

                }
            }

            if (filmofyearssorted.size() == 0) {
                if (years.size() == 9) {
                    cout << "There are no movies released between " << years << "!" << endl << endl;
                    continue;
                }
                else if (years.size() == 4) {
                    cout << "There are no movies released in " << years << "!" << endl << endl;
                    continue;
                }
            }
            else {
                if (years.size() == 9) {
                    cout << "Movies released between the years " << years << " from A to Z with decreasing year ordering:" << endl;
                    for (int i = 0; i < yearssorted.size(); i++) {
                        for (int u = 0; u < filmofyearssorted[i].size(); u++) {
                            cout << "Movie name: " << filmofyearssorted[i][u].name << " Release Year: " << filmofyearssorted[i][u].year << " Genre: " << filmofyearssorted[i][u].genre << endl;
                        }
                    }
                }
                else if (years.size() == 4) {
                    cout << "Movies released in " << years << " from A to Z:" << endl;
                    for (int i = 0; i < yearssorted.size(); i++) {
                        for (int u = 0; u < filmofyearssorted[i].size(); u++) {
                            cout << "Movie name: " << filmofyearssorted[i][u].name << " Genre: " << filmofyearssorted[i][u].genre << endl;
                        }
                    }
                }
            }
            cout << endl;
        }
        else if (choice == "3") {
            int x = (rand() % films.size());
            cout << "Movie name: " << films[x].name << " Release Year: " << films[x].year << " Genre: " << films[x].genre << endl;
        }
        else if (choice == "4") {
            cout << "Thank you..." << endl;
            break;
        }
        else {
            cout << "Invalid action!" << endl << endl;
        }
    }
}


