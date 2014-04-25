
#ifndef COMMONHEADER_H_
#define COMMONHEADER_H_

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <math.h>

using namespace std;

//put this before user.h such as user class's memeber could use this function
template<class myType>
int mybinary_search(vector<myType> &vec, unsigned start, unsigned end, const int &key);

//my define .h
#include "user.h"

#define SIZE_USER 943
#define SIZE_MOVIE 1682
#define TRAIN_SET "/home/red/ML_DM data/ml-10M/train.txt"
#define TEST_SET "/home/red/ML_DM data/ml-10M/testt.txt"
#define OUTPUT_FILE "/home/red/ML_DM data/ml-10M"
#define ROUND(x) ((int)(x * 100 + 0.5)/100.) //round off to the 2nd decimal place
#define SIZE_USER 943
#define SIZE_MOVIE 1682
#define BEGIN_BLOCK {
#define END_BLOCK }

typedef vector<int> Index;
typedef vector<string> Data;
typedef vector<User> UserList;

struct User{

	int id;
	int movieID;
	int rating;
	int time;
	bool operator()(const User &a)
	{
		return (this -> movieID > a.id) ? 1 : 0;
	}
};


void loadTrain(vector<string> &data, vector<int> &movieIndex, vector<int> &userIndex, double &global_averageRating);
void loadTest(vector<string> &data, vector<int> &movieIndex, vector<int> &userIndex);


vector<string> split(const string &n);
int toInt(const string s);

vector<int> sortList(vector<int> list);
double getMean(int totalRating, int ratingCount);


double predictRating(int userTotalRating, int userRatingCount, double bi, double bu);
double rmseProcess(vector<int> &ratingVector,double predictRating);



#endif /* COMMONHEADER_H_ */
