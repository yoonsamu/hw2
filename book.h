#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "product.h"

class Book : public Product {
  public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string author, const std::string isbn);


    ~Book();

    std::set<std::string> keywords() const;
    std::string displayString() const;

    bool isMatch(std::vector<std::string>& searchTerms) const;

    void dump(std::ostream& os) const;


    //Accessors
    std::string getAuthor() const;
    std::string getISBN() const;


  private:
    std::string author_;
    std::string isbn_;

};
#endif