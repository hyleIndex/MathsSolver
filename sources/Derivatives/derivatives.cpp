#include "derivatives.hpp"
#include "Tokenizer.hpp"
//#include "MainWindow/mainwindow.h"


#include <QApplication>
#include <QtTest>
#include <sstream>
#include <iostream>




map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};

AF::AF(vector<Token> fun){
    end = false;
    type = 1;
    vect_label = fun;
    in_str_label = vect_to_str(fun);
    cout << in_str_label << '\n';
    // parentheses(&fun);

    if (int(fun.size()) == 1 && (fun[0].is_super_token() == false)){
        end = true;
        assign(fun[0],leaf);
        left = nullptr;right = nullptr;



    }else{
     if (int(fun.size()) == 1 && fun[0].is_super_token()){
                fun = simplify(fun[0].get_value(),'x');
     }
    operation =  Operator();
    int counter = 0;
    vector<Token>::iterator j = fun.begin();
    for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
        if (i->get_type() > 0){
            int val = type_m[i->get_value()];
            //cout << val<< "  " << i-> get_value()<<'\n';
            if ( val == 7){counter += 1;}
            else if (val == 8){counter -= 1;}
            else if (val > type_m[operation.get_value()] and counter == 0){
                operation = Operator(i->get_value());
                j = i;
            }

        }


    }
    //cout << "string is " << in_str_label<<'\n';
    //cout << "Operation: " << operation.get_value()<< " and val "<<operation.get_type() << '\n';
    if (type_m[operation.get_value()] > 0){
        //cout << "Im here" << in_str_label<<'\n';
        vector<Token> l, r;
        for (vector<Token>::iterator i = fun.begin();i<fun.end();i++){
            if (i<j){
                l.push_back(*i);
            }
            else if (i>j){
                r.push_back(*i);

            }
        }
        //cout << "left: "<< vect_to_str(l)<<" O: "<<j->get_value() << ". right: " << vect_to_str(r)<<'\n';


        if (fun[0].is_super_token()){
            l = simplify(fun[0].get_value(),'x');
        }
        if (fun[2].is_super_token()){
            r = simplify(fun[2].get_value(),'x');
        }
        left = new AF(l);
        right = new AF(r);

        str_label = left->get_str_label() + this->get_operation().get_value()+ right->get_str_label();


    } else {
        //cout << "not a success" << in_str_label <<'\n';
    }
    //cout << "success!" << in_str_label <<'\n';
    }}

void assign(Token fun,SF &leaf){
    int val = fun.get_type();
    if (val == -1){
        leaf = Fnum(fun);
    } else if (val == -2){
        string function = fun.get_value();
        if (function == "exp"){
            leaf = Fexp(fun);
        }
        if (function == "ln"){
            leaf = Fln(fun);
        }
        if (function == "log"){
            leaf = Flog(fun);
        }
        if (function == "cos"){
            leaf = Fcos(fun);
        }
        if (function == "sin"){
            leaf = Fsin(fun);
        }
        if (function == "tan"){
            leaf = Ftan(fun);
        }
        if (function == "sqrt"){
            leaf = Fsqrt(fun);
        }
    }else if (val == -3){
        leaf = Fvar(fun);
    }else if (val == -4){
        leaf = Fcomp(fun);
    }

}


AF::AF(AF left, AF right, Operator operation){
    this->left = &left;
    this->right = &right;
    end = false;
    this->operation = operation;
    this->str_label = "";
    this->in_str_label = "";

}

AF::AF(int type, Token end_token){
    this->left = nullptr;
    this->right = nullptr;
    this->operation = Operator();
    end = true;
    this->type = type;
    this->end_token = end_token;
}



AF AF:: get_left(){
    return *left;
}



void AF::set_left(AF *left){
    this->left = left;
}

AF AF:: get_right(){
    return *right;
}

void AF::set_right(AF *right){
    this->right = right;
}

string AF::get_string_operation(){
    return operation.get_value();
}

string vect_to_str(vector<Token> fun){
    string sfun = "";
    for (int i = 0; i< int(fun.size());i++){
        sfun += fun[i].get_value();
        if (i != int(fun.size())-1){
            sfun += " ";
        }
    }
    return sfun;
}

Operator AF::get_operation(){
    return operation;
}

void AF::set_operation(Operator operation){
    this->operation = operation;

}

string AF::get_str_label(){
    return str_label;
}

string AF::get_in_str_label(){
    return in_str_label;
}

string AF::display(){
    if (this->left == nullptr and this->right == nullptr){
        return get_in_str_label();
    }else{
        return "(" +get_left().display() + " " + operation.get_value() + " " + get_right().display() + ")";
    }
}


int SinF::get_type(){
    return type;
}
int CosF::get_type(){
    return type;
}
int Cons::get_type(){
    return type;
}
int Poly::get_type(){
    return type;
}
int Exp::get_type(){
    return type;
}
int Loga::get_type(){
    return type;
}
int AF::get_type(){
    return type;
}
void AF::set_type(int type){
    this->type = type;
}


AF sf_derivatives(SF &leaf){
    if (leaf.get_type() == 1){
        return AF({Num("1")});
    }else if (leaf.get_type() == 2 || leaf.get_type() == 3){
        return AF({Num("0")});
    }else{
        cout <<leaf.get_type()<< "wtf"<<'\n';return AF();/*else if (leaf.get_type() == 4){
        return AF({Function("exp")});
    }else if (leaf.get_type() == 5){
        return AF({Function("")});
    }*/}
}



SinF::SinF(Token val){
    value = val;
    str_label= "sin(" + value.get_value() +")";

}
SinF::SinF(){
    value = Token("x");
    str_label= "sin(" + value.get_value() +")";

}
AF SinF::to_AF(){
    return AF(2, Token());
}
Token SinF::get_value(){
    return value;
}
string SinF::get_str_label(){
    return str_label;
}

AF SinF::solve(){

    return CosF(value).to_AF();

}

CosF::CosF(Token val){
    value = val;
    str_label= "cos(" + value.get_value() +")";

}

CosF::CosF(){

    value = Token("x");
    str_label= "cos(" + value.get_value() +")";

}
AF CosF::to_AF(){
    return AF(1, Token());
}
Token CosF::get_value(){
    return value;
}
string CosF::get_str_label(){
    return str_label;
}

AF CosF::solve(){
    AF l = Cons(Token("-1")).to_AF();
    AF r = SinF(value).to_AF();
    return AF(l, r, Operator("*"));

}






Exp::Exp(Token base, Token val){

    this->base = base;

    this->value = val;

    str_label = base.get_value() + "^" + value.get_value();
}
AF Exp::to_AF(){
    return AF(3, get_base());
}
Token Exp::get_base(){
    return base;
}

Token Exp::get_value(){
    return value;
}
string Exp::get_str_label(){
    return str_label;
}
AF Exp::solve(){
    if(base.get_value() == "e"){
        return Exp(base, value).to_AF();
    }
    AF r = Loga(Token(base), Token("e")).to_AF();
    return AF(to_AF(), r, Operator("*"));

}




Cons::Cons(Token c){
    this->c = c;
    str_label = "";
}

AF Cons::to_AF(){
    return AF(6, get_c());
}
Token Cons::get_c(){
    return c;
}
string Cons::get_str_label(){
    return str_label;
}
AF Cons::solve(){
    return Cons(Token("0")).to_AF();
}




Loga::Loga(Token val, Token base){

    this->base = base;
    value = val;


    str_label= "log_" + base.get_value() + "(" +value.get_value() + ")";
    if(base.get_value() == "e"){
        str_label = "ln(" + value.get_value() + ")";
    }

}
AF Loga::to_AF(){
    return AF(4, get_base());
}
Token Loga::get_base(){
    return base;
}
Token Loga::get_value(){
    return value;
}
string Loga::get_str_label(){
    return str_label;
}
AF Loga::solve(){
    Token base = this->get_base();
    if(base.get_value() == "e"){
        AF l = Cons(Token("1")).to_AF();
        AF r = Poly(value, Token("1")).to_AF();
        return AF(l, r, Operator("/"));
    }
    AF l = Loga(base, Token("e")).to_AF();
    AF r = Poly(value, Token("1")).to_AF();
    AF step = AF(l, r, Operator("*"));
    AF c = Cons(Token("1")).to_AF();
    return AF(c, step, Operator("/"));

}







Poly::Poly(Token val, Token exponent){

    this->exponent = exponent;
    this->value = val;


    str_label = "";
}
AF Poly::to_AF(){
    return AF(5, get_exponent());
}
Token Poly::get_exponent(){
    return exponent;
}
Token Poly::get_value(){
    return value;
}
string Poly::get_str_label(){
    return str_label;
}
AF Poly::solve(){
    string new_exponent = exponent.get_value() + "-1";
    return AF(Cons(exponent).to_AF(), Poly(value, Token(new_exponent)).to_AF(), Operator("*"));

}


AF solve(AF Func){
    cout << "Current depth is: " <<Func.get_in_str_label() << '\n';
    if (Func.get_end() == false){

    int val = type_m[Func.get_operation().get_value()];
    if(val == 6){
        return AF(solve(Func.get_left()), solve(Func.get_right()), Operator("+"));

    }
    if(val == 5){
        return AF(solve(Func.get_left()), solve(Func.get_right()), Operator("-"));
    }
    if(val == 4){
        AF l= AF(solve(Func.get_left()), Func.get_right(), Operator("*"));
        AF r = AF(solve(Func.get_right()), Func.get_left(), Operator("*"));
        return AF(l, r, Operator("+"));

    }
    if(val == 3){
        AF l1= AF(solve(Func.get_left()), Func.get_right(), Operator("*"));
        AF r2 = AF(Func.get_left(), solve(Func.get_right()), Operator("*"));
        AF l2 = Poly(Token("x"), Token("2")).to_AF();
        return AF(AF(l1, r2, Operator("-")), AF(l2, Func.get_right(), Operator("~")), Operator("/"));
    }
    if(val == 2){
        // assuming no x in exponent
        AF left = AF(solve(Func.get_left()),Func.get_right(),Operator("*"));
        AF exponent = AF(Func.get_right(),AF({Num("1")}),Operator("-"));
        AF right = AF(Func.get_left(),exponent,Operator("^"));
        return  AF(left,right,Operator("*"));

    }
    if(val == 1){
        AF l = AF(solve(Func.get_left()), Func.get_right(), Operator("~"));
        return AF(l ,solve(Func.get_right()), Operator("*"));
    }else {cout << "couldn't find the right path"<<'\n';return AF();}
    } else {
        cout << "currently at the leaf: "<<Func.get_in_str_label()<<'\n';
        SF leaf = Func.get_leaf();
        return sf_derivatives(leaf);
        if(Func.get_type() == 1){
            CosF c = CosF();
            return c.solve();
        }
        if(Func.get_type() == 2){
            SinF s = SinF();
            return s.solve();
        }
        if(Func.get_type() == 3){
            return AF();
        }
        if(Func.get_type() == 4){
            return AF();
        }
        if(Func.get_type() == 5){
            return AF();
        }
        if(Func.get_type() == 6){
            return AF();
        }else return AF();

}

//map<string, int> type_m = {{"~",1},{"^",2},{"/",3},{"*",4},{"-",5},{"+",6},{"(",7},{")",8},{"_",9}};
}








