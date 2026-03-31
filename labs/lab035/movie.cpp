#include "movie.h"
#include <iostream>

using namespace std;

string genreToString(Genre genre) {
    switch (genre) {
        case Genre::Action:
            return "Action";
        case Genre::Drama:
            return "Drama";
        case Genre::SciFi:
            return "SciFi";
    }
    return "Unknown";
}

Genre stringToGenre(string_view text) {
    if (text == "Action" || text == "action") {
        return Genre::Action;
    }
    if (text == "Drama" || text == "drama") {
        return Genre::Drama;
    }
    if (text == "SciFi" || text == "scifi") {
        return Genre::SciFi;
    }

    return Genre::Action;
}

int starsToInt(string_view stars) {
    int count = 0;
    string blackStar = "★";

    for (size_t i = 0; i + blackStar.size() <= stars.size();) {
        if (stars.substr(i, blackStar.size()) == blackStar) {
            count++;
            i += blackStar.size();
        } else {
            i++;
        }
    }

    return count;
}

void MovieDatabase::addRating(const string& title, string_view genre_text, string_view stars) {
    genres_[title] = stringToGenre(genre_text);
    ratings_[title].push_back(starsToInt(stars));
}

void MovieDatabase::printSummary() const {
    cout << "Movie Ratings Summary:" << '\n';

    for (const auto& [title, rating_list] : ratings_) {
        int sum = 0;
        for (int r : rating_list) {
            sum += r;
        }

        int average = sum / static_cast<int>(rating_list.size());

        cout << title
             << ": " << rating_list.size()
             << " ratings, average rating " << average
             << " stars, genre: " << genreToString(genres_.at(title))
             << '\n';
    }
}