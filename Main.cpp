#include <iostream>
#include "EasyBMP_1.06/EasyBMP.h"
#include <vector>
#include <queue>
using namespace std;

//Vertex Object to store Start and End Point
struct Vertex{
    int x;
    int y;
};

//Checks to see if a pixel and a neighbor are actually neighbors
// If we were to add a color check here for seeing if it is a valid pixel it produces an infinite loop or easily something of O(n^3) time
bool isNeighbor(BMP Image, Vertex u, Vertex v){
    if(abs(u.x - v.x) + abs(u.y - v.y) == 1  && Image(u.x, u.y) != Image(v.x, v.y)){
        return true;
    }
    return false;
}

//Breath first search function as described in project outline
//Problem -> this will not output a correct BMP file for some reason. Leads to pixels breaking and ignoring paths
void Breath_First_Search(BMP Image,Vertex start, Vertex end,string outputFile ){
    queue<Vertex> Q; //Creates our queue
    vector<bool> visited(Image.TellWidth() * Image.TellHeight(), false);  //Creates our visited array
    vector<int> d(Image.TellWidth() * Image.TellHeight(), INT_MAX); //Creates our distance array
    vector<Vertex> prev(Image.TellHeight() * Image.TellWidth(),Vertex());

    //Starting Point
    Q.push(start);
    visited[start.y * Image.TellWidth() + start.x] = true;
    d[start.y * Image.TellWidth() + start.x] = 0;

    //Breath First Search
    while(!Q.empty() && !visited[end.y * Image.TellWidth() + end.x]){
        Vertex u = Q.front();
        Q.pop();

        for (int dx = -1; dx < 1; ++dx){
            for (int dy = -1; dy < 1; ++dy){
                Vertex v = {u.x + dx,u.y + dy};

                if (v.x >= 0 && v.x < Image.TellWidth() && v.y >= 0 && v.y < Image.TellHeight() && isNeighbor(Image, u, v) && !visited[v.y * Image.TellWidth() + v.x]){
                    visited[v.y * Image.TellWidth() + v.x] = true;
                    Image(v.x, v.y)->Green = 255;
                    Image(v.x, v.y)->Blue = 0;
                    Image(v.x,v.y)->Red = 0;
                    d[v.y * Image.TellWidth() + v.x] = d[u.y * Image.TellWidth() + u.x] +1;
                    prev[v.y * Image.TellWidth() + v.x] = u;
                    Q.push(v);
                }
            }
        }
    }

    // If target found, create new image and copy modified pixels
    if (!visited[end.y * Image.TellWidth() + end.x]) {
        BMP newImg; // Create an empty image with the same size
        newImg.SetSize(Image.TellWidth(), Image.TellHeight());

        Vertex v = end;
        while (v.x != start.x || v.y != start.y) {
            newImg(v.x, v.y)->Red = 255;
            newImg(v.x, v.y)->Green = 0;
            newImg(v.x, v.y)->Blue = 0;
            v = prev[v.y * Image.TellWidth() + v.x];
        }
        Image(start.x, start.y)->Green = 255;
        Image(start.x, start.y)->Red = 0;
        Image(start.x, start.y)->Blue = 0;

        for (int i = 0; i < Image.TellWidth(); i++) {
            for (int j = 0; j < Image.TellHeight(); j++) {
                newImg(i, j)->Red = Image(i, j)->Red;
                newImg(i, j)->Green = Image(i, j)->Green;
                newImg(i, j)->Blue = Image(i, j)->Blue;
            }
        }
        // Write the pathfinding visualization to the specified file
        newImg.WriteToFile(outputFile.c_str());
    }
    else {
        cout << "Target was not found" << endl;
    }
}


//void Best_First_Search(){}
void Best_First_Search(BMP Image, Vertex start, Vertex end,string outputFile){
    struct queueItem {
        Vertex vertex;
        int distance;
        bool operator<(const queueItem& other) const {
            return distance > other.distance; // Making it min heap
        }
    };

    priority_queue<queueItem> Q; // Creates our priority queue
    vector<bool> visited(Image.TellWidth() * Image.TellHeight(), false);  // Creates our visited array
    vector<int> d(Image.TellWidth() * Image.TellHeight(), INT_MAX); // Creates our distance array
    vector<Vertex> prev(Image.TellHeight() * Image.TellWidth(), Vertex());

    // Starting Point
    Q.push({start, 0});
    visited[start.y * Image.TellWidth() + start.x] = true;
    d[start.y * Image.TellWidth() + start.x] = 0;

    // Best-First Search
    while (!Q.empty() && !visited[end.y * Image.TellWidth() + end.x]) {
        Vertex u = Q.top().vertex;
        Q.pop();

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                Vertex v = {u.x + dx, u.y + dy};
                if (v.x >= 0 && v.x < Image.TellWidth() && v.y >= 0 && v.y < Image.TellHeight() && isNeighbor(Image, u, v) && !visited[v.y * Image.TellWidth() + v.x]) {
                    visited[v.y * Image.TellWidth() + v.x] = true;
                    Image(v.x, v.y)->Green = 255;
                    Image(v.x, v.y)->Blue = 0;
                    Image(v.x,v.y)->Red = 0;
                    d[v.y * Image.TellWidth() + v.x] = d[u.y * Image.TellWidth() + u.x] + 1;
                    prev[v.y * Image.TellWidth() + v.x] = u;
                    int h = abs(v.x - end.x) + abs(v.y - end.y); // Manhattan distance as heuristic
                    Q.push({v, d[v.y * Image.TellWidth() + v.x] + h});
                }
            }
        }
    }

    if (visited[end.y * Image.TellWidth() + end.x]) {
        Vertex v = end;
        while (v.x != start.x || v.y != start.y) {
            Image(v.x, v.y)->Red = 255;
            Image(v.x, v.y)->Green = 0;
            Image(v.x, v.y)->Blue = 0;
            v = prev[v.y * Image.TellWidth() + v.x];
        }

        Image(start.x, start.y)->Green = 255;
        Image(start.x, start.y)->Red = 0;
        Image(start.x, start.y)->Blue = 0;

        // Create output image
        BMP newImg;
        newImg.SetSize(Image.TellWidth(), Image.TellHeight());
        for (int i = 0; i < Image.TellWidth(); i++) {
            for (int j = 0; j < Image.TellHeight(); j++) {
                newImg(i, j)->Red = Image(i, j)->Red;
                newImg(i, j)->Green = Image(i, j)->Green;
                newImg(i, j)->Blue = Image(i, j)->Blue;
            }
        }
        newImg.WriteToFile(outputFile.c_str());
    } else {
        cout << "Target was not found" << endl;
    }
}

//Prompts the user for a file to read
//Prompts the user for a start and end vert
//Prompts the user for the two files to create later on once the algorithms are run

//Weird bug: when inputting vertex values leads to random spaces on following input prompts
int main(){
    string imageFile;
    cout << "Enter the filename of your BMP image: "<< endl;
    cin >> imageFile;

    BMP image;

    if(!image.ReadFromFile(imageFile.c_str())){
        cout << "Error: could not read image file " << imageFile << endl;
        cout << "Check to see if image or path is wrong"<<endl;
        return 1;
    }

    Vertex start, end;
    cout << "Notice the spaces in between the x and y value on the following prompt: 8 8" << endl;
    cout << "Enter the starting point coordinates (X Y): " << endl;
    cin >> start.x >> start.y;

    cout<< "Enter the ending point coordinates (X Y): " << endl;
    cin >> end.x >> end.y;

    string bfsOutputfile, bestfirstOutputfile;

    cout << "Enter the filename for the Breath First output image (e.g. bfs_output.bmp): " << endl;
    cin >> bfsOutputfile;


    cout << "Enter the filename for the Best First output image (e.g. bfs_output.bmp): " << endl;
    cin >> bestfirstOutputfile;

    Breath_First_Search(image,start,end,bfsOutputfile);
    Best_First_Search(image, start,end,bestfirstOutputfile);

    return 0;
}
