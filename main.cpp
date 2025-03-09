#include "Paper-plagiarism-check.h"
using namespace std;


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "用法: " << argv[0] << " <原文文件路径> <抄袭版文件路径> <输出文件路径>" << endl;
        return 1;
    }
    try {
        // 初始化cppjieba
        cppjieba::Jieba jieba(
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/jieba.dict.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/hmm_model.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/user.dict.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/idf.utf8",
            "C:/Users/LinB/Desktop/c++/Paper plagiarism check/x64/Debug/dict/stop_words.utf8"
        );

        // 读取文本
        string originalText = readFile(argv[1]);
        string copiedText = readFile(argv[2]);

        // 分词
        vector<string> originalWords = tokenize(originalText, jieba);
        vector<string> copiedWords = tokenize(copiedText, jieba);

        // 计算 IDF 字典（从两个文本中计算）
        unordered_map<string, double> idfDict = computeIDF(originalWords, copiedWords);

        // 计算 TF-IDF 向量
        unordered_map<string, double> tfidfOriginal = calculateTFIDF(originalWords, idfDict);
        unordered_map<string, double> tfidfCopied = calculateTFIDF(copiedWords, idfDict);

        // 计算基于 TF-IDF 的余弦相似度
        double similarity = cosineSimilarityTFIDF(tfidfOriginal, tfidfCopied);

        writeFile(argv[3], similarity);
        cout << "查重完成，相似度: " << fixed << setprecision(2) << similarity << endl;
    }

    catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }
    return 0;
}