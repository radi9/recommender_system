#ifndef USER_CPP_
#define USER_CPP_

#include "user.h"

void User::setUserID(int userID)
{
	this -> userID = userID;
}

int User::getUserID()
{
	return this -> userID;
}

int User::getMovieRating(int movieID)
{
	return ratingList[movieID];
}

void User::addMovieRating(int movieID, int movieRating)
{
	ratingList.push_back(movieRating);
	movieSaw.push_back(movieID);
}

#endif USER_CPP_
