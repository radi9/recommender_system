#include "commonHeader.h"
#include "common.cpp"
#include "filepro.cpp"
#include "model.cpp"

int main()
{
	Index trainUser;
	Index trainTest;
	Data temp;
	Data train;
	UserList trainMatrix;

	//end preprcessing
	//create model
	int userTotalRating[SIZE_USER] = {0}; //particular user total rating
	int userRatingCount[SIZE_USER] = {0}; //particular user rating counts

	int movieTotalRating[SIZE_MOVIE] = {0}; //particular movie total rating
	int movieRatingCount[SIZE_MOVIE] = {0}; //how many the movie

	double global_averageRating = 0.0;

	for(vector<string>::iterator it = train.begin(); it != train.end(); it++)
	{
		vector<string> temp = split(*it);
		User user;
		user.id = toInt(temp[0]);
		user.movieID = toInt(temp[1]);
		user.rating = toInt(temp[2]);
		user.time = toInt(temp[3]);

		//sotre and add each encounter the movie's rating
		userTotalRating[user.id] += toInt(temp[2]);
		userRatingCount[user.id] += 1;
		movieTotalRating[user.movieID] += toInt(temp[2]);
		movieRatingCount[user.movieID] += 1;
	}


	//initial moive(bi) and user(bu) bias
	
	double bu[SIZE_USER] = {0.0};
	double bi[SIZE_MOVIE] = {0.0};



	system("pause");
	return 0;
}


