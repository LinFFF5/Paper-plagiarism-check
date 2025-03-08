#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include <string>
#include "cppjieba/Jieba.hpp"
#include <algorithm>
#include <cctype>
using namespace std;

//Coine
string trim(const string& s);
vector<string> tokenize(const string& text, cppjieba::Jieba& jieba);
unordered_map<string, int> getWordFrequency(const vector<string>& words);
unordered_map<string, double> computeIDF(const vector<string>& words1, const vector<string>& words2);
unordered_map<string, double> calculateTFIDF(const vector<string>& words, const unordered_map<string, double>& idfDict);
double cosineSimilarityTFIDF(const unordered_map<string, double>& tfidf1, const unordered_map<string, double>& tfidf2);

//textIO
string readFile(const string& filePath);
void writeFile(const string& filePath, double similarity);