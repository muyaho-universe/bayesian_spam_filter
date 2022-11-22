#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <istream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;
#define HAM_SIZE 100;
#define SPAM_SIZE 100;
vector<string> split(string str, char delimiter);

int main(int argc, char *argv[]){
    // list<char> special {'\'', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '<', '>', '?', '/'};
    list<string> special {"\'", "~", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "<", ">", "?", "/"};
    list<string> stopwords_list;
    map<string, int> word_in_ham;
    map<string, int> word_in_spam;
    string str_buf;

    ifstream train_file_ham(".\\csv\\train\\dataset_ham_train100.csv");
    fstream train_file_spam(".\\csv\\train\\dataset_spam_train100.csv");

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
    
          
    int i = 1;
    if(train_file_ham.is_open()){
        while (getline(train_file_ham,str_buf,',')){
            if(i==3){
                vector<string> result = split(str_buf, ' ');
                for (int j=0; j < result.size(); j++){
                    if((find(stopwords_list.begin(),stopwords_list.end(), result[j]) != stopwords_list.end()) && (find(special.begin(),special.end(), result[j]) != special.end())){
                        ++word_in_ham[result[j]];
                        cout <<result[j] << " : " << word_in_ham[result[j]] << endl;
                    }
                }
                i = 1;
            }
            i++;
        }
        train_file_ham.close();
    }

    i = 1;
    if(train_file_spam.is_open()){
        while (getline(train_file_spam,str_buf,',')){
            if(i==3){
                vector<string> result = split(str_buf, ' ');
                for (int j=0; j < result.size(); j++){
                    // cout << result[j] << endl;
                }
                i = 1;
            }
            i++;
        }
        train_file_spam.close();
    }

    // train_file_ham.close();
    // train_file_spam.close();
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