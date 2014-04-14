/*
 * filePro.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: red
 */
#ifndef FILEPRO_CPP_
#define FILEPRO_CPP_

void loadTrain(vector<string> &trainData, vector<int> &movieIndex, vector<int> &userIndex, double &global_averageRating)
{
	ifstream fin;
	fin.open(TRAIN_SET);

	char data_char[SIZE_MOVIE];

	int count = 0;
	int global_totalRating = 0;

	if(!fin)
	{
		cout << "training data opening failed" << endl;
	}
	while(fin.getline(data_char, sizeof(data_char),'\n'))
	{
		vector<string> temp;
		temp.push_back(data_char);
		temp = split(temp[0]);
		trainData.push_back(data_char);

		userIndex.push_back(toInt(temp[0]));
		movieIndex.push_back(toInt(temp[1]));
		count += 1;
		global_totalRating += toInt(temp[2]);

	}
	global_averageRating =  ROUND((static_cast<double>(global_totalRating) / static_cast<double>(count)));
	fin.close();

	//sort by Id and emulate duplicate item
	movieIndex = sortList(movieIndex);
	userIndex = sortList(userIndex);

}

void loadTest(vector<string> &testData, vector<int> &movieIndex, vector<int> &userIndex)
{
	ifstream fin;
	fin.open(TEST_SET);

	char data_char[SIZE_MOVIE];

	while(fin.getline(data_char, sizeof(data_char),'\n'))
	{
		testData.push_back(data_char);
	}

}

#endif FILEPRO_CPP_



