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
    if (text == "action" || text == "Action") {
        return Genre::Action;
    }
    if (text == "drama" || text == "Drama") {
        return Genre::Drama;
    }
    if (text == "scifi" || text == "SciFi") {
        return Genre::SciFi;
    }

    return Genre::Action;
}

int starsToInt(string_view stars) {
    int count = 0;
    const string black_star = "★";

    for (size_t i = 0; i + black_star.size() <= stars.size();) {
        if (stars.substr(i, black_star.size()) == black_star) {
            ++count;
            i += black_star.size();
        } else {
            ++i;
        }
    }

    return count;
}

void MovieDatabase::addRating(const string& title, string_view genre_text, string_view stars) {
    genres_[title] = stringToGenre(genre_text);
    ratings_[title].push_back(starsToInt(stars));
}

void MovieDatabase::printSummary() const {
    for (const auto& [title, rating_list] : ratings_) {
        int sum = 0;
        for (int rating : rating_list) {
            sum += rating;
        }

        int average = 0;
        if (!rating_list.empty()) {
            average = sum / static_cast<int>(rating_list.size());
        }

        cout << title
             << ": " << rating_list.size()
             << " ratings, average rating " << average
             << " stars, genre: " << genreToString(genres_.at(title))
             << '\n';
    }
}