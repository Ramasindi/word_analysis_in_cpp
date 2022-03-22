#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Removes unwanted charracters from string
string clean_string(string input_string) {
    string output_string="";
    for (unsigned int i=0;i<input_string.length();i++) {
        switch (input_string[i]) {
            case ','   :
            case '!'   :
            case '.'   :
                        break;
            default    :
                        output_string+=input_string[i];
        }
    }
    return output_string;
}

//Loads a text file into a vector of words
vector<string> load_file_into_vector(string filename) {
    vector<string> word_list;
    ifstream file_handle(filename.c_str());
    if (file_handle.good()) {
        string word_string;
        while (true) {
            file_handle >> word_string;
            word_string=clean_string(word_string);
            word_list.push_back(word_string);
            if (file_handle.eof())
                break;
        }
    }
    return word_list;
}

//TODO: Develop word_type and member functions
struct word_type{
    string word;
    bool verb = false;
    bool noun = false;
    void print();
    void set_verb_status(vector<string> verb_strings);
    void set_noun_status(vector<string> noun_strings);
};
void word_type::print(){
    cout << "Word: " << std::boolalpha << word << "\n\t+Verb: " << verb << "\n\t+Noun: " << noun << endl;
};
void word_type::set_verb_status(vector<string> verb_strings){
    unsigned int i;
    for(i=0;i<verb_strings.size();i++){
        if(verb_strings[i] == word)
        {
            verb = true;
            return;
        }
    }
};
void word_type::set_noun_status(vector<string> noun_strings){
    unsigned int i;
    for(i=0;i<noun_strings.size();i++){
        if(noun_strings[i] == word){
            noun = true;
            return;
        }
    }
};
//TODO: Develop book_type and member functions
struct book_type{
    vector<string> string_list;
    book_type(string file_name){
        string_list = load_file_into_vector(file_name);
    };
    int find(string word);
    int count(string word);
};
int book_type::find(string word){
    unsigned int i;
    for(i=0;i<string_list.size();i++){
        if(string_list[i] == word){
            return i;//when the word is found
        }
    }
    return -1;//when a word is not found
};
int book_type::count(string word){
    int num_occurences = 0;
    unsigned int i;
    for(i =0;i<string_list.size();i++){
        if(string_list[i] == word){num_occurences++;}
    }
    return num_occurences;
};
int main() {
    //TODO: Read input from console
    word_type my_word_type;
    cout << "Please provide the search word: \n";
    cin >> my_word_type.word;
    //TODO: Load book and word lists
    book_type my_book_type("book.txt");
    //TODO: Determine if input word is a verb or a noun and print information
    vector<string> verbs_strings = load_file_into_vector("verbs.txt");
    vector<string> nouns_strings = load_file_into_vector("nouns.txt");
    my_word_type.set_verb_status(verbs_strings);
    my_word_type.set_noun_status(nouns_strings);
    my_word_type.print();
    //TODO: Find index of first occurrence
    cout << "The word " << my_word_type.word << " is word number " << my_book_type.find(my_word_type.word) << " in the book" << endl;
    //TODO: Count how many times the word occurs in the book
    cout << "Number of occurrences " << my_book_type.count(my_word_type.word) << endl;
    return 0;
}

