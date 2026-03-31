#include "movie.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    MovieDatabase db;
    string title;
    string genre_text;
    string stars;

    while (true) {
        getline(cin, title);

        if (title == "q") {
            break;
        }

        getline(cin, genre_text);
        getline(cin, stars);

        db.addRating(title, genre_text, stars);
    }

    db.printSummary();

    return 0;
}