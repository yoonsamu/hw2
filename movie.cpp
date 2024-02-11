#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <set>
#include "movie.h"
#include "util.h"
#include "product.h"

using namespace std;


// constructor for the movie, initialize the object
Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre_, const std::string rating_)
// call the base class constructor
 : Product(category, name, price, qty) {
   rating = rating_;
   genre = genre_;
}

// destructor
Movie::~Movie() {

}

// create and return the keywords representing the movie
std::set<std::string> Movie::keywords() const{
  // like movie.cpp and book.cpp go through the movie name and add it as a keyword
  set<string> prod = parseStringToWords(name_);
  // genre should be lower case
  prod.insert(convToLower(genre));
  return prod;
}

// cehck if the movie matches the given search terms
bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
  set<string> keys = keywords();
  for (size_t i = 0; i < searchTerms.size(); i++) {
    if (keys.find(convToLower(searchTerms[i])) != keys.end()) {
      return true;
    }
  }
  return false;
}

// construct and return string representatio
std::string Movie::displayString() const{
  // build the display
  stringstream prod;
  prod << name_ << "\nGenre: " << genre << " Rating: " << rating << "\n" << price_ << " " << qty_ << " left." << endl;
  return prod.str();
}

void Movie::dump(std::ostream& os) const {
  Product::dump(os);
  os << genre << "\n" << rating << endl;
}

// accessor function to get rating
std::string Movie::getRating() const {
  return rating;
}

// accessor function to get genre
std::string Movie::getGenre() const {
  return genre;
}
