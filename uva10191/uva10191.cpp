/*
uva10191

    As you may already know, there are professors very busy with a filled
    schedule of work during the day. Your professor, let’s call him Professor P, is
    a bit lazy and wants to take a nap during the day, but as his schedule is very
    busy, he doesn’t have a lot of chances of doing this. He would REALLY like,
    however, to take one nap every day. Because he’ll take just one nap, he wants to
    take the longest nap that it’s possible given his schedule. He decided to write
    a program to help him in this task but, as we said, Professor P is very lazy.
    So, he finally decided that YOU must write the program!

    Input
    The input will consist on an arbitrary number of test cases, each test case
    represents one day. The first line of each set contains a positive integer s
    (not greater than 100) representing the number of scheduled appointments during
    that day. In the next s lines there are the appointments in the following
    format: 
            time1 time2 appointment
        Where time1 represents the time which the appointment starts and time2 the
    time it ends. All times will be in the ‘hh:mm’ format, time1 will always be
    strictly less than time2, they will be separated by a single space and all times
    will be greater than or equal to 10:00 and less than or equal to 18:00.
        So, your response must be in this interval as well (i.e. no nap can start
    before 10:00 and last after 18:00).
        The appointment can be any sequence of characters, but will always be in the
    same line. You can assume that no line will be longer than 255 characters, that
    10 ≤ hh ≤ 18 and that 0 ≤ mm < 60.
        You CAN’T assume, however, that the input will be in any specific order.
    You must read the input until you reach the end of file.

    Output
    For each test case, you must print the following line:
    Day #d: the longest nap starts at hh : mm and will last for [H hours and] M minutes.
        Where d stands for the number of the test case (starting from 1) and hh: mm is
    the time when the nap can start. To display the duration of the nap, follow these
    simple rules:
        1. if the total duration X in minutes is less than 60, just print ‘M minutes’,
        where M = X.
        2. if the total duration X in minutes is greater or equal to 60, print
    ‘H hours and M minutes’, where
        H = X ÷ 60 (integer division, of course) and M = X mod 60.
        
        Notice that you don’t have to worry with concordance (i.e. you must
    print ‘1 minutes’ or ‘1 hours’ if it’s the case).
        The duration of the nap is calculated by the difference between the ending time
    free and the begining time free. That is, if an appointment ends at 14:00 and the
    next one starts at 14:47, then you have (14:47)-(14:00) = 47 minutes of possible nap.
        If there is more than one longest nap with the same duration, print the earliest
    one. You can assume that there won’t be a day all busy (i.e. you may assume that there
    will be at least one possible nap).

    Sample Input
    4
    10:00 12:00 Lectures
    12:00 13:00 Lunch, like always.
    13:00 15:00 Boring lectures...
    15:30 17:45 Reading
    4
    10:00 12:00 Lectures
    12:00 13:00 Lunch, just lunch.
    13:00 15:00 Lectures, lectures... oh, no!
    16:45 17:45 Reading (to be or not to be?)
    4
    10:00 12:00 Lectures, as everyday.
    12:00 13:00 Lunch, again!!!
    13:00 15:00 Lectures, more lectures!
    15:30 17:15 Reading (I love reading, but should I schedule it?)
    1
    12:00 13:00 I love lunch! Have you ever noticed it? :)

    Sample Output
    Day #1: the longest nap starts at 15:00 and will last for 30 minutes.
    Day #2: the longest nap starts at 15:00 and will last for 1 hours and 45 minutes. 
    Day #3: the longest nap starts at 17:15 and will last for 45 minutes.
    Day #4: the longest nap starts at 13:00 and will last for 5 hours and 0 minutes
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define ONLINE_JUDGE

#ifndef ONLINE_JUDGE
#include <gmock/gmock.h>
#endif

//struct Appointments {
//  std::string start_time;
//  std::string stop_time;
  //std::string info_;
//};

struct Occupy {
  std::string start_str;
  std::string stop_str;
  int start_time;
  int stop_time;
};

struct Nap {
  std::string nap_start_time;
  int nap_hour;
  int nap_minute;
};

class Note {
public:
  explicit Note();
  void add_appointment(std::string input);
  void get_longest_nap(int number);
  static bool cmp(Occupy x, Occupy y);

private:
  //std::vector<Appointments> appointment;
  std::vector<Nap> nap;
  std::vector<Occupy> occupy_time;
  std::vector<Occupy> m_occupy_time;
};

Note::Note() {}

bool Note::cmp(Occupy x, Occupy y) {
    if(x.start_time != y.start_time)
        return x.start_time < y.start_time;
    return x.stop_time < y.stop_time;
}

/*
original data
8
12:22 16:25 Meeting with vatsal
12:06 15:23 Meeting with Morass
10:16 10:22 Meeting with Vinit
11:26 16:26 Meeting with try
10:11 12:30 Meeting with Morass
10:39 11:38 Meeting with vatsal
12:30 15:58 Meeting with Anjupiter
11:39 14:12 Meeting with try

after sort 
10:00(600) 10:00(600) 
10:11(611) 12:30(750) 
10:16(616) 10:22(622)   //622<750 rm 
10:39(639) 11:38(698)   //698<750 rm
11:26(686) 16:26(986) 
11:39(699) 14:12(852)   //852<986 rm
12:06(726) 15:23(923)   //923<986 rm
12:22(742) 16:25(985)   //985<986 rm
12:30(750) 15:58(958)   //958<986 rm
18:00(1080) 18:00(1080) 

after remove
10:00(600) 10:00(600) 
10:11(611) 12:30(750) 
11:26(686) 16:26(986) 
18:00(1080) 18:00(1080) 
*/

void Note::get_longest_nap(int number) {
  std::string start_time("10:00");
  int logest_nap_time = 0;
  int max_stop_time = 600;
  int temp;

  std::sort(occupy_time.begin(), occupy_time.end(), cmp);
 
  for (auto it = occupy_time.begin(); it != occupy_time.end(); ++it) {
      temp = 0;
#if 0  
      std::cout << ">>" << it->start_str << "(" << it->start_time << ")" << " " 
                        << it->stop_str << "(" << it->stop_time << ")" << " " <<std::endl;
#endif
      
      if(it->stop_time > max_stop_time)
        max_stop_time = it->stop_time;

      if(it->stop_time < max_stop_time){
          continue;
      } 
    
      m_occupy_time.push_back({it->start_str, it->stop_str, it->start_time, it->stop_time});
  }

#if 0  
  std::cout << "----------------------" <<  std::endl;
  for (auto it = m_occupy_time.begin(); it != m_occupy_time.end(); ++it) {
      std::cout << ">>" << it->start_str << "(" << it->start_time << ")" << " " 
                        << it->stop_str << "(" << it->stop_time << ")" << " " <<std::endl ;
  }
#endif

  for (auto it = m_occupy_time.begin()+1; it != m_occupy_time.end(); ++it) {
      temp = (it)->start_time - (it-1)->stop_time;
      if (temp < 0)
          continue;

      if(temp > logest_nap_time){
          logest_nap_time = temp;
          start_time = (it-1)->stop_str;
      }
  }

  std::cout << "Day #"<<number<<": the longest nap starts at "<< start_time <<" and will last for ";
  if (logest_nap_time < 60)   
      std::cout << logest_nap_time%60;
  else 
      std::cout << logest_nap_time/60 << " hours and " << logest_nap_time%60;
  std::cout << " minutes." <<std::endl;
}

void Note::add_appointment(std::string input) {
  int pos;

  pos = input.find(' ');
  std::string start_time = input.substr(0, pos);
  input.erase(0, pos + 1);

  pos = input.find(' ');
  std::string stop_time = input.substr(0, pos);
  input.erase(0, pos + 1);
  
  occupy_time.push_back({start_time,
                         stop_time,
                         stoi(start_time.substr(0, 2))*60 + stoi(start_time.substr(3, 2)),  
                         stoi(stop_time.substr(0, 2))*60 + stoi(stop_time.substr(3, 2))});
}

void solve_uva_problem(std::istream &is, std::ostream &os) {
  std::string line;
  std::string input;
  int appointments_times;
  int item = 1;

#if 1
  while (1) {
    getline(is, line);

    if (line.empty()) {
      break;
    }

    appointments_times = stoi(line);

    std::shared_ptr<Note> apo_ = std::make_shared<Note>();
    {
      apo_->add_appointment("10:00 10:00 first");
      for (int i = 0; i < appointments_times; i++) {
        getline(is, input);
        apo_->add_appointment(input);
      }
      apo_->add_appointment("18:00 18:00 last");

      apo_->get_longest_nap(item);
      item++;
    }
  }
#endif
}

int main(int argc, char **argv) {
#ifdef ONLINE_JUDGE
  solve_uva_problem(std::cin, std::cout);
#else
  testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
#endif
}

#ifndef ONLINE_JUDGE
TEST(uva10954, test_string1) {
  std::istringstream iss("3\n"
                         "6 5 4\n"
                         "10\n"
                         "9 5 48 2 4 5 6 3 5 4\n"
                         "10\n"
                         "3 4 5 4 7 2 3 8 4 5\n"
                         "0\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("24\n"
            "224\n"
            "147\n",
            oss.str());
}

TEST(uva10954, test_string2) {
  std::istringstream iss("8\n"
                         "4 4 6 6 8 8 10 10\n"
                         "8\n"
                         "4 6 6 7 7 8 8 9\n"
                         "8\n"
                         "3 4 6 6 6 8 8 9\n"
                         "8\n"
                         "3 4 5 5 5 5 8 9\n"
                         "2\n"
                         "99999 0\n"
                         "4\n"
                         "99997 49999 49999 49999\n"
                         "4\n"
                         "49999 99998 49999 49999\n"
                         "0\n");
  std::ostringstream oss;
  solve_uva_problem(iss, oss);
  EXPECT_EQ("166\n"
            "165\n"
            "148\n"
            "130\n"
            "99999\n"
            "499988\n"
            "499990\n",
            oss.str());
}
#endif
