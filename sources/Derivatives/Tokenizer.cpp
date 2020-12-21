#include "Tokenizer.hpp"


bool is_in_vector(vector< string > v, string elem){
    return (find(v.begin(), v.end(), elem) != v.end());
};

vector <string> functions{"cos", "sin", "exp", "tan", "sqrt", "log", "ln"};


vector <string> str_operators{"+", "-", "*" , "/", "^", "sqrt", "(", ")", "_", "~"};


Token::Token(){
    value = "";
    type = other;
}

Token::Token(string s){
    value = s;
 }

string Token::get_value(){
        return value;
    }

operator_type Token::get_type(){
    return type;
}

Operator::Operator():Token(){
    type = none;
}
Operator::Operator(string t): Token(t){
    if (t == "+"){
        type = addition;

    }
    if (t == "-"){
        type = sub;
    }
    if (t == "*"){
        type = mul;
    }
    if (t == "/"){
        type = divi;
    }
    if (t == "^"){
        type = power;

    }
    if (t == "~"){
            type = comp;
    }
    if (t == "(" or t == ")"){
        type = pare;
    }
    if (t == ""){
        type = none;
    }
    if (t == "_"){
        type = base;
    }
};

Operator::Operator(operator_type t){
    type = t;
}

operator_type Operator::get_type(){
    return type;
}

//the following function checks if the substring is a given function
bool is_function_(string s, string f){
    for (int i= 0; i < int(f.size()); i++){
        if (s[i] != f[i]){
            return false;
        }
    }
    return true;
}

//the following function checks if the substring contains any function
string find_function(string s){
    for (int j=0; j<(int(functions.size())); j++){
        string elem = functions[j];
        if (is_function_(s, elem)){
            return elem;
        }
    }
    return "";
}

//the following function takes as input a function under the form of a string and outputs a vector of tokens
vector<Token> simplify(string s, char variable){
    vector <Token> new_vector;
    int i=0;
    while (i < int(s.size())){
        //we ignore spaces of all types
        if ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n')){
            continue;
        }
        //first we consider the case of a letter
        if (isalpha(s[i])){
            //case 1 : we first check if it is the beginning of a function
            string s1 = s.substr(i, i+5);
            string potential_function = find_function(s1);
            //if it is the beginning of a function we add the corresponding token function to the new_vector
            if (potential_function != ""){
                new_vector.push_back(potential_function);
                i += int(potential_function.size())-1;
            }
            //case 2 : variable
            if (s[i] == variable){
                string c(1, s[i]);
                new_vector.push_back(Variable(c));
            }
            //otherwise : any constant
            else {
                string c(1, s[i]);
                new_vector.push_back(Num(c));
            }

        }
        //then we consider operators
        if (is_in_vector(str_operators, string(1,s[i]))){
                string c(1, s[i]);
                new_vector.push_back(Operator(c));
            }
        //then digits
        if (isdigit(s[i])){
                string c(1, s[i]);
                new_vector.push_back(Num(c));
            }
        i++;
}
    return new_vector;
};


