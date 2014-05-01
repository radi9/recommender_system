#include "commonHeader.h"
#include "common.cpp"
#include "filepro.cpp"

int main()
{
	Index trainUser;
	Index trainMovie;
	UserList trainList; //user list in training data,same user id in same list
	UserTable trainMatrix;//each row contents a user list, it's a table(matrix)

	Data train;
	Data test;

	Index testUser;
	Index testMovie;
	UserList testList;
	UserTable testMatrix;

	//end pre-processing
	//create model
	int userTotalRating[SIZE_USER] = {0}; //particular user total rating
	int userRatingCount[SIZE_USER] = {0}; //particular user rating counts

	int movieTotalRating[SIZE_MOVIE] = {0}; //particular movie total rating
	int movieRatingCount[SIZE_MOVIE] = {0}; //how many the movie

	double global_averageRating = 0.0;
	int global_totalRating = 0.0;
	int total_ratingCount = 0;

	loadTrain(trainMatrix, global_totalRating, total_ratingCount, userTotalRating, userRatingCount
			, movieTotalRating, movieRatingCount);
	loadTest(testList);

	global_averageRating =  ROUND((static_cast<double>(global_totalRating)
			/ static_cast<double>(total_ratingCount)));


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
	double pui = 0.0; //predict rating of user u to movie i

	double currentRmse = 0.0;
	double prevRmse = 10000000;

	float userBase[SIZE_USER][50] = {0};
	float movieBase[SIZE_MOVIE][50] = {0};

	ofstream result;
	result.open (OUTPUT_FILE);

	for(int i = 0; i < 460; i++)
	{
		rmseProcess(testList, predictRating(userTotalRating[i], userRatingCount[i],bi[i],bu[i]));
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
				cout << sqrtNub << endl;
			}
			for(int j = 0; j <userRatingCount[i]; j++)
			{
				int movieID = trainUser[j]; //this movieID
				int rating = trainMatrix[i][j].rating; //this user rate this movie, the rating
				double bui = global_totalRating - bu[i] - bi[j];
				pui = predictRating(userTotalRating[i], userRatingCount[i],bi[j],bu[i]);
				//original column
				result << trainMatrix[i][j].id << "::" << trainMatrix[i][j].movieID << "::" << trainMatrix[i][j].rating <<
						"::" << trainMatrix[i][j].time << "::"<< pui << endl;

				double eui = rating - pui; //error about current rating and predict rating
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
			rmseProcess(testList,predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
		}
	}
	for(int i = 0; i < 460; i++)
	{
		rmseProcess(testList,predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
	}

//	for(auto it = testList.begin(); it != testList.end(); it++)
//	{
//		//all of iterators for predict fully records in test set
//		predictRating(userTotalRating[i], userRatingCount[i], bi[i], bj[i]);
//		resutl << "write the output" <<;
//	}


	system("pause");
	return 0;
}


