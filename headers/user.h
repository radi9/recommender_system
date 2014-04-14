#include <string>
#include <vector>

using namespace std;

class User
{
public:
	int getUserID();
	void setUserID(int userID);
	vector<int> getMoviePre();
	vector<int> getMovieRating();
	void addMovieRating(int movieRating);

private:
	int userID;
	vector<int> movieSaw; //movie id in there
//	vector<int> moviePre;//boolean in there    NOT Necessary one
	vector<int> movieRating; //moive rating score record
	bool movieFind(int movieID);
};

void User::setUserID(int userID)
{
	this -> userID = userID;
}

int User::getUserID()
{
	return this -> userID;
}

vector<int> User::getMovieRating()
{
	return this -> movieRating;
}

//void User::addMoviePre(int movieID)
//{
//}
//
//void User::addMovieRating(int movieRating)
//{
//	this - > movieRating.push_bach(movieRating);
//	sort(this -> movieRating);
//}
//
//int User::movieFind(int movieID)
//{
//	return myBinary_search();
//}