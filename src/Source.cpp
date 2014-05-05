#include "commonHeader.h"

vector<string> split(const string& n)
{
	char* char_line = (char*)n.c_str(); // string to char, const necessary
										//c_str is for C programmer and able in C++, because C doesn't have string
										//c_str give a pointer of char type related to string type

	char* token		= NULL;
	char* context	= NULL;
	char  delims[]	= "::";//delimister array
	
	vector<string> temp;

	token = strtok_s(char_line, delims, &context);//split by delims, and return pointer relate to first token

	while (token != NULL)
	{	
		temp.push_back(token);


		token = strtok_s(NULL, delims, &context);//return first pointer of tokens, no more delims needed
	}

	return temp;
}

int toInt(const string s)
{
	return atoi(s.c_str());
}
template <class myType>
int mybinary_search(vector<myType> &vec, unsigned start, unsigned end, const int &key)
{
    // Termination condition: start index greater than end index
    if(start > end)
    {
        return -1;
    }

    // Find the middle element of the vector and use that for splitting
    // the array into two pieces.
    unsigned middle = start + ((end - start) / 2);

    if(vec[middle] == key)
    {
        return middle;
    }
    else if(vec[middle] > key)
    {
        return mybinary_search(vec, start, middle - 1, key);
    }

    return mybinary_search(vec, middle + 1, end, key);
}

vector<int> sortList(vector<int> list)
{
	//sort and delete all of the duplicated item
	sort(list.begin(), list.end());
	vector<int>::iterator position = unique(list.begin(), list.end());
	list.erase(position, list.end());

	return list;
}

double getMean(int totalRating, int ratingCount)
{
	return static_cast<double>(totalRating+25)/static_cast<double>(ratingCount+25);
}

double innerDot(vector<double> &user_row, vector<double> &movie_row, const int &itNum)
{
	double result = 0.0;

	for(int i = 0; i < itNum; i++)
	{
		result = user_row[i] * movie_row[i];
	}
	return result;
}

double predictRating(int userTotalRating, int userRatingCount, vector<double> &user_row, vector<double> &movie_row,
					 double bi, double bu, const int &itNub)
{
	//the user i, predict the rating of item j

	//baseline predict rating r^ui = u +bi +bu +p^t*q
	//where p is userBase and q is itemBase
	//add bias, bi is item bias, bu is user bias

	const int k = 25;
	double predict_rate = 0.0;
	double userAverageRating = getMean(userTotalRating,userRatingCount);

	//if this user ever rate any other movie then plus the rating which after iterations
	//else the predict_rate just is baseline predict rating plus the user bias and movie bias
	if(userRatingCount > 1)
	{
		predict_rate = ((userAverageRating*k+userTotalRating) / (k+userRatingCount))+bi+bu
			+innerDot(user_row, movie_row, itNub);
	}
	else
	{
		predict_rate = ((userAverageRating*k+userTotalRating) / (k+userRatingCount))+bi+bu;
	}
	
	if(predict_rate < 1.0)
	{
		return 1.0;
	}
	if(predict_rate > 5.0)
	{
		return 5.0;
	}

	return predict_rate;
}

double rmseProcess(UserList &userList, double predictRating)
{
	double err;
    double rmse = 0.0;
    int listLen = sizeof(userList);

    for (int i = 0; i < listLen; i++)
    {
    	for(vector<User>::iterator it = userList.begin(); it != userList.end(); it++)
    	{
    		err = static_cast<double>((*it).rating) - predictRating;
    		rmse += err*err;
    	}
    }

	rmse = sqrt(rmse / listLen);
    return rmse;
}

void loadTrain(UserTable &trainMatrix,int &global_totalRating, int &total_ratingCount,
		int *userTotalRating, int *userRatingCount, int *movieTotalRating, int *movieRatingCount)
{
	ifstream fin;
	fin.open(TRAIN_SET);

	char data_char[SIZE_MOVIE];

	if(!fin)
	{
		cout << "training data opening failed" << endl;
		exit(1);
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


		//sotre and add each of movie rating
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
		exit(1);
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

void message_box(string message, bool key)
{
	string sb = message;

	if(key == true)
	{
		cout << sb.c_str() << endl;
	}
}

int main()
{
	UserList trainList; //user list in training data,same user id in same list
	UserTable trainMatrix(SIZE_MOVIE+1);//each row contents a user list, it's a table(matrix)

	Index testUser;
	Index testMovie;
	UserList testList;
	UserTable testMatrix;

	bool key = true;//key for message_box

	//create model
	int userTotalRating[SIZE_USER+1] = {0}; //particular user total rating
	int userRatingCount[SIZE_USER+1] = {0}; //particular user rating counts

	int movieTotalRating[SIZE_MOVIE+1] = {0}; //particular movie total rating
	int movieRatingCount[SIZE_MOVIE+1] = {0}; //how many the movie

	double global_averageRating = 0.0;
	int global_totalRating = 0.0;
	int total_ratingCount = 0;

	message_box("before load train data", key);

	loadTrain(trainMatrix, global_totalRating, total_ratingCount, userTotalRating, userRatingCount
			, movieTotalRating, movieRatingCount);

	message_box("end loading trainning data, beggin load test data", key);

	loadTest(testList);

	message_box("finished loading test data", key);

	global_averageRating =  ROUND((static_cast<double>(global_totalRating)
			/ static_cast<double>(total_ratingCount)));


	//initial moive(bi) and user(bu) bias
	
	double bu[SIZE_USER+1] = {0.0};
	double bi[SIZE_MOVIE+1] = {0.0};


	for(int i = 1; i <= SIZE_USER; i++)
	{
		bu[i] = global_averageRating - getMean(userTotalRating[i], userRatingCount[i]);
	}

	for(int i = 1; i <= SIZE_MOVIE; i++)
	{
		bi[i] = global_averageRating - getMean(movieTotalRating[i], movieRatingCount[i]);
	}

	message_box("initialize vectors of userBase and movieBase ", key);
	vector<vector<double> > userBase;
	vector<vector<double> > movieBase;

	for(int i = 1; i <= SIZE_USER+1; i++)
	{
		vector<double> temp;
		for(int j = 1; j <= 50; j++)
		{
			temp.push_back(1.0);
		}
		userBase.push_back(temp);
	}

	for(int i = 1; i <= SIZE_MOVIE+1; i++)
	{
		vector<double> temp;
		for(int j = 1; j <= 50; j++)
		{
			temp.push_back(1.0);
		}
		movieBase.push_back(temp);
	}

	message_box("finished initialized user and movie base vector and ready initialize necessary parameters", key);
	system("pause");

	//start modeling
	double learnRate = 0.005;
	double lambda = 0.02;
	double pui = 0.0; //predict rating of user u to movie i

	double currentRmse = 0.0;
	double prevRmse = 10000000;

	ofstream result;
	result.open (OUTPUT_FILE);

	
	message_box("Done of initialization necessary parameters, beggining modelling now ", key);
	system("pause");

//	for(int i = 0; i < 460; i++)
//	{
//		rmseProcess(testList, predictRating(userTotalRating[i], userRatingCount[i],bi[i],bu[i]));
//	}
	

	for(int step = 0; step < 50; ++step)
	{
		long double rmse = 0.0;
		int n = 0;
		for(int i = 1; i <= SIZE_USER; i++)
		{
			double sqrtNub = 0.0;
			if(userRatingCount[i] != 0)
			{
				sqrtNub = (1.0) / sqrt(userRatingCount[i]);
				//cout << sqrtNub << endl;
			}
			for(int j = 0; j <userRatingCount[i]; j++)
			{
				int movieID = trainMatrix[i][j].movieID; //this movieID
				int rating = trainMatrix[i][j].rating; //this user rate this movie, the rating
				double bui = global_totalRating - bu[i] - bi[j];
				pui = predictRating(userTotalRating[i], userRatingCount[i], 
					userBase[i], movieBase[i], bi[j], bu[i], 50);
				//original column,shouldn't self testing,should be predict test set
				//result << trainMatrix[i][j].id << "::" << trainMatrix[i][j].movieID << "::" << trainMatrix[i][j].rating <<
				//		"::" << trainMatrix[i][j].time << "::"<< pui << endl;

				double eui = rating - pui; //error about current rating and predict rating
				//cout << eui << endl;
				rmse += eui * eui;
				bu[i] += learnRate * (eui - lambda * bu[j]);
				bi[j] += learnRate * (eui - lambda * bi[j]);

				for(int k =0; k < 50; k++)
				{
					userBase[i][k] += learnRate * (eui * movieBase[movieID][k] - lambda * userBase[i][k]);
					movieBase[movieID][k] += learnRate * (eui * userBase[i][k] - lambda * movieBase[movieID][k]);
				}
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
		//for(int i = 0; i < 460; i++)
		//{
		//	rmseProcess(testList,predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
		//}
	}
	//for(int i = 0; i < 460; i++)
	//{
	//	rmseProcess(testList,predictRating(userTotalRating[i],userRatingCount[i],bi[i],bu[i]));
	//}

//	for(auto it = testList.begin(); it != testList.end(); it++)
//	{
//		//all of iterators for predict fully records in test set
//		predictRating(userTotalRating[i], userRatingCount[i], bi[i], bj[i]);
//		resutl << "write the output" <<;
//	}
	system("psause");
	message_box("multiple userBase and movieBase", key);

	//for(int k = 0; k < 50; k++)
	//{
	//	for(int i = 0; i < 50; i++)
	//	{
	//		cout << userBase[k][i]*movieBase[k][i] << endl;
	//	}
	//}

	


	UserList predict_users;

	for(auto it = testList.begin(); it != testList.end(); it++)
	{
		(*it).predict_rating = predictRating(userTotalRating[(*it).id], userRatingCount[(*it).id], userBase[(*it).id]
						, movieBase[(*it).movieID], bi[(*it).movieID], bu[(*it).id], 50);

		result << (*it).id << "::" << (*it).movieID << "::" << (*it).rating << "::" << (*it).time << "::" << (*it).predict_rating << endl;
	}


	message_box("final measure precedure", key); 

	double measure_score = {0.0};
	int itemCount = 0;

	for(auto it = testList.begin(); it != testList.end(); it++)
	{
		(*it).predict_rating = predictRating(userTotalRating[(*it).id], userRatingCount[(*it).id], userBase[(*it).id]
						, movieBase[(*it).movieID], bi[(*it).movieID], bu[(*it).id], 50);

		measure_score += ((*it).predict_rating - (*it).rating);
		itemCount ++;
	}

	measure_score = sqrt(measure_score/itemCount);

	cout << "final measure MSE score is : " << measure_score << endl;

	system("pause");
	return 0;
}


