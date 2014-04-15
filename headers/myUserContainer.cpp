#ifndef MYUSERCONTAINER_CPP_
#define MYUSERCONTAINER_CPP_

int myUserContainer::size()
{
	return container.size();
}

User myUserContainer::searchUser(int userID)
{
	static_assert(container[userID] == NULL,"this user not exist");

}

void myUserContainer::insert_end(User user)
{
	container.push_back(user);
}

int myUserContainer::checkUser(int userID)
{
	/*static_assert(container[userID] == NULL,"this user not exist in the users list");*/

	return mybinary_search(container, 0, container.size()-1, userID);
}
	


#endif MYUSERCONTAINER_CPP_
