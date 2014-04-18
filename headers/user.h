#ifndef USER_H_
#define USER_H_

class User
{
public:
	int getUserID() const;
	void setUserID(int userID) const;
	int getMovieRating(int movieID);
	void addMovieRating(int movieID, int movieRating);
	int compare(const User&u);

private:
	int userID;
	vector<int> movieSaw; //movie id in there
	vector<int> ratingList; //moive rating score record
	int movieFind(int movieID);
};

#endif USER_H_
