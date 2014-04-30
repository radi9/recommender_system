
#ifndef FILEPRO_CPP_
#define FILEPRO_CPP_

void loadTrain(UserList &trainMatrix, Index &userIndex, Index &movieIndex, double &global_totalRating, int &ratingCount)
{
	ifstream fin;
	fin.open(TRAIN_SET);

	char data_char[SIZE_MOVIE];

	if(!fin)
	{
		cout << "training data opening failed" << endl;
	}
	while(fin.getline(data_char, sizeof(data_char),'\n'))
	{
		vector<string> temp;
		temp.push_back(data_char);
		temp = split(temp[0]);

		User user;
		user.id = toInt(temp[0]);
		user.movieID = toInt(temp[1]);
		user.rating = toInt(temp[2]);
		user.time = toInt(temp[3]);

		trainMatrix.push_back(user);

		userIndex.push_back(toInt(temp[0]));
		movieIndex.push_back(toInt(temp[1]));
		totalCount += 1;
		global_totalRating += toInt(temp[2]);

	}
	global_averageRating =  ROUND((static_cast<double>(global_totalRating) / static_cast<double>(totalCount)));
	fin.close();

	//sort by Id and emulate duplicate item
	movieIndex = sortList(movieIndex);
	userIndex = sortList(userIndex);

}

void loadTest(UserList &testMatrix, Index &movieIndex, Index &userIndex)
{
	ifstream fin;
	fin.open(TEST_SET);

	char data_char[SIZE_MOVIE];

	if(!fin)
	{
		cout << "test data opening error" << endl;
	}

	while(fin.getline(data_char, sizeof(data_char),'\n'))
	{
		vector<string> temp;
		temp.push_back(data_char);
		temp = split(temp[0]);

		User user;
		user.id = toInt(temp[0]);
		user.movieID = toInt(temp[1]);
		user.rating = toInt(temp[2]);
		user.time = toInt(temp[3]);

		testMatrix.push_back(user);

		userIndex.push_back(toInt(temp[0]));
		movieIndex.push_back(toInt(temp[1]));
	}

	fin.close();
}

#endif



