/*
 * main.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: red
 */

#include "../headers/commonHeader.h"
#include "../headers/common.cpp"
#include "../headers/filepro.cpp"
#include "../headers/model.cpp"
#include "../headers/user.cpp"

int main()
{
	Index trainUser;
	Index trainTest;
	Data temp;
	UserList trainMatrix;




	//end preprcessing
	//create model and load test data set
	data.open(TEST_SET);

	vector<string> testData;
	vector<int> t_movieIndex(1411); //identify the index for each user's movie watch list
	vector<int> t_userIndex(460); //identify the index for each user id
	vector<vector<int> > testMatrix(460, vector<int> (1411));

	if(!data)
	{
		cout << "test data opening error" << endl;
	}

	while(data.getline(data_char,sizeof(data_char),'\n'))
	{
		vector<string> temp;
		temp.push_back(data_char);
		temp = split(temp[0]);

		testData.push_back(data_char);
		t_userIndex.push_back(toInt(temp[0]));
		t_movieIndex.push_back(toInt(temp[1]));
	}
	data.close();

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
	double bu[SIZE_USER] = {0};
	double bi[SIZE_MOVIE] = {0};

	for(int i = 0; i < SIZE_USER; i++)
	{
		bu[i] = global_averageRating - getMean(userTotalRating[i], userRatingCount[i]);
	}

	for(int i = 0; i < SIZE_MOVIE; i++)
	{
		bi[i] = global_averageRating - getMean(movieTotalRating[i], movieRatingCount[i]);
	}



	//start modeling
	double learnRate = 0.005;
	double lambda = 0.02;
	double pui = 0.0; //predict value user u to movie i

	double currentRmse = 0.0;
	double prevRmse = 10000000;

	float userBase[SIZE_USER][50] = {0};
	float movieBase[SIZE_MOVIE][50] = {0};

	ofstream result;
	result.open (OUTPUT_FILE);

	for(int i = 0; i < 460; i++)
	{
		rmseProcess(testMatrix[i],predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
	}

	for(int step = 0; step < 50; ++step)
	{
		long double rmse = 0.0;
		int n = 0;
		for(int i = 0; i < SIZE_USER; i++)
		{
			double sqrtNub = 0.0;
			if(userRatingCount[i] != 0)
			{
				sqrtNub = (1.0) / sqrt(userRatingCount[i]);
			}
			for(int j = 0; j <userRatingCount[i]; j++)
			{
				int movieID = movieIndex[j]; //this movieID
				int rating = dataMatrix[i][j]; //this user rate this movie, the rating
				double bui = global_totalRating - bu[i] - bi[j];
				pui = predictRating(userTotalRating[i], userRatingCount[i],bi[j],bu[i]);
				result << userIndex[i] << "::" << movieIndex[j] << "::" << dataMatrix[i][j] << "::" << timeMatrix[i][j] << "::"<< pui << endl;
				double eui = rating - pui; //error about current rating and predicet rating
				rmse += eui * eui;
				bu[i] += learnRate * (eui - lambda * bu[j]);
				bi[j] += learnRate * (eui - lambda * bi[j]);
			}
		}
		currentRmse =  sqrt( rmse / n);
		if(currentRmse >= prevRmse)
		{
			break;//if the rmse of test set begin to increase, then break
		}
		else
		{
			prevRmse = currentRmse;
		}
		for(int i = 0; i < 460; i++)
		{
		rmseProcess(testMatrix[i],predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
		}
	}
	for(int i = 0; i < 460; i++)
	{
		rmseProcess(testMatrix[i],predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
	}

	system("pause");
	return 0;
}


