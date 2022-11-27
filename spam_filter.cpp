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

using namespace std;
#define TRAIN_HAM_SIZE 100
#define TRAIN_SPAM_SIZE 100
#define TEST_HAM_SIZE 20
#define TEST_SPAM_SIZE 20
vector<string> split(string str, char delimiter);
bool cmp(const pair<string, int> &a, const pair<string, int> &b);
void file_parsing(string file_name, map<string, int>& words_map, string type); 
int test_parsing(string file_name, map<string, int> words_map1, map<string, int> words_map2, string type);

int main(int argc, char *argv[]) {
    list<string> special{"+","\'", "~",  "!", "@", "#", "$", "%", "^", "&", "*",  "(",  ")", "-", "<", ">", "?", "/", ".", ",",  "\n", " ", ":", ";", "",  "-", "\"", "\'", "_", "{",  "}",  "[", "]", "|", "\"\"", "\"Subject:"}; //, 
    map<string, int> word_in_ham;
    map<string, int> word_in_spam;
    // for macOS "./csv/train/dataset_ham_train100.csv"  use this form. This code is for window OS.
    string ham_file = ".\\csv\\train\\dataset_ham_train100.csv";
    string spam_file = ".\\csv\\train\\dataset_spam_train100.csv";
    string test_ham_file = ".\\csv\\test\\dataset_ham_test20.csv";
    string test_spam_file = ".\\csv\\test\\dataset_spam_test20.csv";
    
    file_parsing(ham_file, word_in_ham,  "ham");
    file_parsing(spam_file, word_in_spam,  "spam");

    int ham_ham = test_parsing(test_ham_file, word_in_ham, word_in_spam,  "ham");
    cout << "==============================================" << endl;
    int spam_spam = test_parsing(test_spam_file, word_in_ham, word_in_spam,  "spam");
    cout << "==============================================" << endl;
    cout << "ham_ham: " << ham_ham << " spam_spam: " << spam_spam << endl;
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

void file_parsing(string file_name, map<string, int>& words_map, string type){
    list<string> special{"+","\'", "~",  "!", "@", "#", "$", "%", "^", "&", "*",  "(",  ")", "-", "<", ">", "?", "/", ".", ",",  "\n", " ", ":", ";", "",  "-", "\"", "\'", "_", "{",  "}",  "[", "]", "|", "\"\"", "\"Subject:"};
    int i = 2;
    string ham_spam = type;
    int stop = 101;
    bool test = false;
    
    ifstream file(file_name);
    string str_buf;
    bool first = false;
    set<string> one_data;

    if (file.is_open()) {
        list<string> text_input;
        while (getline(file, str_buf, ',')) {
            vector<string> line = split(str_buf, '\n');
            if (first) {
                string t1 = to_string(i);
                if (i == stop) {
                    if ((line.size() > 1) && (line.at(line.size() - 1)[line.at(line.size() - 1).size() - 1] == '\"')) { // 진짜 끝나면
                        for (int a = 0; a < line.size(); a++) {
                            string t = line[a];
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if (a == (line.size() - 1) && word[word.length() - 1] == '\"') {
                                    word = word.substr(0, word.length() - 1);
                                }
                                if ((find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                        for (string t : one_data) {
                           if(words_map[t] == 0) {
                                words_map[t]= words_map[t] + 1;
                            }
                            else words_map[t]= words_map[t] + 1;
                        }
                        one_data.clear();
                        i++;
                        first = false;
                    } 
                    else {
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(special.begin(), special.end(), word) == special.end())) {
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
                                if ((find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                        i++;
                        for (string t : one_data) {
                           if(words_map[t] == 0) {
                                words_map[t]= words_map[t] + 1;
                            }
                            else words_map[t]= words_map[t] + 1;
                        }
                        one_data.clear();
                        first = false;
                    } 
                    else {  // 끝 문자가 아닐 때
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                    }
                }
            } 
            else {
                if (line.at(0) == ham_spam) {
                    first = true;
                }
            }
        }
        file.close();
    }
}
int test_parsing(string file_name, map<string, int> words_map1, map<string, int> words_map2, string type){
    list<string> special{"+","\'", "~",  "!", "@", "#", "$", "%", "^", "&", "*",  "(",  ")", "-", "<", ">", "?", "/", ".", ",",  "\n", " ", ":", ";", "",  "-", "\"", "\'", "_", "{",  "}",  "[", "]", "|", "\"\"", "\"Subject:"};
    int i = 102;
    string ham_spam = type;
    int stop = 121;
    
    ifstream file(file_name);
    string str_buf;
    bool first = false;
    set<string> one_data;

    int count = 0;
    double threshold = 0.6; 
    int popo = 0;
    if (file.is_open()) {
        list<string> text_input;
        while (getline(file, str_buf, ',')) {
            vector<string> line = split(str_buf, '\n');
            if (first) {
                string t1 = to_string(i);
                if (i == stop) {
                    if ((line.size() > 1) && (line.at(line.size() - 1)[line.at(line.size() - 1).size() - 1] == '\"')) { // 진짜 끝나면
                        for (int a = 0; a < line.size(); a++) {
                            string t = line[a];
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if (a == (line.size() - 1) && word[word.length() - 1] == '\"') {
                                    word = word.substr(0, word.length() - 1);
                                }
                                if ((find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                       double p = 1.0;
                        double q = 1.0;
                        double r = 0.0;
                        for (string t : one_data) {
                            if((words_map1[t]!= 0) && (words_map2[t]!= 0)){
                                p *= ((double)words_map2[t]/100.0);
                                q *= ((double) words_map1[t]/100.0);
                            }
                        }
                        r  = p/(p+q);
                        popo++;
                        cout << popo << ": "<<"p: " << p << " q: " << q << " " << "threshold: " << threshold << " r: " << r << endl;
                        if(threshold> r){
                            cout << "Ham!!" << endl; 
                            (type == "ham") ? count++: 0;
                        }
                        else{
                            cout <<  "Spam!!"  << endl; 
                            (type == "spam") ? count++: 0;
                        }
                        i++;
                        first = false;
                    } 
                    else {
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(special.begin(), special.end(), word) == special.end())) {
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
                                if ((find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                        i++;
                        double p = 1.0;
                        double q = 1.0;
                        double r = 0.0;
                        for (string t : one_data) {
                            if((words_map1[t]!= 0) && (words_map2[t]!= 0)){
                                p *= ((double)words_map2[t]/100.0);
                                q *= ((double) words_map1[t]/100.0);
                            }
                        }
                        r  = p/(p+q);
                        popo++;
                        cout << popo << ": "<<"p: " << p << " q: " << q << " ";
                        cout << "threshold: " << threshold << " r: " << r << endl;
                        if(threshold> r){
                            cout << "Ham!!" << endl; 
                            (type == "ham") ? count++: 0;
                        }
                        else{
                            cout <<  "Spam!!"  << endl; 
                            (type == "spam") ? count++: 0;
                        }
                        
                        one_data.clear();
                        
                        first = false;
                    } 
                    else {  // 끝 문자가 아닐 때
                        for (string t : line) {
                            vector<string> words = split(t, ' ');
                            for (string word : words) {
                                if ((find(special.begin(), special.end(), word) == special.end())) {
                                    one_data.insert(word);
                                }
                            }
                        }
                    }
                }
            } 
            else {
                if (line.at(0) == ham_spam) {
                    first = true;
                }
            }
        }
        file.close();
    }
    return count;
}