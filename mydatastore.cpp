#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <queue>
#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include "product_parser.h"
#include "mydatastore.h"

using namespace std;

MyDataStore::MyDataStore() {
    // Constructor remains unchanged.
}

MyDataStore::~MyDataStore() {
    // Iterate over products set and delete each dynamically allocated Product
    set<Product*>::iterator it;
    for (it = products.begin(); it != products.end(); ++it) {
        delete *it;
    }
    products.clear();

    // Iterate over users set and delete each dynamically allocated User
    set<User*>::iterator userit;
    for (userit = users.begin(); userit != users.end(); ++userit) {
        delete *userit;
    }
    users.clear();
    // Automatically clear maps to release memory.
    pMap.clear();
    cartMap.clear();
}

void MyDataStore::addProduct(Product* p) {
    products.insert(p);
    set<string> words = p->keywords();
    for (set<string>::iterator it = words.begin(); it != words.end(); ++it) {
        pMap[*it].insert(p);
    }
}

void MyDataStore::addUser(User* u) {
    users.insert(u);
    queue<Product*> cart;
    cartMap[convToLower(u->getName())] = cart;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    set<Product*> resultSet;
    if (type == 0) { // AND search
        bool isFirstTerm = true;
        for (vector<string>::size_type i = 0; i < terms.size(); ++i) {
            if (pMap.find(terms[i]) != pMap.end()) {
                if (isFirstTerm) {
                    resultSet = pMap[terms[i]];
                    isFirstTerm = false;
                } else {
                    resultSet = setIntersection(resultSet, pMap[terms[i]]);
                }
            } else {
                resultSet.clear();
                break;
            }
        }
    } else if (type == 1) { // OR search
        for (vector<string>::size_type i = 0; i < terms.size(); ++i) {
            if (pMap.find(terms[i]) != pMap.end()) {
                resultSet = setUnion(resultSet, pMap[terms[i]]);
            }
        }
    }

    vector<Product*> prod;
    for (set<Product*>::iterator it = resultSet.begin(); it != resultSet.end(); ++it) {
        prod.push_back(*it);
    }
    return prod;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << endl;
    for (set<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for (set<User*>::iterator userit = users.begin(); userit != users.end(); ++userit) {
        (*userit)->dump(ofile);
    }
    ofile << "</users>" << endl;
}

void MyDataStore::addToCart(std::string username, Product* p) {
    string lowercaseName = convToLower(username);
    if (cartMap.find(lowercaseName) != cartMap.end()) {
        cartMap[lowercaseName].push(p);
    } else {
        cout << "Invalid request" << endl;
    }
}

void MyDataStore::printCart(std::string username) {
    string lowercaseName = convToLower(username);
    if (cartMap.find(lowercaseName) != cartMap.end()) {
        queue<Product*> tempCart = cartMap[lowercaseName];
        int index = 1;
        while (!tempCart.empty()) {
            cout << "Item " << index << ": " << tempCart.front()->displayString() << endl;
            tempCart.pop();
            ++index;
        }
    } else {
        cout << "Invalid username" << endl;
    }
}

void MyDataStore::buyCart(std::string username) {
    string lowercaseName = convToLower(username);
    if (cartMap.find(lowercaseName) == cartMap.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    User* user = nullptr;
    for (set<User*>::iterator it = users.begin(); it != users.end(); ++it) {
        if (convToLower((*it)->getName()) == lowercaseName) {
            user = *it;
            break;
        }
    }

    if (!user) {
        cout << "User not found." << endl;
        return;
    }

    queue<Product*>& cart = cartMap[lowercaseName];
    while (!cart.empty()) {
        Product* product = cart.front();
        if (product->getQty() > 0 && user->getBalance() >= product->getPrice()) {
            product->subtractQty(1);
            user->deductAmount(product->getPrice());
        }
        cart.pop();
    }
}
