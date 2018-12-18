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
    //pre:
    assert(input.is_open());
    //post: the gift is read correctly
    input >> gift.price;
    getline(input,gift.id) ;
    gift.id.erase(0,1);
}
ostream& operator<< (ostream& output, Gift& gift)
{
    //pre:
    assert(true);
    //post: formats the output.
    output << "Price: " << gift.price << "\n"
           << "Id: " << gift.id << endl ;
}

ifstream& operator>> (ifstream& input, Person& person)
{
    //pre:
    assert(input.is_open());
    //post: read the wishlist of a person
    Gift temp;

    input >> person.budget;
    input.ignore();
    while (!input.eof())
    {
        getline(input,temp.id) ;
        temp.price = 0 ;
        person.wishlist.push_back(temp);
    }

}

struct Attempt
{
    int n_of_items;
    vector <Gift> present_list;
    int tot_spent;
};

bool operator<< (Attempt& first, Attempt& second)
{
    //pre:
    assert(true);
    //post: return true if the first expense is less than the second one.
    return (first.tot_spent < second.tot_spent);
}
bool sub(Attempt& best, Attempt& solution)
{
    //pre:
    assert(true);
    //post: substitute values in best with the one in solution.
    Gift temp;
    best.n_of_items = solution.n_of_items;
    best.tot_spent = solution.tot_spent;
    for (int i = 0 ; i < solution.present_list.size(); i++)
    {
         best.present_list.push_back(temp);
        best.present_list[i] = solution.present_list[i];
    }


}

Attempt best;

void gifts (vector <Gift> wishlist, int budget,int i)
{
    //pre:
    assert(budget>0);
    //post: the function computes the highest budget lists of item in the person wish list.
    Attempt solution;
    solution.n_of_items = 0;
    solution.tot_spent = 0;
    int p = 0 ;
    int j = i;


    if (i < wishlist.size())
    {
    while ((budget - solution.tot_spent) >= 0)
    {
        if (j == wishlist.size())
        {
            if (best << solution)
              sub(best,solution);
            if (i < wishlist.size())
              return gifts(wishlist,budget,i+1);
            else
                break;
        }

        if (wishlist[j].price + solution.tot_spent <= budget )
        {
            Gift temp;
            solution.present_list.push_back(temp);

            solution.present_list[p].id = wishlist[j].id;
            solution.tot_spent = solution.tot_spent + wishlist[j].price;
            solution.n_of_items++;
            p++;
            j++;
        }else
            j++;

     }
    }
}

int main()
{
    //pre:
    assert(true);
    //post: read the giftshop file and wish lists, then it calls the function gifts and print the best solution found.

    ifstream input;
    string name;
    string file_name;
    Gift temp;
    Person p;

    input.open("giftstore.txt");

    while (!input.eof())
    {
        input >> temp;
        gift_store.push_back(temp);
    }

    cout << "Gift-shop loaded!" << endl;
    input.close();

    cout << "Insert wishlist: ";
    getline(cin,file_name);
    cout << endl;
    int pos = file_name.find('.');
    name = file_name;
    name.erase(pos, name.size());

    input.open(file_name.c_str());

    if (input.is_open())
        cout << "Whislist loaded correctly!" << endl ;

    input >> p;
    p.name = name;

    input.close();

    for (int i = 0 ; i < p.wishlist.size() ;i++)
    {
        for (int j = 0 ; j < gift_store.size();j++)
        {
            if (p.wishlist[i].id == gift_store[j].id)
               p.wishlist[i].price = gift_store[j].price;

        }
    }

    gifts(p.wishlist,p.budget,0);

    cout << "OPTIMAL WISH LIST:"<<endl;
    for (int i = 0 ; i < best.n_of_items; i++)
    {
        cout << best.present_list[i].id << endl ;
    }
    cout << "Spent: " << best.tot_spent << " out of " << p.budget << endl;
    cout << "That means we spent "  << (double)best.tot_spent/(double)p.budget*100 << "% of the budget" << endl ;

    return 0;
}
