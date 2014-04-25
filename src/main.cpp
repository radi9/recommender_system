#include "../headers/commonHeader.h"
#include "../headers/common.cpp"
#include "../headers/filepro.cpp"
#include "../headers/model.cpp"
#include "../headers/user.cpp"
#include "../headers/myUserContainer.cpp"

int main()
{
	Index trainUser;
	Index trainTest;
	Data temp;
	UserList trainMatrix;

	//end preprcessing
	//create model
	int userTotalRating[SIZE_USER] = {0}; //particular user total rating
	int userRatingCount[SIZE_USER] = {0}; //particular user rating counts

	int movieTotalRating[SIZE_MOVIE] = {0}; //particular movie total rating
	int movieRatingCount[SIZE_MOVIE] = {0}; //how many the movie

	for(vector<string>::iterator it = trainData.begin(); it != trainData.end(); it++)
	{
		vector<string> temp = split(*it);
		User user;
		user.id = toInt(temp[0]);
		user.movieID = toInt(temp[1]);
		user.rating = toInt(temp[2]);
		user.time = toInt(temp[3]);

		//sotre and add each encounter the movie's rating
		userTotalRating[user_index] += toInt(temp[2]);
		userRatingCount[user_index] += 1;
		movieTotalRating[movie_index] += toInt(temp[2]);
		movieRatingCount[movie_index] += 1;
	}


	//initial moive(bi) and user(bu) bias
	
	double bu[SIZE_USER] = {0};
	double bi[SIZE_MOVIE] = {0};



	system("pause");
	return 0;
}


