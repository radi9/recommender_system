/*
 * user.h
 *
 *  Created on: Apr 11, 2014
 *      Author: red
 */

#ifndef USER_H_
#define USER_H_

void User::setUserID(int userID)
{
	this -> userID = userID;
}

int User::getUserID()
{
	return this -> userID;
}

vector<int> User::getMovieRating(int movieID)
{
	return ratingList[movieID];
}

void User::addMoiveFavore(int movieID)
{
	movieSaw.push_back((movieID));
}

void User::addMovieRating(int movieRating)
{
	ratingList.push_back(movieRating);
}


#endif /* USER_H_ */
