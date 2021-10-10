/*
    Michael Bentivegna
    Spellcheck Assignment

    This project initially loads a dictionary into a hashtable.  It then takes in a user selected input file to spell check it with the allotted dictionary.
    If the word is either too long or contains a number it is omitted from the spell check process.  The proper output is then written to a user specified file.
*/


#include "hash.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

//Confirms valid word before sending it to be spellchecked
void wordConfirmation(string word, int line, bool hasNum, ofstream &outF, hashTable *dictionaryHash)
{
    if (hasNum == false) //Number check
    {
        if(word.length() > 20)  //Length Check
        {
            outF << "Long word at line " << line << ", starts: " << word.substr(0,20) << "\n";
        }
        else
        {
            if (dictionaryHash->contains(word) == false) //See if the word is in the dictionary
            {
                outF << "Unknown word at line " << line << ": " << word << "\n";
            }
        }
    }        
}

//Function for separating out words from the text file
void parseText(string inputFile, string outputFile, hashTable *dictionaryHash)
{
    //Set up proper streams
    ifstream inF;
    inF.open(inputFile);

    ofstream outF;
    outF.open(outputFile);

    string oneLine;
    int lineCounter = 1;

    //Loop through input file line by line
    while (getline(inF, oneLine))
    {
        string currentString = "";
        int charIndex = 0;
        bool hasNum = false;

        while (charIndex < oneLine.length()) 
        {
            char c = tolower(oneLine.at(charIndex)); //Lowercase

            if((c >= 48 && c <= 57) || (c >= 97 && c <= 122) || c == 39 || c == 45) //Check for valid characters
            {
                if (c >= 48 && c <= 57) //Indicates if there is a number in the word
                {
                    hasNum = true;
                }
                
                currentString = currentString + c;

                if (charIndex == oneLine.length() - 1) //If valid character ends the line it still gets sent
                {
                     wordConfirmation(currentString, lineCounter, hasNum, outF, dictionaryHash);
                     currentString = "";
                     hasNum = false;
                }
            }
            else
            {
                if(currentString.length() != 0) //Make sure we aren't sending an empty string
                {
                    wordConfirmation(currentString, lineCounter, hasNum, outF, dictionaryHash);
                }

                currentString = "";
                hasNum = false;
            }
            charIndex++;
        }
        lineCounter++;
    }
}

//Load dictionary function by inserting into hashtable
void loadDict(string dictionary, hashTable *dictionaryHash)
{
    ifstream inF;
    inF.open(dictionary);
    string def= "";

    while(getline(inF, def)) //Loop line by line
    {
        string lcString = "";
        for(int i = 0; i < def.length(); i++) //Make lowercase
        {
            char c = tolower(def.at(i));
            lcString = lcString + c;
        }
        dictionaryHash->insert(lcString); //Send to hashtable
    }
}

//Mission control
int main() 
{
    //Ask user for dictionary
    string inputFile, dictionary, outputFile;
    cout << "Please specify a dictionary that you want to use: ";
    cin >> dictionary;

    //Load dictionary and record the time
    clock_t c_start = clock();

    hashTable *dictionaryHash = new hashTable(40000);
    loadDict(dictionary, dictionaryHash);

    clock_t c_end = clock();

    double time_elapsed_s = ((double)(c_end-c_start)) / CLOCKS_PER_SEC;
    cout << "Time Elapsed to Load Dictionary: " << time_elapsed_s << " s\n";
    
    //Ask for input and output files
    cout << "Please input a text file to be spellchecked: ";
    cin >> inputFile;
    cout << "Please name the output file: ";
    cin >> outputFile;

    //Call function to spellcheck the input file's words and record the time
    c_start = clock();
    parseText(inputFile, outputFile, dictionaryHash);
    c_end = clock();
    time_elapsed_s = ((double)(c_end-c_start)) / CLOCKS_PER_SEC;
    cout << "Time Elapsed to Parse Input: " << time_elapsed_s << " s\n";
    
    return 0;
}