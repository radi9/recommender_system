#ifndef USER_CPP_
#define USER_CPP_

#include "user.h"

int User::getUserID() const
{
	return this -> userID;
}

void User::setUserID(int userID)
{
	this -> userID = userID;
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

vector<int> User::getMovieRecords() const
{
	return this -> movieSaw;
}

int User::movieFind(int movieID)
{
	return mybinary_search(movieSaw, 0, movieSaw.size()-1, movieID);
}

bool User::operator > (const User &a) const
{
	return (this -> userID > a.getUserID()) ? 1 : 0;
}

bool User::operator < (const User &a) const
{
	return (this -> userID < a.getUserID()) ? 1 : 0;
}

void User::operator == (const User &a)
{
	if(userID == a.getUserID())
	{
		vector<int> temp = a.getMovieRecords();
		for(vector<int>::iterator it = temp.begin(); it != temp.end(); it++)
		{
			int rating = a.getMovieRating(*it);
			movieSaw.push_back(*it);
			ratingList.push_back(rating);
		}
	}
}

#endif
