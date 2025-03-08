#include "Paper-plagiarism-check.h"

// 读取文件内容
string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file) {
        throw runtime_error("无法打开文件: " + filePath);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// 写入文件（输出相似度）
void writeFile(const string& filePath, double similarity) {
    ofstream file(filePath);
    if (!file) {
        throw runtime_error("无法打开输出文件: " + filePath);
    }
    file.precision(2);
    file << fixed << similarity << endl;
}

