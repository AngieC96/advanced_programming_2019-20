#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

enum class months {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

string get_month(const months m) {
  switch (m) {
    case months::jan:
    	return "jan";
    case months::feb:
    	return "feb";
    case months::mar:
    	return "mar";
    case months::apr:
		return "apr";
	case months::may:
		return "may";
	case months::jun:
		return "jun";
	case months::jul:
		return "jul";
	case months::aug:
		return "aug";
	case months::sep:
		return "sep";
	case months::oct:
		return "oct";
	case months::nov:
		return "nov";
	case months::dec:
		return "dec";
	default:
		cout << "Non valid month!" << endl;
		return 0;
  }
}

class Date{
	unsigned int  _day;
	months        _month;
	unsigned int  _year;

	public:
//		Date(const int day, const months month, const int year){
//			_day = day;
//			_month = month;
//			_year = year;
//		};
		Date(const unsigned int day, const months month, const unsigned int year):
			_day{day},
			_month{month},
			_year{year}
		{}
//		Date();
		Date() {}
//		~Date(); //
		int day() const{
			return _day;
		}
		months month() const{
			return _month;
		}
		int year() const{
			return _year;
		}
		void print() const{
			cout << _day << " " << get_month(_month) << " " << _year << endl;
		}
		void add_day() {
			switch (_month){
				case months::jan: case months::mar: case months::may:	//If it fits more cases
				case months::jul: case months::aug: case months::oct:
					if (_day == 31) {
						_day = 1;
						_month = months(((int) _month)+ 1);
					} else {
						_day += 1;
					}
					break;
				case months::apr: case months::jun: case months::sep: case months::nov:
					if (_day == 30) {
						_day = 1;
						_month = months(((int) _month)+ 1);
					} else {
						_day += 1;
					}
					break;
				case months::feb:
					if (_day == 28) {
						_day = 1;
						_month = months(((int) _month)+ 1);
					} else {
						_day += 1;
					}
					break;
				case months::dec:
					if(_day == 31){
						_day = 1;
						_month = months::jan;
						_year += 1;
					} else {
						_day += 1;
					}
			}

		}
		void add_days(const unsigned int n) {
			for(std::size_t k{0}; k < n; ++k){
				add_day();
			}
		}
};


int main() {

	Date date{1,months::mar,2019};
	Date date2{31,months::jan,2019};
	Date date3{28,months::feb,2019};
	Date date4{1,months::dec,2019};

	//cout << date._day <<endl; //error: ‘unsigned int Date::_day’ is private within this context
	cout << date.day() << endl;

	date.print();

	cout << "Example of adding  day:" << endl;
	date2.print();
	date2.add_day();
	date2.print();

	cout << endl;
	date3.print();
	date3.add_day();
	date3.print();

	cout << endl;
	date3.print();
	date3.add_days(31);
	date3.print();

	cout << endl;
	date4.print();
	date4.add_days(31);
	date4.print();


	return 0;
}
