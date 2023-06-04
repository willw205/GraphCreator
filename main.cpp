
 //William Wong
 //6/4/23
 //This is the graph creator project which creates a Table the displays the labels of the nodes and the weights of the edges between

 #include <cstring>
 #include <iostream>
 #include <vector>
 #include <iterator>
 #include <fstream>
 using namespace std;

 struct Node{
   char* label; //The label of vertex
   vector<Node*> connect; //the lit of vertices connected toward
   vector<int> weightlist; //list of weights
 };

 //Function prototypes below

 void addVertex(vector<Node*>* glist);
 void addEdge(vector<Node*>* glist);
 int distance(Node* x, Node* y);
 void removeVertex(vector<Node*>* glist);
 void removeEdge(vector<Node*>* glist);
 void printTable(vector<Node*> glist);
 void dijkstra(vector<Node*> glist, Node* start, Node* stop);

 int main() {

   vector<Node*> glist;
   char* userInput = new char[20];
   bool cont = true;
   while (cont == true) {
     cout << "Please input one of these commands AV (Add Vertext), AE (Add Edge), RV (Remove Vertex), RE (Remove Edge), SP (Shortest Path) PRINT (Print) QUIT (Quit) " << endl;
     cin >> userInput;
     cin.ignore();
     if (strcmp(userInput, "AV") == 0) { //If user wants to add vertex
       addVertex(&glist);
     }
     else if (strcmp(userInput, "AE") == 0) { //If user wants to Add Edge
       addEdge(&glist);
     }
     else if (strcmp(userInput, "RV") == 0) { //IF user wants to remove vertex
       removeVertex(&glist);
     }
     else if (strcmp(userInput, "RE") == 0) { //If user wants to remove edge
       removeEdge(&glist);
     }
     else if (strcmp(userInput, "PRINT") == 0) { //If user wants to print
       printTable(glist);
     }
     else if (strcmp(userInput, "SP") == 0) {
       //function error
       char* ione = new char(50);
       char* itwo = new char(50);
       Node* one = NULL;
       Node* two = NULL;
       bool yone = false;
       bool ytwo = false;
       int i = 0;
       vector<Node*> :: iterator it;
       cout << "Vertex 1: " << endl;
       cin.getline(ione, 50);
       cout << "Vertex 2: " << endl;
       cin.getline(itwo, 50);
       for(it = glist.begin(); it != glist.end(); it++){//check if both vertices exist
	 if (strcmp((*it)->label, ione) == 0){
	   one = *(it);
	   yone = true;
	 }
	 if (strcmp((*it)->label, itwo) == 0){
	   two = *(it);
	   ytwo = true;
	 }
       }
       if (yone == true && ytwo == true){//if both exist, shortest path
	 dijkstra(glist, one, two);
       }
       else{
	 cout << "Invalid Vertices!" << endl;
       }
     }
     else if (strcmp(userInput, "QUIT") == 0) { //If user wants to quit
       cout << "Thanks for using this program!" << endl;
       cont = false;
       return 0;
     }
   }
   cout << endl;
   return 0;
			      
 }

 //Below helps to return the distance from the current vertex to first element of vertex

 int distance(Node* x, Node* y) {

   vector<Node*> :: iterator it;
   for(it = x->connect.begin(); it != x->connect.end(); it++) {
     if ((*it) == y) { //if node is within connected v ertices
       return it - x->connect.begin(); //returns distance
     }
   }
   return -1;
 }

 //Adds vertext to list 

 void addVertex(vector<Node*>* glist) {

   Node* temp = new Node();
   char* input = new char[50];
   cout << "Vertext Label:" << endl;
   cin.getline(input, 50, '\n');
   temp->label = input; //pushing temp into vertexlist
   glist->push_back(temp);
   
 }

 //Below helps to take two vertices and assigns edge wieght between them

 void addEdge(vector<Node*>* glist) { 

   char* sone = new char[50];
   char* stwo = new char[50];
   bool gone = false;
   bool gtwo = false;
   int weight = 0;
   Node* one = NULL;
   Node* two = NULL;

   if(glist->size() < 2) { //if there are less than two vertices
     cout << "There are not enoguth nodes!" << endl;
     return;
   }

   vector<Node*> :: iterator it;
   cout << "Vertex 1: " << endl;
   cin.getline(sone, 50);
   cout << "Vertex 2: " << endl;
   cin.getline(stwo, 50);
   for(it = glist->begin(); it != glist->end(); it++) { //looks for vetex list
     if (strcmp((*it)->label, sone) == 0) {
       one = (*it);
       gone = true;
     }
     if (strcmp((*it)->label, stwo) == 0) {
       two = *(it);
       gtwo = true;
     }
   }
   if(gone == true && gtwo == true) { //if both are existing assign the weight
     cout << "Edge Weight: " << endl;
     cin >> weight;
     cin.ignore();
     one->connect.push_back(two); //Vertex 2 connected toward vertex 1
     one->weightlist.push_back(weight); //storing weight in list
     return;
   }
   cout << "Not valid Vertices!" << endl;
   
 }

 //Helps to remove the corresponding vertex in vertex in the vertext list from userInput

 void removeVertex(vector<Node*>* glist) { 

   char* input = new char[50];
   Node* temp = NULL;
   int n = 0;
   cout << "Vertex Label: " << endl;
   cin.getline(input, 50);
   vector<Node*> :: iterator it;
   for (it = glist->begin(); it != glist->end(); it++) { //helps to look for the vertex to be deleted
     if (strcmp((*it)->label, input) == 0) {
       temp = *(it); //stroing the address
     }
   }

   if (temp == NULL) { //if the vertex not idnetified
     cout << "Not a valid node! " << endl;
     return;
   }

   vector<Node*> :: iterator ite;
   for (ite = glist->begin(); ite != glist->end(); ite++) { //runs through glist
     n = distance((*ite), temp); //if tem is within, won't return -1
     if (n != -1) {
       (*ite)->connect.erase((*ite)->connect.begin() + n); // connect and weightlist have same distance
       (*ite)->weightlist.erase((*ite)->weightlist.begin() + n);
     }
   }
     vector<Node*> :: iterator iter;
     for(iter = glist->begin(); iter != glist->end(); iter++) {
       if (temp == (*iter)) { //goes toward vertex in glist
	 glist->erase(iter); //helps to clear the memory
	 iter--;
	 delete temp;
       }
     }
 }

 //Below helps to remove vertex from connection lists and weight lists

 void removeEdge(vector<Node*>* glist) {

   char * sone = new char(50);
   char* stwo = new char(50);
   Node* one = NULL;
   Node* two = NULL;
   bool gone = false;
   bool gtwo = false;
   int i = 0;
   vector<Node*> :: iterator it;
   cout << "Vertex 1: " << endl;
   cin.getline(sone, 50); 
   cout << "Vertex 2: " << endl;
   cin.getline(stwo, 50);
   for(it = glist->begin(); it != glist->end(); it++) { //checks if both vertices exist
     if(strcmp((*it)->label, sone) == 0) {
       one = *(it);
       gone = true;
     }
     if(strcmp((*it)->label, stwo) == 0) {
       two = *(it);
       gtwo = true;
     }
   }
   if (gone == true && gtwo == true) { //if both do exist
     i = distance(one, two); //if they are connected
     if(i != -1) {
       one->connect.erase(one->connect.begin() + i); //helps to erase vertex in connect list and wieght list
       one->weightlist.erase(one->weightlist.begin() + i);
       return;
     }
   }
   cout << "Not valid Vertices!" << endl;
   
 }

 //Below helps to print the table

 void printTable(vector<Node*> glist) {

   vector<Node*> :: iterator it;
   vector<Node*> :: iterator i;
   vector<Node*> :: iterator j;
   int p = 0;
   cout << "The Adjacency Table:" << endl << endl;
   cout << "\t";
   for (it = glist.begin(); it != glist.end(); it++) { //the first row headers
     cout << (*it)->label;
     cout << "\t";
   }
   cout << endl;

   for(i = glist.begin(); i!= glist.end(); i++) { //goes through the vertex list
     cout << (*i)->label; //prints the labels
     cout << "\t";
     for (j = glist.begin(); j != glist.end(); j++) { //helps to check for connection/weight between
       p = distance((*i),(*j)); //checkign for connection/distance of the weight
       if (p != -1) { //if they are connected
         cout << (*i)->weightlist[p]; //prints the weight of connected vertices
         cout << "\t";
       }
       else { //if there is no weight, print *
         cout << "*";
         cout << "\t";
      }
    }
    cout << endl;
   }
 }

 void dijkstra(vector<Node*> glist, Node* start, Node* stop) {

   cout << "Working" << endl;
   
 }
