#include<iostream>
#include<fstream>
#include<cstring>
#include<conio.h>
#include<iomanip>
using namespace std;
void writeInFile(char*);
void writeOutputinFile(char[][30], int);   //Output dictionary to file
void writeOutputinFile(char[][30], int, int);   //Output Matches to file
void writeOutputinFile(int, char[][30], int);   //Output Final array to file
char* getStringFromFile();
int i = 0;
int read_and_store_dic(char[][30]);
int read_and_store_Paragraph(char[][30]);
int tokenpara(char[][30]);
int MatchandReplace(char[][30], int, char[][30], int);
void Addpunctuation(char[][30], char[][30], int);
int main()
{
    ofstream myFile;
    myFile.open("Output1.txt", ios::trunc);
    i = 0;
    char para[5000];
    char Dictionary1[500][30];
    int Dictionarylen1 = read_and_store_dic(Dictionary1);
    cout << "Enter the paragrpah(# to end the paragraph):" << endl;
    cin.getline(para, 5000, '#');
    int length = strlen(para);
    writeInFile(para);
    ofstream myFileOUTPUT;
    char parareadandstoredin2D[1000][30];
    int paralen1 = read_and_store_Paragraph(parareadandstoredin2D);
    cout << "The Dictionary is:" << endl;
    for (int i = 0; i < Dictionarylen1; i = i + 2) //Displaying the Dictionary.
    {
        cout << setw(10) << Dictionary1[i] << setw(15) << Dictionary1[i + 1] << endl;
    }
    char indivi[1000][30];
    int counter1 = tokenpara(indivi);
    writeOutputinFile(Dictionary1, Dictionarylen1);
    cout << "\n**********************************************" << endl;
    cout << "\nDictionary Words used:" << endl;
    cout << setw(15) << "English" << setw(15) << "Urdu" << setw(15) << endl;
    cout << "----------------------------------------------" << endl;
    int Matchfound_counter = MatchandReplace(indivi, counter1, Dictionary1, Dictionarylen1);
    cout << "Numbers of words found in Dictionary: " << Matchfound_counter << endl;
    char dot[] = ".";
    Addpunctuation(indivi, parareadandstoredin2D, paralen1);
    cout << "\nFinal Output" << endl;
    for (int i = 0; i < counter1; i++)
    {
        cout << indivi[i] << " ";
    }
    cout << endl;
    writeOutputinFile(Matchfound_counter, indivi, counter1);
    myFileOUTPUT.close();
    return 0;
}       //End of Main
int read_and_store_dic(char Dictionary[][30])
{
    ifstream DictionaryFile("Dictionary.txt");
    if (!DictionaryFile)
    {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    int index = 0;
    int deictionarylen = 0;
    while (DictionaryFile >> Dictionary[index] >> Dictionary[index + 1])
    {
        index = index + 2;
        deictionarylen = deictionarylen + 2;
    }
    DictionaryFile.close();
    return deictionarylen;
}
void writeInFile(char* data)
{
    ofstream myFile;
    myFile.open("Para.txt");
    myFile << data;
    myFile.close();
}
void writeOutputinFile(char dic[][30], int lenofdicti)   //Output dictionary to file
{
    ofstream myFile;
    myFile.open("Output1.txt", ios::app);
    myFile << "The Dictionary is:" << endl;
    for (int i = 0; i < lenofdicti; i = i + 2)
    {
        myFile << setw(10) << dic[i] << setw(15) << dic[i + 1] << endl;
    }
    myFile << "\n**********************************************" << endl;
    myFile << "\nDictionary Words used:" << endl;
    myFile << setw(15) << "English" << setw(15) << "Urdu" << setw(15) << endl;
    myFile << "----------------------------------------------" << endl;
}
void writeOutputinFile(char dic[][30], int lenofdicti, int j)   //Output Matches to file
{
    ofstream myFile;
    myFile.open("Output1.txt", ios::app);
    myFile << setw(15) << dic[j] << setw(15) << dic[j + 1] << endl;
}
void writeOutputinFile(int matchfoundcount, char final[][30], int lenoffinalarray)  //Output Final array to file
{
    ofstream myFile;
    myFile.open("Output1.txt", ios::app);
    myFile << "Matches found:" << matchfoundcount << endl;
    cout << endl;
    myFile << "\nFinal Output" << endl;
    for (int i = 0; i < lenoffinalarray; i++)
    {
        myFile << final[i] << " ";
    }
}
char* getStringFromFile()
{
    ifstream inFile("para.txt", ios::in);	//read from a file named Paragraph.
    if (!inFile)
    {
        cout << "File could not be opened" << endl;
        exit(1);	//exit with code 1 indicating an error.
    }
    char allData[5000] = "";
    while (!inFile.eof())
    {
        char data[5000] = "";
        inFile.getline(data, 5000);
        strcat_s(allData, data);
    }
    return allData;
}
int read_and_store_Paragraph(char parareadandstoredin2D1[][30])
{
    ifstream paraFile("para.txt", ios::in);
    if (!paraFile)
    {
        cout << "File could not be opened" << endl;
        exit(0);
    }
    int countpara = 0, paralen = 0;;
    i = 0;
    while (paraFile >> parareadandstoredin2D1[i])
    {
        i++;
        paralen++;
    }
    return paralen;
    paraFile.close();
}
int tokenpara(char string1[][30])
{
    char separators[] = " .";
    char* token;
    char* next_token;
    i = 0;
    token = strtok_s(getStringFromFile(), separators, &next_token);
    int tokenlength = 0;
    while ((token != NULL))
    {
        if (token != NULL)
        {
            strcpy_s(string1[i], token);
            i++;
            tokenlength++;
            token = strtok_s(NULL, separators, &next_token);
        }
    }
    return tokenlength;
}
int MatchandReplace(char indivi[][30], int counter1, char Dictionary1[][30], int Dictionarylen1)
{
    int matchfoundcounter = 0;
    for (int i = 0; i < counter1; i++)
    {
        for (int j = 0; j < Dictionarylen1; j = j + 2)
        {
            if (indivi[i][0] >= 65 && indivi[i][0] <= 90) //if in Capital 
            {
                if (Dictionary1[j][0] >= 97 && Dictionary1[j][0] <= 122)
                {
                    Dictionary1[j][0] -= 32;
                    Dictionary1[j + 1][0] -= 32;
                }
                if (strcmp(indivi[i], Dictionary1[j]) == 0)
                {
                    cout << setw(15) << Dictionary1[j] << setw(15) << Dictionary1[j + 1] << endl;
                    writeOutputinFile(Dictionary1, counter1, j);
                    strcpy_s(indivi[i], Dictionary1[j + 1]);
                    matchfoundcounter++;
                    break;
                }
            }
            else if (indivi[i][0] >= 97 && indivi[i][0] <= 122) //if in lower 
            {

                if (Dictionary1[j][0] >= 65 && Dictionary1[j][0] <= 90)
                {
                    Dictionary1[j][0] += 32;
                    Dictionary1[j + 1][0] += 32;
                }
                if (strcmp(indivi[i], Dictionary1[j]) == 0)
                {
                    cout << setw(15) << Dictionary1[j] << setw(15) << Dictionary1[j + 1] << endl;
                    writeOutputinFile(Dictionary1, counter1, j);
                    strcpy_s(indivi[i], Dictionary1[j + 1]);
                    matchfoundcounter++;
                    break;
                }
            }
        }
    }
    return matchfoundcounter;
}
void Addpunctuation(char indivi1[][30], char parareadandstoredin2D[][30], int paralen2)
{
    char dot[] = ".";
    for (int i = 0; i < paralen2; i = i++)
    {
        if (parareadandstoredin2D[i][strlen(parareadandstoredin2D[i]) - 1] == '.')
        {
            strcat_s(indivi1[i], dot);
        }
    }
}
