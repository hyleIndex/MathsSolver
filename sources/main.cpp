#include <QApplication>
#include <QtTest>
//#include "mainwindow.h"

//#include "MainWindow/mainwindow.h"
#include "Derivatives/derivatives.hpp"
//#include "ImageRecognition/imagePreprocessing.hpp"
#include "Derivatives/Tokenizer.hpp"
#include "NumericalSolver/num_derivation.hpp"
#include "NumericalSolver/num_integration.hpp"
#include "NumericalSolver/num_roots.hpp"
#include "Derivatives/derivatives.hpp"
#include "Equations/polynomial.hpp"
#include "Equations/matrix.hpp"
#include "Equations/gaussin.hpp"
#include "functionPreprocessing.hpp"


#include<iostream>
#include<string>
#include<math.h>
#include<vector>
//#include<opencv2/opencv.hpp>



using namespace std;

int main(int argc, char *argv[])
{
<<<<<<< HEAD
    Matrix A(3, 3), Y(3, 1);
    A.set_element(0, 0, 2);
    A.set_element(0, 1, 5);
    A.set_element(0, 2, 2);
    A.set_element(1, 0, 3);
    A.set_element(1, 1, -2);
    A.set_element(1, 2, 4);
    A.set_element(2, 0, -6);
    A.set_element(2, 1, 1);
    A.set_element(2, 2, -7);
    Y.set_element(0, 0, -38);
    Y.set_element(1, 0, 17);
    Y.set_element(2, 0, -12);

    Matrix D(2, 2);

    D.set_element(0,0, 1);
    D.set_element(0,1,2);
    D.set_element(1,0, 3);
    D.set_element(1,1,4);

    //D.power(2).print_mat();
    //D.power(3).print_mat();

    gaussian(A, Y);

    Matrix B(4, 4), X(4, 1);
    B.set_element(0, 0, -1);
    B.set_element(0, 1, 1);
    B.set_element(0, 2, -1);
    B.set_element(0, 3, 1);
    B.set_element(1, 0, -2);
    B.set_element(1, 1, 1);
    B.set_element(1, 2, 1);
    B.set_element(1, 3, -3);
    B.set_element(2, 0, 1);
    B.set_element(2, 1, 2);
    B.set_element(2, 2, -3);
    B.set_element(2, 3, 1);
    B.set_element(3, 0, 2);
    B.set_element(3, 1, 3);
    B.set_element(3, 2, 4);
    B.set_element(3, 3, -1);
    X.set_element(0, 0, 0);
    X.set_element(1, 0, 0);
    X.set_element(2, 0, 0);
    X.set_element(3, 0, 0);

    gaussian(B, X);

    return 0;
=======


    QApplication  a(argc, argv);
    string function = "";
    //uncomment next line and make your own (simple for now) equation
    //function = "sin(x+5)^3 + 3";
    vector<Token> function_ex = simplify(function,'x');
    AF Function = AF(function_ex);
    //uncomment next line to get a back to string representation of your function tree
    cout << "Function: "<<Function.display() << '\n';



    //w.show();
    return a.exec();

>>>>>>> c39f93aebb920357cd11e08b082146ed97f88c21
}
