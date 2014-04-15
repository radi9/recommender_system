#include "../headers/commonHeader.h"
#include "../headers/common.cpp"
#include "../headers/filepro.cpp"
#include "../headers/model.cpp"
#include "../headers/user.cpp"
#include "myUserContainer.cpp"
int main()
{
	Index trainUser;
	Index trainTest;
	Data temp;
	UserList trainMatrix;




	//end preprcessing
	//create model


	t_userIndex = sortList(t_userIndex);
	t_movieIndex = sortList(t_movieIndex);

	for(vector<string>::iterator it = testData.begin(); it != testData.end(); it++)
	{
		vector<string> temp = split(*it);
		//check the identify index in userIndex and movieIndex
		int user_index = mybinary_search(t_userIndex, 0, t_userIndex.size()-1, atoi(temp[0].c_str()));
		int movie_index = mybinary_search(t_movieIndex, 0, t_movieIndex.size()-1, atoi(temp[1].c_str()));

		//insert rating into "the table" that is which user rated corresponding to movie, and also huge two dim table
		testMatrix[user_index][movie_index] = toInt(temp[2]);
	}

	//initial moive(bi) and user(bu) bias
	

	system("pause");
	return 0;
}


