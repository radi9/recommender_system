#include "../headers/commonHeader.h"
#include "../headers/common.cpp"
#include "../headers/filepro.cpp"
#include "../headers/model.cpp"

int main()
{
	Index trainUser;
	Index trainMovie;
	Index testUser;
	Index testMovie;
	Data temp;
	Data train;
	Data test;
	UserList trainMatrix;
	UserList testMatrix;

	//end pre-processing
	//create model
	int userTotalRating[SIZE_USER] = {0}; //particular user total rating
	int userRatingCount[SIZE_USER] = {0}; //particular user rating counts

	int movieTotalRating[SIZE_MOVIE] = {0}; //particular movie total rating
	int movieRatingCount[SIZE_MOVIE] = {0}; //how many the movie

	double global_averageRating = 0.0;

	void loadTrain(UserList &trainMatrix, Index &userIndex, Index &movieIndex, double &global_averageRating);
	loadTest(testMatrix, testUser, testMovie);

	for(vector<string>::iterator it = train.begin(); it != train.end(); it++)
	{
		vector<string> temp = split(*it);
		User user;
		user.id = toInt(temp[0]);
		user.movieID = toInt(temp[1]);
		user.rating = toInt(temp[2]);
		user.time = toInt(temp[3]);

		//sotre and add each encounter the movie's rating
		userTotalRating[user.id] += toInt(temp[2]);
		userRatingCount[user.id] += 1;
		movieTotalRating[user.movieID] += toInt(temp[2]);
		movieRatingCount[user.movieID] += 1;
	}


	//initial moive(bi) and user(bu) bias
	
	double bu[SIZE_USER] = {0.0};
	double bi[SIZE_MOVIE] = {0.0};


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
		rmseProcess(testMatrix, predictRating(userTotalRating[i], userRatingCount[i],bi[i],bu[i]));
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
				int movieID = trainUser[j]; //this movieID
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


