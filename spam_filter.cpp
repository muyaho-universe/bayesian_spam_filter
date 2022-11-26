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
void file_parsing(string file_name, map<string, int>& words_map, list<string> stopwords_list, string type); // 00 train_ham, 01 train_spam, 10 test_ham, 11 test_spam

int main(int argc, char *argv[]) {
    // SetConsoleOutputCP(CP_UTF8);
    list<string> special{"+","\'", "~",  "!", "@", "#", "$", "%", "^", "&", "*",  "(",  ")", "-", "<", ">", "?", "/", ".", ",",  "\n", " ", ":", ";", "",  "-", "\"", "\'", "_", "{",  "}",  "[", "]", "|", "\"\"", "\"Subject:"}; //, 
    list<string> stopwords_list;
    map<string, int> word_in_ham;
    map<string, int> word_in_spam;
    string str_buf;

    //   ifstream train_file_ham("./csv/train/dataset_ham_train100.csv");
    // ifstream train_file_ham(".\\csv\\train\\dataset_ham_train100.csv");
    string ham_file = ".\\csv\\train\\dataset_ham_train100.csv";
    string spam_file = ".\\csv\\train\\dataset_spam_train100.csv";
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
    
    file_parsing(ham_file, word_in_ham, stopwords_list, "00");
    vector<pair<string, int>> words_in_ham_order(word_in_ham.begin(), word_in_ham.end());
    cout << "==============================================" << endl;
    for (int i = 0; i < words_in_ham_order.size(); i++)
    {
        // cout << words_in_ham_order.at(i).first << " : " << words_in_ham_order.at(i).second << endl;
    }
    sort(words_in_ham_order.begin(), words_in_ham_order.end(), cmp);
    // sort(words_in_spam_order.begin(), words_in_spam_order.end(), cmp);
    cout << words_in_ham_order.at(1).first << " : " << words_in_ham_order.at(1).second << endl;
    

    // cout << word_in_ham["http123"] << endl;
    int i = 2;
    // if (train_file_spam.is_open()) {
    //     list<string> text_input;
    //     while (getline(train_file_spam, str_buf, ',')) {
    //         vector<string> line = split(str_buf, '\n');
    //         if (first) {
    //             string t1 = to_string(i);
    //             set<string> one_data;
    //             if (i == 101) {
    //                 if ((line.size() > 1) && (line.at(line.size() - 1)[line.at(line.size() - 1).size() - 1] == '\"')) { // 진짜 끝나면
    //                     for (int a = 0; a < line.size(); a++) {
    //                         string t = line[a];
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if (a == (line.size() - 1) && word[word.length() - 1] == '\"') {
    //                                 word = word.substr(0, word.length() - 1);
    //                             }
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 // cout << "last word: " << word << endl;
    //                                 // ++word_in_ham[word];
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                     for(string t : one_data){
    //                         if(word_in_spam[t] == 0) {
    //                             word_in_spam[t]= word_in_spam[t] + 1;
    //                             // cout << "insert ";
    //                         }
    //                         else word_in_spam[t]= word_in_spam[t] + 1;
    //                         // cout << "last t: " << t << " word_in_spam[t]: "<< word_in_spam[t] << endl;
    //                     }
    //                     i++;
    //                     first = false;
    //                 } 
    //                 else {
    //                     for (string t : line) {
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                 }
    //             } 
    //             else {
    //                 if ((line.size() > 1) && (line.at(line.size() - 2)[line.at(line.size() - 2).size() - 1] == '\"') && (line.at(line.size() - 1) == t1)) { // text가 끝나면
    //                     for (int a = 0; a < line.size() - 1; a++) {
    //                         string t = line[a];
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if (a == (line.size() - 2) && word[word.length() - 1] == '\"') {
    //                                 word = word.substr(0, word.length() - 1);
    //                             }
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 // cout << "word: " << word <<endl;
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                     i++;
    //                     for (string t : one_data) {
    //                        if(word_in_spam[t] == 0) {
    //                             word_in_spam[t]= word_in_spam[t] + 1;
    //                             // cout << "insert ";
    //                         }
    //                         else word_in_spam[t]= word_in_spam[t] + 1;
                           
    //                         // word_in_spam[t] = ++word_in_spam[t];
    //                     //    cout << "t t: " << t << " word_in_spam[t]: "<< word_in_spam[t] << endl;
    //                     }
    //                     one_data.clear();
    //                     first = false;
    //                 } 
    //                 else {  // 끝 문자가 아닐 때
    //                     for (string t : line) {
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 // cout << "word: " << word <<endl;
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         } 
    //         else {
    //             if (line.at(0) == "spam") {
    //                 first = true;
    //             }
    //         }
    //     }
    //     train_file_spam.close();
    // }
    // vector<pair<string, int>> words_in_ham_order(word_in_ham.begin(), word_in_ham.end());
    // vector<pair<string, int>> words_in_spam_order(word_in_spam.begin(), word_in_spam.end());
    // sort(words_in_ham_order.begin(), words_in_ham_order.end(), cmp);
    // sort(words_in_spam_order.begin(), words_in_spam_order.end(), cmp);
    // // cout << words_in_ham_order.at(0).first << " : " << words_in_ham_order.at(0).second << endl;
    // // cout << words_in_spam_order.at(0).first << " : " << words_in_spam_order.at(0).second << endl;
    // // bool isIn = false;
    // // int key = 0;
    // // for (int a = 0; a < words_in_ham_order.size(); a++)
    // // {
    // //     if(words_in_spam_order.at(0).first == words_in_ham_order.at(a).first){
    // //         isIn = true;
    // //         key = a;
    // //         break;
    // //     }
    // // }
    // // cout << "Yes " << words_in_ham_order.at(key).first << ": " << words_in_ham_order.at(key).second;
    // // cout << "Yeah " << words_in_spam_order.at(0).first << ": " << words_in_spam_order.at(0).second;

    // ifstream test_file_ham(".\\csv\\test\\dataset_ham_test20.csv");
    // ifstream test_file_spam(".\\csv\\test\\dataset_spam_test20.csv");

    // int count_ham = 0;
    // double threshold = 0.6; 
    // i = 102;
    // first = false;
    // if (test_file_ham.is_open()) {
    //     list<string> text_input;
    //     while (getline(test_file_ham, str_buf, ',')) {
    //         vector<string> line = split(str_buf, '\n');
    //         set<string> one_data;
    //         if (first) {
    //             // for(string t: line)
    //             // cout << t << endl;
    //             string t1 = to_string(i);
                
    //             if (i == 121) {
    //                 if ((line.size() > 1) && (line.at(line.size() - 1)[line.at(line.size() - 1).size() - 1] == '\"')) { // 진짜 끝나면
    //                     for (int a = 0; a < line.size(); a++) {
    //                         string t = line[a];
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if (a == (line.size() - 1) && word[word.length() - 1] == '\"') {
    //                                 word = word.substr(0, word.length() - 1);
    //                             }
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 // cout << "last word: " << word << endl;
    //                                 // ++word_in_ham[word];
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                     for(string t : one_data){
    //                         // cout << "last t: " << t << endl;
    //                     }
    //                     i++;
    //                     first = false;
    //                 } 
    //                 else {
    //                     for (string t : line) {
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                 }
    //             } 
    //             else {
    //                 if ((line.size() > 1) && (line.at(line.size() - 2)[line.at(line.size() - 2).size() - 1] == '\"') && (line.at(line.size() - 1) == t1)) { // text가 끝나면
    //                     bool go = false;
    //                     for (int a = 0; a < line.size() - 1; a++) {
    //                         string t = line[a];
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if (a == (line.size() - 2) && word[word.length() - 1] == '\"') {
    //                                 word = word.substr(0, word.length() - 1);
    //                                 go = true;
    //                             }
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 // cout << "word: " << word <<endl;
    //                                 one_data.insert(word);
    //                             }
    //                         }
    //                     }
    //                     if(go){
    //                         double p = 1.0;
    //                         double q = 1.0;
    //                         double r = 0.0;
    //                         cout << "one_data.size(): " << one_data.size() << endl;
    //                         for (string t : one_data) {
    //                             cout << t << " : " <<word_in_ham[t] << " : " << word_in_spam[t] << endl;
    //                             if((word_in_ham[t]!= 0) && (word_in_spam[t]!= 0)){
    //                                 cout << t << " is here!!" << endl;
    //                                 cout<< word_in_ham[t] << " : " << word_in_spam[t] << endl;
    //                                 p *= ((double)word_in_spam[t]/100.0);
    //                                 q *= ((double) word_in_ham[t]/100.0);
    //                                 // cout << "p: " << p << " q: " << q << endl;
    //                                 r  = p/(p+q);
    //                             }
    //                             go = false;
    //                         }
    //                         cout << "r: " << r << endl; 
    //                         if(threshold> r){
    //                             // cout << "Ham!!" << endl; 
    //                         }
    //                         else{
    //                             // cout <<  "Spam!!"  << endl; 
    //                         }
    //                          i++;
                        
    //                         // one_data.clear();
    //                         first = false;
    //                     }
    //                 } 
    //                 else {  // 끝 문자가 아닐 때
    //                     for (string t : line) {
    //                         vector<string> words = split(t, ' ');
    //                         for (string word : words) {
    //                             if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
    //                                 // cout << "word: " << word <<endl;
    //                                 one_data.insert(word);
    //                                 cout << "one_data.size() when not done: " << one_data.size() << endl;
    //                             }
    //                         }
    //                     }
    //                 }
    //             }
    //         } 
    //         else {
    //             if (line.at(0) == "ham") {
    //                 // cout << line.at(0) << endl;
    //                 first = true;
    //             }
    //         }
    //     }
    //     test_file_ham.close();
    // }

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

void file_parsing(string file_name, map<string, int>& words_map, list<string> stopwords_list, string type){
    list<string> special{"+","\'", "~",  "!", "@", "#", "$", "%", "^", "&", "*",  "(",  ")", "-", "<", ">", "?", "/", ".", ",",  "\n", " ", ":", ";", "",  "-", "\"", "\'", "_", "{",  "}",  "[", "]", "|", "\"\"", "\"Subject:"};
    int i = 2;
    string ham_spam = "1";
    int size = 100;
    int stop = 101;
    if(type == "00"){
        i = 2;
        ham_spam = "ham";
    }
    else if(type == "01"){
        i = 2;
        ham_spam = "spam";
        
    }
    else if(type == "10"){
        i = 102;
        ham_spam = "ham";
        size = 20;
        stop = 121;
    }
    else{
        i = 102;
        ham_spam = "spam";
        size = 20;
        stop = 121;
    }
    
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
                                if ((find(stopwords_list.begin(), stopwords_list.end(), word) == stopwords_list.end()) && (find(special.begin(), special.end(), word) == special.end())) {
                                    // cout << "last word: " << word << endl;
                                    // ++word_in_ham[word];
                                    one_data.insert(word);
                                }
                            }
                        }
                        for(string t : one_data){
                            if(words_map[t] == 0) {
                                words_map[t]= words_map[t] + 1;
                                // cout << "insert ";
                            }
                            else words_map[t]= words_map[t] + 1;
                            // cout << "last t: " << t << " words_map[t]: "<< words_map[t] << endl;
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
                        // cout << "one_data.size() just before mapping: " << one_data.size() << endl;
                        for (string t : one_data) {
                           if(words_map[t] == 0) {
                                words_map[t]= words_map[t] + 1;
                                // cout << "insert ";
                            }
                            else words_map[t]= words_map[t] + 1;
                           
                            // words_map[t] = ++words_map[t];
                        //    cout << "t: " << t << " words_map[t]: "<< words_map[t] << endl;
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
                                    // cout << "one_data.size() when not done: " << one_data.size() << endl;
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