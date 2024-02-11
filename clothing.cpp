#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <set>
#include "clothing.h"
#include "util.h"
#include "product.h"

using namespace std;

// contructor that initializes a object
Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size_, const std::string brand_)
// call the base class constructor
 : Product(category, name, price, qty) {
   size = size_;
   brand = brand_;
}

// destructr
Clothing::~Clothing() {

}

// return the set of keyword representing the item
std::set<std::string> Clothing::keywords() const{
  // same idea in book.cpp, it'll parse the product name into the keyword
  set<string> prod = parseStringToWords(name_);
  set<string> BRAND = parseStringToWords(brand);
  prod = setUnion(prod, BRAND);
  return prod;
}

// check if the item matches any of the searches
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {
  set<string> keys = keywords();
  for (size_t i = 0; i < searchTerms.size(); i++) {
    if (keys.find(searchTerms[i]) != keys.end()) {
      return true;
    }
  }
  return false;
}

// construct and return the string representation
std::string Clothing::displayString() const{
  stringstream prod;
  prod << name_ << "\nSize: " << size << " Brand: " << brand << "\n" << price_ << " " << qty_ << " left." << endl;
  return prod.str();
}

// output the clothing item in the output stream
void Clothing::dump(std::ostream& os) const {
  Product::dump(os);
  os << size << "\n" << brand << endl;
}

//Accessor function to get size
std::string Clothing::getSize() const {
  return size;
}

// accessor to get brand
std::string Clothing::getBrand() const {
  return brand;
}
