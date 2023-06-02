
 #include <cstring>
 #include <iostream>
 #include <vector>
 #include <iterator>
 #include <fstream>

 using namespace std;

 //function prototypes below

 int main() {

   vector<Node*> gList;
   char* userInput = new char[50];
   bool cont = true;
   while (cont == true) {
     cout << "Please input one of these commands AV (Add Vertext), AE (Add Edge), RV (Remove Vertex), RE (Remove Edge), SP (Shortest Path" << endl;
     cin >> userInput;
     cin.ignore();
     if (strcmp(input, "AV") == 0) {
       //vertext function here
     }
     else if (strcmp(input, "AE") == 0) {
       //edge function here
     }
		     
   }
			      
   
 }
