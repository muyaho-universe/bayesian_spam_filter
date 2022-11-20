#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;

vector<string> csv_read_row(istream &file, char delimiter);

int main(int argc, char *argv[]){
    string str_buf;

    fstream train_file_ham;
    train_file_ham.open(".\\csv\\train\\dataset_ham_train100.csv");
    fstream train_file_spam;
    train_file_spam.open(".\\csv\\train\\dataset_spam_train100.csv");

    // ifstream train_file_ham(".\\csv\\train\\dataset_ham_train100.csv");
    // ifstream train_file_spam(".\\csv\\train\\dataset_spam_train100.csv");
    
    // if(train_file_ham.fail()){
    //     return (cout << "햄 파일 없음" << endl) && 0;
    // }
    
    // if(train_file_spam.fail()){
    //     return (cout << "스팸 파일 없음" << endl) && 0;
    // }

    // while (train_file_ham.good()){
    //     vector<string> row = csv_read_row(train_file_ham, ',');
    //     if(!row[0].find("#")) continue;
    //     else{
    //         for (int i = 0, leng = row.size() - 2; i < leng; i++){
    //             cout << "[" << row[i] << "]" << "\t";
    //         }
    //         cout << endl;
    //     }
    // }

    while(!train_file_ham.eof()){
        getline(train_file_ham,str_buf,',');
        cout<<str_buf<<endl;        
    }
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