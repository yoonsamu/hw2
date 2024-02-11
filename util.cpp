#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) {
  // Convert to lowercase and trim whitespace.
    string temp = convToLower(trim(rawWords));
    // Initialize the set to store the words.
    set<string> words;
    // Buffer to hold characters forming a current word.
    string currentWord = "";

    for (size_t i = 0; i < temp.length(); ++i) {
        char c = temp[i];
        // Check if the character is alphabetic or a valid number, accumulate it.
        if (isalnum(c)) {
            currentWord += c;
        } else if (ispunct(c) || isspace(c) || i == temp.length() - 1) {
            // If the current character is punctuation or space, or we're at the end,
            // check if the accumulated word is valid and add it to the set.
            if (currentWord.length() >= 2) {
                words.insert(currentWord);
            }
             // Reset the current word buffer
            currentWord.clear();
        }

        // Special case for handling the last character
        if (isalnum(c) && i == temp.length() - 1 && currentWord.length() >= 2) {
            words.insert(currentWord);
        }
    }

    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

