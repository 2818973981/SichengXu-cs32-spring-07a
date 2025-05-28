// WordCount.cpp

#include "WordCount.h"
#include <sstream>

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int totalwords = 0;
	for(size_t i = 0; i < CAPACITY; ++i){
		if(table[i].size() != 0){
			for(size_t j = 0; j < table[i].size();++j){
				totalwords += table[i][j].second;
			}	
		}
	}
	return totalwords;
}

int WordCount::getNumUniqueWords() const {
	int uniquewords = 0;
	for(size_t i = 0; i < CAPACITY; ++i){
		uniquewords += table[i].size();
	}
	return uniquewords;
}

int WordCount::getWordCount(std::string word) const {
	word = makeValidWord(word); 
    if (word.empty()) return 0;

    int index = hash(word);
    for (size_t i = 0; i < table[index].size(); ++i) {
        if (table[index][i].first == word) {
            return table[index][i].second;
        }
    }

    return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	word = makeValidWord(word);
    if (word.empty()) return 0;

	if(getWordCount(word) == 0){
		table[hash(word)].push_back(std::make_pair(word, 1));
		return 1;
	}
	else{
		for(size_t i = 0; i < table[hash(word)].size();++i){
			if(table[hash(word)][i].first == word){
				table[hash(word)][i].second ++;
				return table[hash(word)][i].second;
			}
		}
	}
	return 0;
}

int WordCount::decrWordCount(std::string word) {
	word = makeValidWord(word);
    if (word.empty()) return -1;

    int index = hash(word);
    for (size_t i = 0; i < table[index].size(); ++i) {
        if (table[index][i].first == word) {
            if (table[index][i].second > 1) {
                table[index][i].second--;
                return table[index][i].second;
            } else {
                table[index].erase(table[index].begin() + i);
                return 0;
            }
        }
    }
	return -1;
}


bool WordCount::isWordChar(char c) {
	return std::isalpha(static_cast<unsigned char>(c));
}

std::string WordCount::makeValidWord(std::string word) {
	std::string result;

    for (char &c : word) {
        c = std::tolower(c);
    }

    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];

        if (isWordChar(c)) {
            result += c;
        } else if ((c == '\'' || c == '-') &&
                   i > 0 && i < word.length() - 1 &&       
                   isWordChar(word[i - 1]) && isWordChar(word[i + 1])) {
            result += c; 
        }
    }

    return result;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> allWords;  // vector, not array

    for (size_t i = 0; i < CAPACITY; ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            allWords.push_back(table[i][j]);
        }
    }

	std::sort(allWords.begin(), allWords.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.first > b.first; 
        });

	for (const auto& p : allWords) {
        out << p.first << "," << p.second << "\n";
    }

}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> allWords;  // vector, not array

    for (size_t i = 0; i < CAPACITY; ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            allWords.push_back(table[i][j]);
        }
    }

	std::sort(allWords.begin(), allWords.end(),
    [](const auto& a, const auto& b) {
        if (a.second != b.second)
            return a.second < b.second;  
        else
            return a.first < b.first;    
    });

	for (const auto& p : allWords) {
        out << p.first << "," << p.second << "\n";
    }
}

void WordCount::addAllWords(std::string text) {
	std::istringstream ss(text);
    std::string word;

    while (ss >> word) {
        incrWordCount(word);  
    }
}
