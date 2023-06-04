
 #include <cstring>
 #include <iostream>
 #include <vector>
 #include <iterator>
 #include <fstream>
 using namespace std;

 struct Node{
   char* label;
   vector<Node*> connect;
   vector<int> weightlist;
 };

 void addVertex(vector<Node*>* glist);
 void addEdge(vector<Node*>* glist);
 int distance(Node* x, Node* y);
 void removeVertex(vector<Node*>* glist);
 void removeEdge(vector<Node*>* glist);
 void printTable(vector<Node*> glist);
 void dijkstra(vector<Node*> glist, Node* start, Node* stop);

 int main() {

   vector<Node*> glist;
   char* userInput = new char[50];
   bool cont = true;
   while (cont == true) {
     cout << "Please input one of these commands AV (Add Vertext), AE (Add Edge), RV (Remove Vertex), RE (Remove Edge), SP (Shortest Path) PRINT (Print) QUIT (Quit) " << endl;
     cin >> userInput;
     cin.ignore();
     if (strcmp(userInput, "AV") == 0) {
       addVertex(&glist);
     }
     else if (strcmp(userInput, "AE") == 0) {
       addEdge(&glist);
     }
     else if (strcmp(userInput, "RV") == 0) {
       removeVertex(&glist);
     }
     else if (strcmp(userInput, "RE") == 0) {
       removeEdge(&glist);
     }
     else if (strcmp(userInput, "PRINT") == 0) {
       printTable(glist);
     }
     else if (strcmp(userInput, "SP") == 0) {
       //write the shortest path stuff here
     }
     else if (strcmp(userInput, "QUIT") == 0) {
       cout << "Thanks for using this program!" << endl;
     }
   }
   cout << endl;
   return 0;
			      
 }

 int distance(Node* x, Node* y) {

   vector<Node*> :: iterator it;
   for(it = x->connect.begin(); it != x->connect.end(); it++) {
     if ((*it) == y) {
       return it - x->connect.begin();
     }
   }
   return -1;
 }

 void addVertex(vector<Node*>* glist) {

   Node* temp = new Node();
   char* input = new char(50);
   cout << "Vertext Label: " << endl;
   cin.getline(input, 50, '\n');
   temp->label = input;
   glist->push_back(temp);
   
 }

 void addEdge(vector<Node*>* glist) {

   char* sone = new char(50);
   char* stwo = new char(50);
   bool gone = false;
   bool gtwo = false;
   int weight = 0;
   Node* one = NULL;
   Node* two = NULL;

   if(glist->size() < 2) {
     cout << "There are not enoguth nodes!" << endl;
     return;
   }

   vector<Node*> :: iterator it;
   cout << "Vertex 1: " << endl;
   cin.getline(sone, 50);
   cout << "Vertex 2: " << endl;
   cin.getline(stwo, 50);
   for(it = glist->begin(); it != glist->end(); it++) {
     if (strcmp((*it)->label, sone) == 0) {
       one = (*it);
       gone = true;
     }
     if (strcmp((*it)->label, stwo) == 0) {
       two = *(it);
       gtwo = true;
     }
   }
   if(gone == true && gtwo == true) {
     cout << "Edge Weight: " << endl;
     cin >> weight;
     cin.ignore();
     one->connect.push_back(two);
     one->weightlist.push_back(weight);
     return;
   }
   cout << "Not valid Vertices!" << endl;
   
 }

 void removeVertex(vector<Node*>* glist) {

   char* input = new char[50];
   Node* temp = NULL;
   int n = 0;
   cout << "Vertex Label: " << endl;
   cin.getline(input, 50);
   vector<Node*> :: iterator it;
   for (it = glist->begin(); it != glist->end(); it++) {
     if (strcmp((*it)->label, input) == 0) {
       temp = *(it);
     }
   }

   if (temp == NULL) {
     cout << "Not a valid node! " << endl;
     return;
   }

   vector<Node*> :: iterator ite;
   for (ite = glist->begin(); ite != glist->end(); ite++) {
     n = distance((*ite), temp);
     if (n != -1) {
       (*ite)->connect.erase((*ite)->connect.begin() + n);
       (*ite)->weightlist.erase((*ite)->weightlist.begin() + n);
     }
   }
     vector<Node*> :: iterator iter;
     for(iter = glist->begin(); iter != glist->end(); iter++) {
       if (temp == (*iter)) {
	 glist->erase(iter);
	 iter--;
	 delete temp;
       }
     }
 }

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
   for(it = glist->begin(); it != glist->end(); it++) {
     if(strcmp((*it)->label, sone) == 0) {
       one = *(it);
       gone = true;
     }
     if(strcmp((*it)->label, stwo) == 0) {
       two = *(it);
       gtwo = true;
     }
   }
   if (gone == true && gtwo == true) {
     i = distance(one, two);
     if(i != -1) {
       one->connect.erase(one->connect.begin() + i);
       one->weightlist.erase(one->weightlist.begin() + i);
       return;
     }
   }
   cout << "Not valid Vertices!" << endl;
   
 }

 void printTable(vector<Node*> glist) {

   vector<Node*> :: iterator it;
   vector<Node*> :: iterator i;
   vector<Node*> :: iterator j;
   int p = 0;
   cout << "The Adjacency Table: " << endl << endl;
   cout << "\t";
   for (it = glist.begin(); it != glist.end(); it++) {
     cout << (*it)->label;
     cout << "\t";
   }
   cout << endl;

   for(i = glist.begin(); i!=glist.end(); i++) {
     cout << (*it)->label;
     cout << "\t";
     for (j = glist.begin(); j != glist.end(); j++) {
       p = distance((*i),(*j));
       if (p != -1) {
         cout << (*i)->weightlist[p];
         cout << "\t";
       }
       else {
         cout << "*";
         cout << "\t";
      }
    }
    cout << endl;
   }
 }

 void dijkstrea(vector<Node*> glist, Node* start, Node* stop) {

   cout << "Working " << endl;
   
 }
