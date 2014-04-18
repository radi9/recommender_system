#ifndef USER_CPP_
#define USER_CPP_

#include "user.h"


int User::getMovieRating(int movieID)
{
	return ratingList[movieID];
}

void User::addMovieRating(int movieID, int movieRating)
{
	ratingList.push_back(movieRating);
	movieSaw.push_back(movieID);
}

int User::movieFind(int movieID)
{
	return mybinary_search(movieSaw, 0, movieSaw.size()-1, movieID);
}

int User::compare(const User &u)
{
	if(u.getUserID() == userID)
	{

	}
}
#endif USER_CPP_
