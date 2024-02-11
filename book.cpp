#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <set>
#include "book.h"
#include "util.h"
#include "product.h"

using namespace std;


// constructor for the book class, which can initializes the book object
Book::Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn)
 : Product(category, name, price, qty) {
   author_ = author;
   isbn_ = isbn;
}

// destructor
Book::~Book() {

}

// return keywords according to the book
std::set<std::string> Book::keywords() const{
  // put product name into the keywords
  set<string> prod = parseStringToWords(name_);
  // add the isbn into the set of keywords
  prod.insert(isbn_);
  // combine keywords with product and isbn
  set<string> author = parseStringToWords(author_);
  prod = setUnion(prod, author);
  return prod;
}

// if book matches any of the items provided
bool Book::isMatch(std::vector<std::string>& searchTerms) const {
  // get the keywords for book
  set<string> keys = keywords();
  // iterate through the search
  for (size_t i = 0; i < searchTerms.size(); i++) {
    // if keyword is found in book's keywords
    if (keys.find(searchTerms[i]) != keys.end()) {
      return true;
    }
  }
  return false;
}

// constructor and return the string
std::string Book::displayString() const{
  // build the display
  stringstream prod;
  prod << name_ << "\nAuthor: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left." << endl;
  return prod.str();
}

// output the book's details
void Book::dump(std::ostream& os) const {
  Product::dump(os);
  os << isbn_ << "\n" << author_ << endl;
}


// accessor to get the author's name
std::string Book::getAuthor() const {
  return author_;
}

// get the book's isbn number
std::string Book::getISBN() const {
  return isbn_;
}
