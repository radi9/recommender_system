#ifndef USER_H_
#define USER_H_

class User
{
public:
	int getUserID();
	void setUserID(int userID);
	int getMovieRating(int movieID);
	void addMovieRating(int movieID, int movieRating);

private:
	int userID;
	vector<int> movieSaw; //movie id in there
	vector<int> ratingList; //moive rating score record
	bool movieFind(int movieID);
};

#endif USER_H_
