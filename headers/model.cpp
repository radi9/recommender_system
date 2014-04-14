/*
 * model.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: red
 */
#ifndef MODEL_CPP_
#define MODEL_CPP_

namespace model
{
int userTotalRating[SIZE_USER] = {0}; //particular user total rating
int userRatingCount[SIZE_USER] = {0}; //particular user rating counts

int movieTotalRating[SIZE_MOVIE] = {0}; //particular movie total rating
int movieRatingCount[SIZE_MOVIE] = {0}; //how many the movie


for(vector<string>::iterator it = trainData.begin(); it != trainData.end(); it++)
{
	vector<string> temp = split(*it);
	//check the identify index in userIndex and movieIndex
	int user_index = mybinary_search(userIndex, 0, userIndex.size()-1, atoi(temp[0].c_str()));
	int movie_index = mybinary_search(movieIndex, 0, movieIndex.size()-1, atoi(temp[1].c_str()));

	//insert rating into "the table" that is which user rated corresponding to movie, and also huge two dim table
	dataMatrix[user_index][movie_index] = toInt(temp[2]);
	timeMatrix[user_index][movie_index] = toInt(temp[3]);

	//sotre and add each encounter the movie's rating
	userTotalRating[user_index] += toInt(temp[2]);
	userRatingCount[user_index] += 1;
	movieTotalRating[movie_index] += toInt(temp[2]);
	movieRatingCount[movie_index] += 1;
}

void model()
{

}

};

#endif

