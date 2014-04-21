#ifndef USER_H_
#define USER_H_

class User
{
public:
	int getUserID() const;
	void setUserID(int userID);
	int getMovieRating(int movieID) const;
	vector<int> getMovieRecords() const;
	void addMovieRating(int movieID, int movieRating);

	bool operator > (const User &a) const;
	bool operator < (const User &a) const;
	void operator == (const User &a);

private:
	int userID;
	vector<int> movieSaw; //movie id in there
	vector<int> ratingList; //moive rating score record
	int movieFind(int movieID);
};

#endif
