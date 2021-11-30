/*
Michael Bentivegna
String Merge Checker

    This project uses dynamic programming to see if a given string is the merge of two other strings.  In a merge, the characters can be interspersed, but
each character in an individual string must be in the correct order. If it is a merge, then the merged string is printed with string one's
characters' capitalized. If it isn't then *** NOT A MERGE *** is printed.  The strings are read in from a specified input file and all print messages
are sent to a specified output file.

This is a problem from the 1998 regional ACM Programming Contest - http://www.acmgnyr.org/year1998/prob_g.html
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Global 2D Array for Dynamic Programming
bool matrix[1001][1001];

int main()
{
    string input, output;
    string A, B, C;

    //Set up input file stream
    cout << "Enter name of input file: ";
    cin >> input;

    ifstream inF;
    inF.open(input);

    //Set up output file stream
    cout << "Enter name of output file: ";
    cin >> output;

    ofstream outF;
    outF.open(output);

    //Main loop deals with 3 strings at a time A, B, C
    while(getline(inF, A))
    {
        getline(inF, B);
        getline(inF, C);
        string correct = "";

        //Quick check to ensure merged string is the correct length to avoid out of bounds issues
        if(C.length() != (A.length() + B.length()))
        {
            outF << "*** NOT A MERGE ***\n";
        }
        else
        {
            //Loop through every element in the 2D array and check the element to the top and left to see if true
            //Also check if the character lines up with one of the two strings
            //If top is true and string 2 lines up then true 
            //If left is true and string 1 lines up then true
            //Else false
            for (int i = 0; i < B.length() + 1; i++)
            {
                for (int j = 0; j < A.length() + 1; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        matrix[i][j] = true;
                    }
                    else if (i == 0)
                    {
                        matrix[i][j] = (matrix[i][j-1] && (A.at(j-1)) == C.at(i+j-1));
                    }
                    else if (j == 0)
                    {
                        matrix[i][j] = (matrix[i-1][j] && (B.at(i-1)) == C.at(i+j-1));
                    }
                    else
                    {
                        matrix[i][j] = ((matrix[i-1][j] && (B.at(i-1)) == C.at(i+j-1)) || (matrix[i][j-1] && (A.at(j-1)) == C.at(i+j-1)));
                    }
                }
            }

            //Check if matrix is a merge by looking at the last element
            if (matrix[B.length()][A.length()])
            {
                int a = A.length();
                int b = B.length();

                //Loop for writing out the string with string one capitalized
                while(correct.length() < C.length())
                {
                    if (b == 0)
                    {
                        string s(1, toupper(A.at(a-1)));
                        correct = s + correct;
                        a--;
                    }
                    else if (a == 0)
                    {
                        correct = B.at(b-1) + correct;
                        b--;
                    }
                    else if (matrix[b - 1][a])
                    {   
                        correct = B.at(b-1) + correct;
                        b--;
                    }
                    else
                    {
                        string s(1, toupper(A.at(a-1)));
                        correct = s + correct;
                        a--;
                    }
                }

                outF << correct << "\n";
            }
            else
            {
                outF << "*** NOT A MERGE ***\n";
            }
        }   
    }
}