
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

#define SIZE_USER 943
#define SIZE_MOVIE 1682
#define TRAIN_SET "C:/Users/red/Documents/optimization data/train.txt"
#define TEST_SET "C:/Users/red/Documents/optimization data/test.txt"
#define OUTPUT_FILE "C:/Users/red/Documents/optimization data/output.txt"
#define ROUND(x) ((int)(x * 100 + 0.5)/100.) //round off to the 2nd decimal place
#define SIZE_USER 943
#define SIZE_MOVIE 1682
#define BEGIN_BLOCK {
#define END_BLOCK }

struct User
{
	int id;
	int movieID;
	int rating;
	int time;
	double predict_rating;
	bool operator()(const User &a)
	{
		return (this -> movieID > a.id) ? 1 : 0;
	}
};

typedef vector<int> Index;
typedef vector<string> Data;
typedef vector<User> UserList;
typedef vector<UserList> UserTable;


void message_box(string message, bool key);

void loadTrain(UserTable &trainMatrix,int &global_totalRating, int &total_ratingCount,
		int *userTotalRating, int *userRatingCount, int *movieTotalRating, int *movieRatingCount);
void loadTest(UserList &testList);


vector<string> split(const string &n);
int toInt(const string s);

vector<int> sortList(vector<int> list);
double getMean(int totalRating, int ratingCount);


double predictRating(int userTotalRating, int userRatingCount, double bi, double bu);
double rmseProcess(UserList &userList,double predictRating);



#endif /* COMMONHEADER_H_ */
