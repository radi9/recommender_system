
#ifndef MODEL_CPP_
#define MODEL_CPP_

void model(const double &global_averageRating, const int &userTotalRating[],
		const int &userRatingCount[], const int &movieTotalRating[], const int movieRatingCount[])
{
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
}


#endif

