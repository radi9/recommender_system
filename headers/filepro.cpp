
#ifndef FILEPRO_CPP_
#define FILEPRO_CPP_

void loadTrain(UserTable &trainMatrix,int &global_totalRating, int &total_ratingCount,
		int *userTotalRating, int *userRatingCount, int *movieTotalRating, int *movieRatingCount)
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

		trainMatrix[user.id].push_back(user);


		//sotre and add each encounter the movie's rating
		userTotalRating[user.id] += toInt(temp[2]);
		userRatingCount[user.id] += 1;
		movieTotalRating[user.movieID] += toInt(temp[2]);
		movieRatingCount[user.movieID] += 1;

//		userIndex.push_back(toInt(temp[0]));
//		movieIndex.push_back(toInt(temp[1]));
		total_ratingCount += 1;
		global_totalRating += toInt(temp[2]);

	}

	fin.close();

	//sort by Id and emulate duplicate item
//	movieIndex = sortList(movieIndex);
//	userIndex = sortList(userIndex);

}

void loadTest(UserList &testList)
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

		testList.push_back(user);

	}

	fin.close();
}

#endif



