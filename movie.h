#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "product.h"

class Movie : public Product {
  public:
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre_, const std::string rating_);

    ~Movie();

    std::set<std::string> keywords() const;
    std::string displayString() const;
    std::string getGenre() const;
    std::string getRating() const;

    bool isMatch(std::vector<std::string>& searchTerms) const;

    void dump(std::ostream& os) const;

  private:
    std::string genre;
    std::string rating;

};
#endif
