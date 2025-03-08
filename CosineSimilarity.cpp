#include "Paper-plagiarism-check.h"

// ȥ�����ҿհ��ַ�
string trim(const string& s) {
    auto start = s.begin();
    while (start != s.end() && isspace(*start)) {
        start++;
    }
    auto end = s.end();
    do {
        end--;
    } while (distance(start, end) > 0 && isspace(*end));
    return string(start, end + 1);
}

// ʹ�� cppjieba ���ı����зִʣ�Ԥ�������
vector<string> tokenize(const string& text, cppjieba::Jieba& jieba) {
    string trimmedText = trim(text);
    //�ǿ��ж�
    if (trimmedText.empty()) {
        throw invalid_argument("�����ı�����Ϊ�ջ�������հ��ַ�");
    }
    vector<string> words;
    jieba.Cut(trimmedText, words, true);
    // ���˵����п� token
    vector<string> filtered;
    for (const string& word : words) {
        if (!word.empty() && word.find_first_not_of(" \t\r\n") != string::npos)
            filtered.push_back(word);
    }
    return filtered;
}


// ��Ƶͳ��
unordered_map<string, int> getWordFrequency(const vector<string>& words) {
    unordered_map<string, int> freq;
    for (const string& word : words) {
        freq[word]++;
    }
    return freq;
}

// �������ı��м���ÿ���ʵ� IDF ֵ
unordered_map<string, double> computeIDF(const vector<string>& words1, const vector<string>& words2) {
    unordered_map<string, int> df;
    unordered_set<string> unique1(words1.begin(), words1.end());
    unordered_set<string> unique2(words2.begin(), words2.end());
    for (const auto& w : unique1) {
        df[w]++;
    }
    for (const auto& w : unique2) {
        df[w]++;
    }
    int N = 2;
    unordered_map<string, double> idf;
    for (const auto& pair : df) {
        idf[pair.first] = log(static_cast<double>(N + 1) / (pair.second + 1)) + 1;
    }
    // ��ʽ��idf = log((N+1)/(df+1)) + 1������ N=2���ĵ�������
    return idf;
}

// ���� TF �� IDF ���� TF-IDF Ȩ������
unordered_map<string, double> calculateTFIDF(const vector<string>& words, const unordered_map<string, double>& idfDict) {
    unordered_map<string, double> tfidf;
    unordered_map<string, int> freq = getWordFrequency(words);
    int totalWords = words.size();
    for (const auto& pair : freq) {
        double tf = static_cast<double>(pair.second) / totalWords;
        double idf = idfDict.count(pair.first) ? idfDict.at(pair.first) : log(1 + 1e6);
        tfidf[pair.first] = tf * idf;
    }
    return tfidf;
}

// ����TF-IDFȨ�ؼ����������ƶ�
double cosineSimilarityTFIDF(const unordered_map<string, double>& tfidf1,const unordered_map<string, double>& tfidf2) {
    double dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    unordered_set<string> keys;
    for (const auto& pair : tfidf1) keys.insert(pair.first);
    for (const auto& pair : tfidf2) keys.insert(pair.first);
    for (const auto& key : keys) {
        double v1 = tfidf1.count(key) ? tfidf1.at(key) : 0.0;
        double v2 = tfidf2.count(key) ? tfidf2.at(key) : 0.0;
        dotProduct += v1 * v2;
        norm1 += v1 * v1;
        norm2 += v2 * v2;
    }
    if (norm1 == 0 || norm2 == 0) return 0.0;
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}