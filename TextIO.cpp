#include "Paper-plagiarism-check.h"

// ��ȡ�ļ�����
string readFile(const string& filePath) {
    ifstream file(filePath);
    if (!file) {
        throw runtime_error("�޷����ļ�: " + filePath);
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// д���ļ���������ƶȣ�
void writeFile(const string& filePath, double similarity) {
    ofstream file(filePath);
    if (!file) {
        throw runtime_error("�޷�������ļ�: " + filePath);
    }
    file.precision(2);
    file << fixed << similarity << endl;
}

