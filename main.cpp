#include "Paper-plagiarism-check.h"
using namespace std;

const char* const DICT_PATH = "dict/jieba.dict.utf8";
const char* const HMM_PATH = "dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "dict/user.dict.utf8";
const char* const IDF_PATH = "dict/idf.utf8";
const char* const STOP_WORD_PATH = "dict/stop_words.utf8";


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "�÷�: " << argv[0] << " <ԭ���ļ�·��> <��Ϯ���ļ�·��> <����ļ�·��>" << endl;
        return 1;
    }
    try {
        // ��ʼ��cppjieba
        cppjieba::Jieba jieba(DICT_PATH, HMM_PATH, USER_DICT_PATH, IDF_PATH, STOP_WORD_PATH);

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