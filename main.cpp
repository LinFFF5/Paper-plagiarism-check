#include "Paper-plagiarism-check.h"
using namespace std;


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "�÷�: " << argv[0] << " <ԭ���ļ�·��> <��Ϯ���ļ�·��> <����ļ�·��>" << endl;
        return 1;
    }
    try {
        // ��ʼ��cppjieba
        cppjieba::Jieba jieba(
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/jieba.dict.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/hmm_model.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/user.dict.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/idf.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/stop_words.utf8"
        );

        // ��ȡ�ı�
        string originalText = readFile(argv[1]);
        string copiedText = readFile(argv[2]);

        // �ִ�
        vector<string> originalWords = tokenize(originalText, jieba);
        vector<string> copiedWords = tokenize(copiedText, jieba);

        // ���� IDF �ֵ䣨�������ı��м��㣩
        unordered_map<string, double> idfDict = computeIDF(originalWords, copiedWords);

        // ���� TF-IDF ����
        unordered_map<string, double> tfidfOriginal = calculateTFIDF(originalWords, idfDict);
        unordered_map<string, double> tfidfCopied = calculateTFIDF(copiedWords, idfDict);

        // ������� TF-IDF ���������ƶ�
        double similarity = cosineSimilarityTFIDF(tfidfOriginal, tfidfCopied);

        writeFile(argv[3], similarity);
        cout << "������ɣ����ƶ�: " << fixed << setprecision(2) << similarity << endl;
    }

    catch (const exception& e) {
        cerr << "����: " << e.what() << endl;
        return 1;
    }
    return 0;
}