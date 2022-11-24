#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <istream>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <Windows.h>

using namespace std;
#define TRAIN_HAM_SIZE 100
#define TRAIN_SPAM_SIZE 100
#define TEST_HAM_SIZE 20
#define TEST_SPAM_SIZE 20
vector<string> split(string str, char delimiter);

int main(int argc, char *argv[]){
    SetConsoleOutputCP(CP_UTF8);
    list<string> special {"\'", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "<", ">", "?", "/", ".", ",", "\n", " ", ":", ";", "", "-", "\"\"", "_", "{", "}", "[", "]", "|"};
    list<string> stopwords_list;
    map<string, int> word_in_ham;
    map<string, int> word_in_spam;
    string str_buf;

    ifstream train_file_ham(".\\csv\\train\\dataset_ham_train100.csv");
    ifstream train_file_spam(".\\csv\\train\\dataset_spam_train100.csv");

    bool first = false;
    bool second = false;

    string line;
	ifstream stopwords_file("stopwords.txt"); 
	if(stopwords_file.is_open()){
		while(getline(stopwords_file, line)) {
            stopwords_list.push_back(line);
		}
		stopwords_file.close();
	} else {
		cout << "Unable to open file";
	}
    // for(string s : stopwords_list){
    //     cout << s << endl;
    // }
    
    // bool a =  find(special.begin(),special.end(), "\"\"") == special.end();
    // if(a) cout<< "yes" <<endl;
    // else cout <<"no" << endl;
    int i = 2;
    
    
    if(train_file_ham.is_open()){
        list<string> text_input;
        while (getline(train_file_ham,str_buf,',')){
            // cout << "\nnew line!!" << endl;
            vector<string> line = split(str_buf, '\n');
            // cout <<"In line: ";
            // for(string t : line){
            //     cout << t << " // ";
            // } 
            // cout <<endl;
            
            if(first){
                // vector<string> words = split
               cout <<"In line: ";
                for(string t : line){
                    cout << t << " // ";
                } 
                cout <<endl;
                string t1 =to_string(i);
                // cout << "t1: " << t1 << endl;
                if(i == 101){
                    if((line.size() > 1)&&(line.at(line.size()-1)[line.at(line.size()-1).size()-1] == '\"')){        // text가 끝나면
                        cout << "진짜 끝!!" << endl;
                        i ++;
                        first = false;
                    }
                    else{

                    }
                }
                else{
                    if((line.size() > 1)&&(line.at(line.size()-2)[line.at(line.size()-2).size()-1] == '\"')&&(line.at(line.size()-1) == t1)){        // text가 끝나면
                        cout << "문자 끝!!" << endl;
                        i ++;
                        first = false;
                    }
                    else{

                    }
                }
                
                //         string t = line.at(line.size()-1);
                //         t = t.substr(0, t.size()-2);
                //         // cout  <<"1: " << t << endl;
                //         text_input.push_back(t);
                // }
                // if(!second){
                //     if(line.at(0)[line.at(0).size()-1] == '\"'){
                //         string t = line.at(line.size()-1);
                //         t = t.substr(0, t.size()-2);
                //         // cout  <<"1: " << t << endl;
                //         text_input.push_back(t);
                //     }
                //     if(line.at(line.size()-1)[line.at(line.size()-1).size()-1] == '\"'){
                //         string t = line.at(line.size()-1);
                //         t = t.substr(0, t.size()-2);
                //         // cout  <<"1: " << t << endl;
                //         text_input.push_back(t);
                //         second = true;
                //     }
                //     else
                //     {
                //         for(string t : line)
                //         {
                //             // cout  << "2: "<< t << endl;
                //             // text_input.push_back(t);
                //         }
                //         // cout << "i: " << i;
                //         // i++;
                //     }
                // }
                // if(second){
                //     for(string t : text_input) {
                //         vector<string> result = split(str_buf, ' ');
                //         for(int j=0; j < result.size(); j++){
                //             if((find(stopwords_list.begin(),stopwords_list.end(), result[j]) == stopwords_list.end()) && (find(special.begin(),special.end(), result[j]) == special.end())){
                //                 // if()
                //                 // cout  << "result["<<j<<"]:"  <<result[j] << endl;
                //                 ++word_in_ham[result[j]];
                //             }
                //         }
                //     }
                //     text_input.clear();
                //     first = false;
                //     second = false;
                // }
            }
            else{
                if(line.at(0) == "ham"){
                    // cout << line.at(0) << endl;
                    first = true;
                }
                // if((line.size()>1) && (line.at(1) == "ham"))
                // {
                //     string t = line.at(2);
                //     t = t.substr(1, t.size()-1);
                //     cout << "3: " << t << endl;
                //     text_input.push_back(t);
                //     first = true;
                // }   
            }
        }
        train_file_ham.close();
    }
    cout << word_in_ham["houston"] << endl;
    // i = 1;
    // if(train_file_spam.is_open()){
    //     while (getline(train_file_spam,str_buf,',')){
    //         if(i==3){
    //             vector<string> result = split(str_buf, ' ');
    //             for (int j=0; j < result.size(); j++){
    //                 int npos;
    //                 npos = result[j].find_first_not_of(' ');
    //                 result[j].erase(0, npos);
    //                 npos = result[j].find_last_not_of(' ');
	//                 result[j].erase(npos+1);
    //                 //  cout <<result[j] << endl;
    //                 if(result[j].find('\n') > 0){
    //                    vector<string> result2 = split(result[j], '\n');
    //                    for (int k = 0; k < result2.size(); k++)
    //                    {
    //                     if((find(stopwords_list.begin(),stopwords_list.end(), result2[k]) == stopwords_list.end()) && (find(special.begin(),special.end(), result2[k]) == special.end())){
    //                         ++word_in_spam[result2[k]];
    //                         // cout <<result2[k] << " from 2: " << word_in_spam[result2[k]] << endl;
    //                     }
    //                    }
    //                 }
    //                 else{
    //                     if((find(stopwords_list.begin(),stopwords_list.end(), result[j]) == stopwords_list.end()) && (find(special.begin(),special.end(), result[j]) == special.end())){
    //                         ++word_in_spam[result[j]];
    //                         // cout <<result[j] << " from 1: " << word_in_spam[result[j]] << endl;
    //                     }
    //                 }
    //             }
    //             i = 1;
    //         }
    //         i++;
    //     }
    //     train_file_spam.close();
    // }
   

    // ifstream test_file_ham(".\\csv\\test\\dataset_ham_test20.csv");
    // ifstream test_file_spam(".\\csv\\test\\dataset_spam_test20.csv");
    // i = 1;
    // double threshold = 0.8;
    // int count_spam = 0;
    // int count_ham = 0;
    // list<int> p;        // spam
    // list<int> q;        // not spam 
    // int c = 0;
    // if(test_file_ham.is_open()){
    //     while (getline(test_file_ham,str_buf,',')){
    //         c++;
    //         if(i==3){
    //             vector<string> result = split(str_buf, ' ');                
    //             for (int j=0; j < result.size(); j++){
    //                 int npos;
    //                 npos = result[j].find_first_not_of(' ');
    //                 result[j].erase(0, npos);
    //                 npos = result[j].find_last_not_of(' ');
	//                 result[j].erase(npos+1);
    //                  cout <<result[j] << endl;
    //                 if(result[j].find('\n') > 0){
    //                    vector<string> result2 = split(result[j], '\n');
    //                    for (int k = 0; k < result2.size(); k++)
    //                    {
    //                     if((find(stopwords_list.begin(),stopwords_list.end(), result2[k]) == stopwords_list.end()) && (find(special.begin(),special.end(), result2[k]) == special.end())){
    //                         p.push_back(word_in_spam[result2[k]]);
    //                         q.push_back(word_in_ham[result2[k]]);
    //                     }
                            
    //                    }
                       
    //                 }
    //                 else{
    //                     if((find(stopwords_list.begin(),stopwords_list.end(), result[j]) == stopwords_list.end()) && (find(special.begin(),special.end(), result[j]) == special.end())){
    //                         p.push_back(word_in_spam[result[j]]);
    //                         q.push_back(word_in_ham[result[j]]);
    //                     }
    //                 }
    //             }
                
    //             i = 1;
    //         }
    //         i++;
    //     }
    //     cout << c << endl;
    //     train_file_ham.close();
    // }
    // int all_p = 1;
    // double p_v;
    // for(int t : p){
    //     all_p *= t;
    // }
    // p_v = all_p / pow(TRAIN_SPAM_SIZE, p.size());

    // int all_q = 1;
    // double q_v;
    // for(int t : q){
    //     all_q *= t;
    // }
    // q_v = all_q / pow(TRAIN_HAM_SIZE, q.size());
    // double r;
    // r = p_v/ (p_v + q_v);

    // if(r > threshold) count_spam++;
    // else count_ham++;
    
    // cout << count_spam << endl;

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