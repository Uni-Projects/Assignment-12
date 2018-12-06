#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;


struct Gift
{
    string id;
    int price;
};

struct Person
{
    string name;
    vector <Gift> wishlist;
    int budget;
};


vector <Gift> gift_store;

ifstream& operator>> (ifstream& input, Gift& gift)
{
    input >> gift.price;
    getline(input,gift.id) ;
    gift.id.erase(0,1);
}
ostream& operator<< (ostream& output, Gift& gift)
{
    output << "Price: " << gift.price << "\n"
           << "Id: " << gift.id << endl ;
}

ifstream& operator>> (ifstream& input, Person& person)
{
    Gift temp;

    input >> person.budget;
    input.ignore();
    while (!input.eof())
    {
        getline(input,temp.id) ;
        temp.price = 0;
        person.wishlist.push_back(temp);
    }

}

struct Attempt
{
    int n_of_items;
    vector <Gift> present_list;
    int tot_spent;
};
bool sub(Attempt& best, Attempt& solution)
{
    best.n_of_items = solution.n_of_items;
    best.tot_spent = solution.tot_spent;
    for (int i = 0 ; i < solution.present_list.size(); i++)
      best.present_list.push_back(solution.present_list[i]);

}

Attempt solution;
Attempt best;

int p = 0 ;

int gifts (vector <Gift>& wishlist, int budget,int g)
{
    if (g == wishlist.size()-1)
      return 1;

   if (budget == 0)
   {
       sub(best,solution);
       return 1;
   }

   if (wishlist[g].price <= budget)
   {
       solution.present_list[p].id = wishlist[g].id ;
       p++;
       solution.n_of_items ++;
       solution.tot_spent += wishlist[g].price ;
       return gifts(wishlist,budget - wishlist[g].price, g+1);
   }

    if (wishlist[g].price > budget)
    {
        return gifts(wishlist,budget,g+1);
    }



}

int main()
{
    ifstream input;
    Gift temp;
    Person andrew;
    Person belle;
    andrew.name = "Andrew";
    belle.name = "Belle";

    input.open("giftstore.txt");

    while (!input.eof())
    {
        input >> temp;
        gift_store.push_back(temp);
    }

    cout << "GIFTSTORE: " << endl;

    for (int i = 0 ; i < gift_store.size()-1; i++)
    {
        cout << gift_store[i];
    }

    input.close();

    input.open("Andrew.txt");

    input >> andrew;

    input.close();

    input.open("Belle.txt");

    input >> belle;

    for (int i = 0 ; i < andrew.wishlist.size() ;i++)
    {
        for (int j = 0 ; j < gift_store.size();j++)
        {
            if (andrew.wishlist[i].id == gift_store[j].id)
               andrew.wishlist[i].price = gift_store[j].price;

        }
    }

    for (int i = 0 ; i < belle.wishlist.size() ;i++)
    {
        for (int j = 0 ; j < gift_store.size();j++)
        {
            if (belle.wishlist[i].id == gift_store[j].id)
               belle.wishlist[i].price = gift_store[j].price;

        }
    }
    cout << endl ;
    cout << endl ;

    cout << andrew.name << endl;
    cout << endl ;
    cout << "Budget: " << andrew.budget << endl ;
    cout << endl ;
    for (int i = 0 ; i < andrew.wishlist.size()-1; i++)
    {
        cout << andrew.wishlist[i] << endl ;
    }

    cout << belle.name <<endl;
    cout << endl ;
    cout << "Budget: " << belle.budget << endl ;
    cout << endl ;

    for (int i = 0 ; i < belle.wishlist.size()-1; i++)
    {
        cout << belle.wishlist[i] << endl ;
    }

    gifts(andrew.wishlist,andrew.budget,0);
    /*
    for (int i = 0 ; i < solution.present_list.size()-1; i++)
    {
        cout << solution.present_list[i] << endl ;
    }
*/
    return 0;
}
