#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <istream>
#include <list>

using namespace std;

vector<string> csv_read_row(istream &file, char delimiter);

int main(int argc, char *argv[]){
    list<char> special {'\'', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '<', '>', '?', '/'};
    string str_buf;
    for(char t: special){
        cout << t << endl;
    }

    fstream train_file_ham;
    train_file_ham.open(".\\csv\\train\\dataset_ham_train100.csv");
    fstream train_file_spam;
    train_file_spam.open(".\\csv\\train\\dataset_spam_train100.csv");

    int i = 1;
    // while(!train_file_ham.eof()){
    //     getline(train_file_ham,str_buf,',');
    //     if(i==3){
    //         cout<<str_buf<<endl;
    //         i = 1;
    //     }
    //     i++; 
    //     cout << "야호!!"<<endl;      
    // }
    // i = 1;
    // while(!train_file_spam.eof()){
    //     getline(train_file_spam,str_buf,',');
    //     if(i==3){
    //         cout<<str_buf<<endl;
    //         i = 1;
    //     }
    //     i++; 
    //     cout << "무야호!!"<<endl;      
    // }
    train_file_ham.close();
    train_file_spam.close();
    return 0;
}

// vector<string> csv_read_row(istream &file, char delimiter){
//     stringstream ss;
//     bool inquotes = false;
//     vector<string> row;

//     while (file.good()){
//         char c = file.get();
        
//         if(!inquotes && c == '""'){
//             inquotes =true;
//         }
//         else if (inquotes && c == '""'){
//             if( file.peek() == '"'){
//                 ss << (char) file.get();
//             }
//             else{
//                 inquotes = false;
//             }
//         }
//         else if (!inquotes && c == delimiter){
//            row.push_back(ss.str());
//            ss.str("");
//         }
//         else if (!inquotes && (c =='\r' || c == '\n')){
//             if(file.peek() =='\n') {file.get();}
//             row.push_back(ss.str());
//             return row;
//         }
//         else{
//             ss << c;
//         }
//     }
// }