#include <string>
#include <stack>
#include <queue>
#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <boost/iterator/counting_iterator.hpp>

#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE    
#include <gmock/gmock.h>
#endif

class Train
{
    public:
        Train (int count, std::stringstream &seqnum) : count_(count)
    {
        init_track_A();
        init_track_B(seqnum);
    };
        bool is_track_B_reasonable();

    private:
        void init_track_A();
        void init_track_B(std::stringstream &seqnum);
    private:
        int count_;
        std::queue<int> track_A;
        std::queue<int> track_B;
        std::stack<int> station_S;
};

bool Train::is_track_B_reasonable()
{
    while (!track_B.empty())
    {
        int tB = track_B.front();
        int tA = track_A.empty() ? 0 : track_A.front();
        int tS = station_S.empty() ? 0 : station_S.top();

        /* from track_A to track_B */
        if (tB == tA)
        {
            track_A.pop();
            track_B.pop();
            continue;
        }      
        /* from station_S to track_B */
        else if (tB == tS)
        {
            station_S.pop();
            track_B.pop();
            continue;
        }
        /* no train */
        else if (track_A.empty())
        {
            return false;
        }            
        /* from track_A to station_S */
        else
        {
            track_A.pop();
            station_S.push(tA);
        }
    }
    return true;
}

void Train::init_track_B(std::stringstream &seqnum)
{
    for(int i=0; i<count_; i++)
    {
        int number;
        seqnum >> number;
        track_B.push(number);
    }
}

void Train::init_track_A()
{
#if 1    
    for (int i=1; i<=count_; i++)
        track_A.push(i);
#else /* or use boost */
    std::queue<int> q(boost::counting_iterator<int>(1), boost::counting_iterator<int>(count_));
    track_A = q;
#endif
}

void resolve_uva(std::istream & is, std::ostream & os)
{
    std::string line;
    int last_num = -1;
    int first_num;

    while (getline(is, line))
    {
        std::stringstream seqnum(line);
        /* is there a space ?
         *           No: means only one number. It is a Track_A's init number
         *                     Yes: they are the Track_B's test data */
        size_t space_count = std::count(line.begin(), line.end(), ' ');

        if (space_count == 0) /* no space means Track_A's init number */
        {
            seqnum >> first_num;

            /* is the continuous num zero ? */
            if ((last_num == 0) & (first_num == 0)) 
                return; // end the test
            else    
            {
                last_num = first_num;
                if (first_num == 0)
                    os << std::endl;

                continue;
            }                
        }

        Train train(first_num, seqnum);
        bool answer = train.is_track_B_reasonable();
        os << ((answer == true) ? "Yes" : "No") << std::endl;
    }        
}

int main(int argc, char** argv)    
{
#ifdef ONLINE_JUDGE
    resolve_uva(std::cin, std::cout);
    return 0;
#else    
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
#endif    
}
