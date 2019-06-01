#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

class Date
{
public:
    explicit Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    int GetYear() const
    {
        return year;
    }
    int GetMonth() const
    {
        return month;
    }
    int GetDay() const
    {
        return day;
    }
private:
    int year;
    int month;
    int day;
};

ostream& operator<<(ostream& stream, const Date& dt)
{
    stream << setw(4) << setfill('0') << dt.GetYear() << "-"
           << setw(2) << setfill('0') << dt.GetMonth() << "-"
           << setw(2) << setfill('0') << dt.GetDay();
}

bool operator<(const Date& lhs, const Date& rhs)
{

}

class Database {
public:
    void AddEvent(const Date& date, const string& event)
    {
        events[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {
        cout << "DeleteEvent: " << event << " on date " << date << endl;
    }
    int  DeleteDate(const Date& date)
    {
        cout << "DeleteDate: " << date << endl;
    }
    set<string> Find(const Date& date) const
    {   
        cout << "Find on date: " << date << endl;
    }
    void Print() const
    {
        for (const auto& item : events)
        {
            for (const auto& ev : item.second)
            {
                cout << item.first << " " << ev << endl;
            }
        }
    }
private:
    map<Date, set<string>> events;

};

void valiDate(stringstream& stream, const string& str_dt)
{
    if (stream.peek() != '-')
    {
        stringstream ss;
        ss << "Wrong date format: " << str_dt;
        throw runtime_error(ss.str());
    }
    stream.ignore(1);
}


Date parse_date(const string& date)
{
    stringstream ss(date);
    int y, m, d;
    ss >> y;
    valiDate(ss, date);
    ss >> m;
    valiDate(ss, date);
    ss >> d;

    if (m < 1 or m > 12)
    {
        string err = "Month value is invalid: " + to_string(m);
        throw runtime_error(err);
    }
    if (d < 1 or d > 31)
    {
        string err = "Day value is invalid: " + to_string(d);
        throw runtime_error(err);
    }   

    return Date(y, m, d);
}


void exec_cmd(const string& command, Database& db)
{
    stringstream ss(command);
    string cmd, str_date, ev;
    ss >> cmd;
    ss >> str_date;
    ss >> ev;

    if (cmd == "Add")
    {
        Date dt = parse_date(str_date);
        db.AddEvent(dt, ev);
    }
    else if (cmd == "Del")
    {
        Date dt = parse_date(str_date);
        if (ev.empty())
        {
            int N = db.DeleteDate(dt);
            cout << "Deleted " << N << " events" << endl;
        }
        else
        {
            if (db.DeleteEvent(dt, ev))
            {
                cout << "Deleted successfully" << endl;
            }
            else
            {
                cout << "Event not found" << endl;
            }            
        }
        
    }
    else if (cmd == "Find")
    {
        Date dt = parse_date(str_date);
        set<string> events = db.Find(dt);        
    }
    else if (cmd == "Print")
    {
        db.Print();
    }
    else if (cmd == ""){}
    else
    {
        string err = "Unknown command: " + cmd;
        throw runtime_error(err);
    }
}

int main()
{
    Database db;
    
    string command;
    while (getline(cin, command))
    {
        try
        {
            exec_cmd(command, db);
        }
        catch(const exception& e)
        {
            cout << e.what() << endl;
            return 1;
        }
    }

return 0;
}