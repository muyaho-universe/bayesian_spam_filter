#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
// #include <Windows.h>

using namespace std;
#define TRAIN_HAM_SIZE 100
#define TRAIN_SPAM_SIZE 100
#define TEST_HAM_SIZE 20
#define TEST_SPAM_SIZE 20
vector<string> split(string str, char delimiter);
bool cmp(const pair<string, int> &a, const pair<string, int> &b);

int main(int argc, char *argv[]) {
    // SetConsoleOutputCP(CP_UTF8);
    list<string> special{"\'", "~",  "!", "@", "#", "$", "%", "^", "&", "*",  "(",  ")", "-", "<", ">", "?", "/", ".", ",",  "\n", " ", ":", ";", "",  "-", "\"", "\'", "_", "{",  "}",  "[", "]", "|", "\"\""}; //, "\"Subject:"
    list<string> stopwords_list;
    map<string, int> word_in_ham;
    map<string, int> word_in_spam;
    string str_buf;

    //   ifstream train_file_ham("./csv/train/dataset_ham_train100.csv");
    ifstream train_file_ham(".\\csv\\train\\dataset_ham_train100.csv");

    ifstream train_file_spam(".\\csv\\train\\dataset_spam_train100.csv");
//   ifstream train_file_spam("./csv/train/dataset_spam_train100.csv");

    bool first = false;
    bool second = false;

    string line;
    ifstream stopwords_file("stopwords.txt");
    if (stopwords_file.is_open()) {
        while (getline(stopwords_file, line)) {
            stopwords_list.push_back(line);
        }
        stopwords_file.close();
    } 
    else {
        cout << "Unable to open file";
    }
    // for(string s : stopwords_list){
  //     cout << s << endl;
  // }

  // bool a =  find(special.begin(),special.end(), ".") == special.end();
  // if(a) cout<< "yes" <<endl;
  // else cout <<"no" << endl;
    int i = 2;

    if (train_file_ham.is_open()) {
        list<string> text_input;
        while (getline(train_file_ham, str_buf, ',')) {
            vector<string> line = split(str_buf, '\n');
            if (first) {
                string t1 = to_string(i);
                set<string> one_data;
                if (i == 101) {
                    if ((line.size() > 1) && (line.at(line.size() - 1)[line.at(line.size() - 1).size() - 1] == '\"')) { // 진짜 끝나면
                        for (int a = 0; a < line.size(); a++) {
                            string t = line[a];
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if (a == (line.size() - 1) && word[word.length() - 1] == '\"') {
                                    word = word.substr(0, word.length() - 1);
                                }
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    // cout << "last word: " << word << endl;
                                    // ++word_in_ham[word];
                                    one_data.insert(word);
                                }
                            }
                        }
                        for(string t : one_data){
                            if(word_in_ham[t] == 0) {
                                word_in_ham[t]= word_in_ham[t] + 1;
                                cout << "insert ";
                            }
                            else word_in_ham[t]= word_in_ham[t] + 1;
                            cout << "last t: " << t << " word_in_ham[t]: "<< word_in_ham[t] << endl;
                        }
                        i++;
                        first = false;
                    } 
                    else {
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                    }
                } 
                else {
                    if ((line.size() > 1) && (line.at(line.size() - 2)[line.at(line.size() - 2).size() - 1] == '\"') && (line.at(line.size() - 1) == t1)) { // text가 끝나면
                        for (int a = 0; a < line.size() - 1; a++) {
                            string t = line[a];
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if (a == (line.size() - 2) && word[word.length() - 1] == '\"') {
                                    word = word.substr(0, word.length() - 1);
                                }
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    // cout << "word: " << word <<endl;
                                    one_data.insert(word);
                                }
                            }
                        }
                        i++;
                        for (string t : one_data) {
                            if(word_in_ham[t] == 0) {
                                word_in_ham[t]= word_in_ham[t] + 1;
                                cout << "insert ";
                            }
                            else word_in_ham[t]= word_in_ham[t] + 1;
                            // word_in_ham[t] = ++word_in_ham[t];
                           cout << "t: " << t << " word_in_ham[t]: "<< word_in_ham[t] << endl;
                        }
                        one_data.clear();
                        first = false;
                    } 
                    else {  // 끝 문자가 아닐 때
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    // cout << "word: " << word <<endl;
                                    one_data.insert(word);
                                }
                            }
                        }
                    }
                }
            } 
            else {
                if (line.at(0) == "ham") {
                    first = true;
                }
            }
        }
        train_file_ham.close();
    }
    // cout << word_in_ham["http123"] << endl;
    i = 2;
    if (train_file_spam.is_open()) {
        list<string> text_input;
        while (getline(train_file_spam, str_buf, ',')) {
            vector<string> line = split(str_buf, '\n');
            if (first) {
                string t1 = to_string(i);
                if (i == 101) {
                    if ((line.size() > 1) && (line.at(line.size() - 1)[line.at(line.size() - 1).size() - 1] == '\"')) { // 진짜 끝나면
                        for (int a = 0; a < line.size(); a++) {
                            string t = line[a];
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if (a == (line.size() - 1) && word[word.length() - 1] == '\"') {
                                    word = word.substr(0, word.length() - 1);
                                }
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    ++word_in_spam[word];
                                }
                            }
                        }

                        i++;
                        first = false;
                    } 
                    else {
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                                for (string word : words) {
                                    if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                    // cout  << "word " <<word << endl;
                                        ++word_in_spam[word];
                                    }
                                }
                        }
                    }
                } 
                else {
                    if ((line.size() > 1) && (line.at(line.size() - 2)[line.at(line.size() - 2).size() - 1] == '\"') && (line.at(line.size() - 1) == t1)) { // text가 끝나면
                        for (int a = 0; a < line.size() - 1; a++) {
                            string t = line[a];
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if (a == (line.size() - 2) && word[word.length() - 1] == '\"') {
                                    word = word.substr(0, word.length() - 1);
                                }
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    ++word_in_spam[word];
                                }
                            }
                        }
                        i++;
                        first = false;
                    } 
                    else {
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    ++word_in_spam[word];
                                }
                            }
                        }
                    }
                }
            } 
            else {
                if (line.at(0) == "spam") {
                    first = true;
                }
            }
        }
        train_file_spam.close();
    }
    vector<pair<string, int>> words_in_ham_order(word_in_ham.begin(), word_in_ham.end());
    vector<pair<string, int>> words_in_spam_order(word_in_spam.begin(), word_in_spam.end());
    sort(words_in_ham_order.begin(), words_in_ham_order.end(), cmp);
    cout << words_in_ham_order.at(0).first << " : " << words_in_ham_order.at(0).second << endl;

    return 0;
}

vector<string> split(string input, char delimiter) {
    vector<string> string_vector;
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        string_vector.push_back(temp);
    }

    return string_vector;
}

bool cmp(const pair<string, int> &a, const pair<string, int> &b) {
    if (a.second == b.second)
        return a.first > b.first;
    return a.second > b.second;
}