#ifndef COMMON_CPP_
#define COMMON_CPP_


vector<string> split(const string &n)
{
	vector<string> temp;
	char *token = (char*)n.c_str();
	char *pt = NULL;
	char delimis[] = "::";
	pt = strtok(token, delimis);
	//get split first time and return a pointer, pt catch it

	while(pt != NULL)
	{
		if(pt != NULL)
		{
			temp.push_back(pt);
			//push first, because the pt now is begin tokenizer
		}
		pt = strtok(NULL, delimis);
		//it's like pt++
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

double predictRating(int userTotalRating, int userRatingCount, double bi, double bu)
{
	//the user i, predict the rating of item j

	//baseline predict rating r^ui = u +bi +bu
	//add bias, bi is item bias, bu is user bias

	const int k = 25;
	double userAverageRating = getMean(userTotalRating,userRatingCount);
	double predict_rate = ((userAverageRating*k+userTotalRating) / (k+userRatingCount))+bi+bu;

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

double rmseProcess(UserList &userList,double predictRating)
{
	//lack item element
	double err;
    double rmse = 0.0;
    int listLen = userList.max_size();

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

#endif // COMMON_CPP_



