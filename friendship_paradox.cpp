#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

void print(vector<double> &v);
void print(vector<vector<int> > &v);
double average(vector<double> &v, int s);

int main ()
{
    ifstream fin;
    fin.open("facebook_combined.txt");
    
    if (fin.fail()) {
        cout << "The file containing the dataset from the network failed to open." << endl;
        exit(1);
    }
    
    //searches for the largest numbered person in the file to determine the size of the network
    int p;
    int max = 0;
    
    while (fin >> p)
        if (p > max) {
            max = p;
        }
    
    //add one to the max-numbeed person to account for the 0th person
    int size = max+1;
    
    //declaration of vectors to be used
    vector<vector<int> > adj_list(max+1);
    vector<double> num_frs;
    vector<double> avg_frs_frs;
    
    //add each person's number to the first position in their vector in the adjacency list
    for (int i = 0; i < adj_list.size(); i++) {
        adj_list[i].push_back(i);
    }
    
    //close and reopen the file with the network's data
    fin.close();
    fin.open("facebook_combined.txt");
    
    if (fin.fail()) {
        cout << "The file contating the dataset from the network failed to open" << endl;
        exit(1);
    }
    
    //integer variables for reading the file
    int x;
    int y;
    
    //creates the adjacency list
    //assumes the file with the data is formatted correctly, each pair of numbers represents a symmetric friendship
    while (fin >> x) {
        fin >> y;
        
        //push back in both vectors because friendship is symmetric
        //x is friends with y and y is friends with x
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }
    
    //prints out the adjacency list
    cout << "Adjacency list of friends in the network: " << endl;
    print(adj_list);
    
    fin.close();
    
    //creates the number of friends (num_frs) vector
    //contains the number of friends each person has at their index
    //i.e. 0th person's number of friends is found at num_frs[0]
    for (int j = 0; j < adj_list.size(); j++) {
        num_frs.push_back(adj_list[j].size()-1);
    }
    
    //calculates the average number of friends for the network
    double avg_num_frs = average(num_frs, size);
    
    //prints out the average number of friends for each person
    cout << "Average number of friends in the network:" << endl;
    print(num_frs);
    
    
    
    //creates average number of friends of friends vector
    for (int k = 0; k < adj_list.size(); k++) {
        double sum = 0.0;
        double avg = 0.0;
        
        for (int m = 1; m < adj_list[k].size(); m++) {
            sum += num_frs[adj_list[k][m]];
        }
        
        avg = sum/num_frs[k];
        avg_frs_frs.push_back(avg);
    }
    
    //calculates the average number of friends of friends for the network
    double avg_frs_of_frs = average(avg_frs_frs, size);
    
    //prints out the average number of friends of each person's friends
    cout << "Average number of friends of a person's friends" << endl;
    print(avg_frs_frs);
    
    
    
    /************ FIRST EVALUATION METHOD **************
    
    compares each person's average number of frineds to the average number of friends of their friends
    
    if the person's friends have an average of more friends than he does, tr is incremented by one to represent that person - pradox appears true in this case
    if the person's friends have an average of less friends than he does or if the values are equal, fal is incremented by one to represent that person - paradox appears false in this case
     
    after accounting for everyone in the network:
        if tr > fal, the friendship paradox appears true for the network
        if fal > tr, the friendship paradox does not appear true for the network */
    
    int tr = 0;
    int fal = 0;
    
    for (int a = 0; a < num_frs.size(); a++) {
        if (avg_frs_frs[a] > num_frs[a]) {
            tr++;
        }
        else {
            fal++;
        }
    }
    
    
    //used these assignments to test that the conclusive if, else if, and else conditions work properly
    //avg_frs_of_frs = 0;
    //tr = 0;
    
    
    /************* CONCLUSIONS ***************/
    
    cout << size << '\t' << "people in the network" << endl << endl;
    
    cout << "FIRST EVALUATION METHOD:" << endl;
    cout << tr << '\t' << "people whose friends have more friends than they do" << endl;
    cout << fal << '\t' << "people have more friends than the average number of their friends' friends" << endl << endl;
    
    cout << "SECOND EVALUATION METHOD:" << endl;
    cout << avg_num_frs << '\t' << "average number of friends for the network" << endl;
    cout << avg_frs_of_frs << '\t' << "average number of friends of a person's friends in the network" << endl << endl;
    
    
    
    
    if ((tr > fal) && (avg_frs_of_frs > avg_num_frs)) {
        cout << "The friendship paradox appears true for this network because:" << endl << endl
        << "   " << "1. most people have fewer friends than the average number of their friends' friends" << endl
        << "   " << "2. average number of friends is less than the average number of friends of friends" << endl << endl;
    }
    
    else if ((tr > fal && !(avg_frs_of_frs > avg_num_frs)) || (!(tr > fal) && avg_frs_of_frs > avg_num_frs)) {
        cout << "The two evaluation methods are yielding different results for this dataset. Inconclusive." << endl;
    }
    
    else {
        cout << "The friendship paradox appears false for this network because: " << endl << endl
        << "   " << "1. majority of people have more friends than the average number of their friends' friends" << endl
        << "   " << "2. average number of friends is greater than the average number of friends of friends" << endl;
    }
    
    
}

void print(vector<double> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << i << '\t' << v[i] << endl;
    }
    cout << endl << endl;
}

void print(vector<vector<int> > &v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            cout << v[i][j] << '\t';
        }
        cout << endl << endl;
    }
    cout << endl << endl;
}

double average(vector<double> &v, int s) {
    double sum = 0.0;
    double avg = 0.0;
    
    for (int i = 0; i < v.size(); i++) {
        sum += v[i];
    }
    
    double size = static_cast<double>(s);
    avg = sum/size;
    
    return avg;
}

