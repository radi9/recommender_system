/*
 * commonHeader.h
 *
 *  Created on: Apr 11, 2014
 *      Author: red
 */

#ifndef COMMONHEADER_H_
#define COMMONHEADER_H_

#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <math.h>



#define SIZE_USER 943
#define SIZE_MOVIE 1682
#define TRAIN_SET "/home/red/ML_DM data/ml-10M/train.txt"
#define TEST_SET "/home/red/ML_DM data/ml-10M/testt.txt"
#define OUTPUT_FILE "/home/red/ML_DM data/ml-10M"
#define ROUND(x) (int)(x * 100 + 0.5)/100. //round off to the 2nd decimal place
#define SIZE_USER 943
#define SIZE_MOVIE 1682
#define BEGIN_BLOCK {
#define END_BLOCK }

using namespace std;

typedef vector<int> Index;
typedef vector<string> Temp;
typedef vector<User> UserMatrix;
typedef vector<vector<int> > DataMatrix;

class User
{
public:
	int getUserID();
	void setUserID(int userID);
	vector<int> getMovieRating(int movieID);
	void addMoiveFavore(int movieID);
	void addMovieRating(int movieRating);

private:
	int userID;
	vector<int> movieSaw; //movie id in there
	vector<int> ratingList; //moive rating score record
	bool movieFind(int movieID);
};


void loadTrain(vector<string> &data, vector<int> &movieIndex, vector<int> &userIndex, double &global_averageRating);
void loadTest(vector<string> &data, vector<int> &movieIndex, vector<int> &userIndex);


vector<string> split(const string &n);
int toInt(const string s);
int mybinary_search(vector<int> &vec, unsigned start, unsigned end, const int &key);
vector<int> sortList(vector<int> list);
double getMean(int totalRating, int ratingCount);


double predictRating(int userTotalRating, int userRatingCount, double bi, double bu);
double rmseProcess(vector<int> &ratingVector,double predictRating);


#endif /* COMMONHEADER_H_ */
