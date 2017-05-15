#include <chrono>
#include <random>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include <typeinfo>
#include <array>
#include <algorithm>
#include <numeric>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
//#include <Windows.h>

using namespace std;



#define clubUCode L"\u2663"
#define diamondUCode L"\u2666"
#define heartUCode L"\u2665"
#define spadeUCode L"\u2660"

enum SUIT
{
	CLUB,
	DIAMOND,
	HEART,
	SPADE
};

struct card
{
	int rank;
	SUIT suit;
};

struct suitSort
{
	bool operator()(const card& x, const card& y) const
	{
		return x.suit < y.suit;
	}
};

struct rankSort
{
	bool operator()(const card& x, const card& y) const
	{
		return x.rank < y.rank;
	}
};

#pragma region HELPER_FUNCTIONS

void clearScreen()
{
	system("CLS");
}

void clearAdvance()
{
	char temp;
	cout << "Press ENTER to continue";
	do
	{
		temp = _getch();	
	} while (temp != '\r');
	clearScreen();
}

std::string steadyMsecTimeStamp(const std::chrono::steady_clock::time_point& start, const std::chrono::steady_clock::time_point& end)
{
	chrono::milliseconds steady_result(chrono::duration_cast<chrono::milliseconds>(end - start).count());

	chrono::hours   hh = chrono::duration_cast<chrono::hours>(steady_result);
	chrono::minutes mm = chrono::duration_cast<chrono::minutes>(steady_result % chrono::hours(1));
	chrono::seconds ss = chrono::duration_cast<chrono::seconds>(steady_result % chrono::minutes(1));
	chrono::milliseconds msec = chrono::duration_cast<chrono::milliseconds>(steady_result % chrono::seconds(1));

	string ts;

	std::stringstream stream;
	stream << setfill('0') << setw(2) << hh.count() << ":"
						   << setw(2) << mm.count() << ":"
						   << setw(2) << ss.count() << ":"
						   << setw(3) << msec.count();

	ts = stream.str();

	return ts;
}

std::string steadySecTimeStamp(const std::chrono::steady_clock::time_point& start, const std::chrono::steady_clock::time_point& end)
{
	chrono::seconds steady_result(chrono::duration_cast<chrono::seconds>(end - start).count());

	chrono::hours   hh = chrono::duration_cast<chrono::hours>(steady_result);
	chrono::minutes mm = chrono::duration_cast<chrono::minutes>(steady_result % chrono::hours(1));
	chrono::seconds ss = chrono::duration_cast<chrono::seconds>(steady_result % chrono::minutes(1));

	string ts;

	std::stringstream stream;
	stream << setfill('0') << setw(2) << hh.count() << ":"
						   << setw(2) << mm.count() << ":"
						   << setw(2) << ss.count();

	ts = stream.str();

	return ts;
}

std::string systemDateStamp(const std::chrono::system_clock::time_point& tp)
{
	std::time_t t = std::chrono::system_clock::to_time_t(tp);
	std::string ds = std::ctime(&t);    
	ds.resize(ds.size() - 1);            
	return ds;
}


int numericInput(int maxLength)
{
	char temp = 0;
	bool cont = false;
	int ret = 0;
	int digits = 0;

	do
	{
		temp = _getch();
		if (isdigit(temp))
		{
			if (digits < maxLength) {
				_putch(temp);
				if(ret == 0)
					ret += static_cast<int>(temp - '0');			
				else
					ret = ret * 10 + static_cast<int>(temp - '0');
				digits++;		
			}
		}
		else if (temp == '\r')
		{
			cont = true;
		}
		else if (temp == '\b' && digits!=0)
		{
			_putch(temp);
			_putch(' ');
			_putch(temp);
			ret /= 10;
			digits--;			
		}
	} while (cont == false);

	return ret;
}

bool yesNoInput()
{
	char temp = 'Y';
	bool cont = false;
	bool ret = true;
	_putch(temp);
	_putch('\b');

	do {
		temp = _getch();
		if (temp == 'Y' || temp == 'y')
		{
			_putch('Y');
			_putch('\b');
			ret = true;
		}
		else if (temp == 'N' || temp == 'n')
		{
			_putch('N');
			_putch('\b');
			ret = false;
		}
		else if (temp == '\r')
		{
			cont = true;
		}

	} while (cont == false);

	return ret;
}

void printUnicode(const wstring& s)
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	wcout << s;
	_setmode(_fileno(stdout), _O_TEXT);

}
#pragma endregion

int main()
{



#pragma region VARIABLES

	// clocks and timepoints
	auto steadyClock = chrono::steady_clock();
	chrono::steady_clock::time_point programStart;
	programStart = steadyClock.now();

	chrono::steady_clock::time_point programEnd;
	chrono::steady_clock::time_point steady_tp1;
	chrono::steady_clock::time_point steady_tp2;

	auto sysClock = chrono::system_clock();	

	chrono::system_clock::time_point system_tp1;
	chrono::system_clock::time_point system_tp2;

	auto highResClock = chrono::high_resolution_clock();
	
	chrono::high_resolution_clock::time_point highRes_tp1;
	chrono::high_resolution_clock::time_point highRes_tp2;

	system_tp1 = sysClock.now();
	steady_tp1 = steadyClock.now();	
	highRes_tp1 = highResClock.now();

	// durations
	chrono::duration<int> thirtySeconds(30);
	chrono::duration<int, std::ratio<60>> fiveMinutes(5);
	chrono::duration<int, std::ratio<3600>> twoHours(2);
	chrono::duration<int, std::ratio<1,60>> sixtyFPS_Tick(1);

	chrono::hours day(24);
	
	chrono::duration<double, std::nano> nanoTick;

	chrono::system_clock::time_point epoch_tp;
	
	using ms = chrono::duration<float, std::milli>; //milliseconds as float
	using sec = chrono::duration<float>;  //seconds as float
	
	// 5. standard random engine execution time
	default_random_engine DeRaEn1;
	int min;
	int max;
	int iter;
	uniform_int_distribution<int> dist2;
	// 6. standard random engine seeded
	default_random_engine DeRaEn2(chrono::steady_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> dist1(1, 10);

	

	int seed = 0;

	// 7. dice roll
	default_random_engine DeRaEn3;
	uniform_int_distribution<int> distDice(1, 6);
	chrono::steady_clock::time_point seedTime;
	std::array<int, 4> diceRolls;
	array<int, 4>::iterator smallest;
	int sum;
	
	// 8. shuffle
	default_random_engine shuffleEn;
	array<card, 52> deck;
	wstring club = clubUCode;
	wstring diamond = diamondUCode;
	wstring heart = heartUCode;
	wstring spade = spadeUCode;
	for (int i = 0; i < deck.size();i++) {
		deck[i].rank = i%13+1;
		switch (i/13)
		{
		case SUIT::CLUB:
			deck[i].suit = CLUB;
			break;
		case SUIT::DIAMOND:
			deck[i].suit = DIAMOND;
			break;
		case SUIT::HEART:
			deck[i].suit = HEART;
			break;
		case SUIT::SPADE:
			deck[i].suit = SPADE;
			break;
		default:
			break;
		}

	}


	// menu and input
	char temp;
	char menu = '0';
	bool cont = false;

#pragma endregion

#pragma region PROGRAM_LOOP

	do {  	
		
		cout << "\t\t\t---------\n"
			 << "\t\t\tMAIN MENU\n"
		     << "\t\t\t---------\n\n"
		     << "\tCHRONO:\n"
		     << "\t\t1.\tPrint Test Durations\n"
			 << "\t\t2.\tPrint Clock Type Stats\n"
			 << "\t\t3.\tDate Stamp\n"
			 << "\t\t4.\tSession Time\n"
			 << "\tRANDOM:\n"
			 << "\t\t5.\tRandom Number /w Benchmark\n"
			 << "\t\t6.\tSeeded Random\n"
			 << "\t\t7.\tDice Roll\n"
			 << "\t\t8.\tDeck Shuffle\n\n"
		     << "\t0. Exit\n" << endl;
	
		do
		{
			menu = _getch();
			if (isdigit(menu)){
				_putch(menu);		
			}
		} while (!isdigit(menu));
		
		clearScreen();
		switch (menu)
		{

		case '1': // test durations output

			cout << "Test Durations" << "\n"
				 << "--------------" << "\n"
				 << "thirtySeconds is:\t\t\t" << thirtySeconds.count() << "\n"
				 << "3 * thirtySeconds is:\t\t\t" << (thirtySeconds * 3).count() << "\n\n"

				 << "fiveMinutes is:\t\t\t\t" << fiveMinutes.count() << "\n"
				 << "10 * fiveMinutes is:\t\t\t" << (10 * fiveMinutes).count() << "\n\n"

				 << "twoHours is:\t\t\t\t" << twoHours.count() << "\n"
				 << "5 * twoHours is:\t\t\t" << (5 * twoHours).count() << "\n\n"

				 << "sixtyFPS_Tick is:\t\t\t" << sixtyFPS_Tick.count() << "\n"
				 << "30 * sixtyFPS_Tick is:\t\t\t" << (30 * sixtyFPS_Tick).count() << "\n\n"

				 << "day is:\t\t\t\t\t" << day.count() << "\n"
				 << "2 * day is:\t\t\t\t" << (2 * day).count() << "\n"
				 << "day - twoHours is:\t\t\t" << (day - twoHours).count() << "\n\n"

				 << "1 sixtyFPS_Tick is:\t\t\t" << chrono::duration_cast<sec>(sixtyFPS_Tick * 1).count() << "\tseconds\n"
				 << "1 sixtyFPS_Tick is:\t\t\t" << chrono::duration_cast<ms>(sixtyFPS_Tick * 1).count() << "\t\tmillisecconds\n\n";

			clearAdvance();
			break;
		case '2': // display clock stats
		
			cout << "System Clock" << "\n"
				 << "------------" << "\n"
				 << "is steady:\t\t" << (chrono::system_clock::is_steady ? "yes" : "no") << "\n"
				 << "min:max duration:\t" << chrono::system_clock::duration::min().count() << ":" << chrono::system_clock::duration::max().count() << "\n"
				 << "duration type:\t\t" << typeid(chrono::system_clock::rep).name() << "\n"
				 << "seconds ratio:\t\t" << std::chrono::system_clock::period::num << "/" << std::chrono::system_clock::period::den << "\n";
			nanoTick = chrono::system_clock::duration(1);
			cout << "accuracy:\t\t" << nanoTick.count() << " ns\n"

				 << "\nSteady Clock" << "\n"
				   << "------------" << "\n"
				 << "is steady:\t\t" << (chrono::steady_clock::is_steady ? "yes" : "no") << "\n"
				 << "min:max duration:\t" << chrono::steady_clock::duration::min().count() << ":" << chrono::steady_clock::duration::max().count() << "\n"
				 << "duration type:\t\t" << typeid(chrono::steady_clock::rep).name() << "\n"
				 << "seconds ratio:\t\t" << std::chrono::steady_clock::period::num << "/" << std::chrono::steady_clock::period::den << "\n";
			nanoTick = chrono::steady_clock::duration(1);
			cout << "accuracy:\t\t" << nanoTick.count() << " ns\n"

				 << "\nHigh Res Clock" << "\n"
				   << "--------------" << "\n"
				 << "is steady:\t\t" << (chrono::high_resolution_clock::is_steady ? "yes" : "no") << "\n"
				 << "min:max duration:\t" << chrono::high_resolution_clock::duration::min().count() << ":" << chrono::high_resolution_clock::duration::max().count() << "\n"
				 << "duration type:\t\t" << typeid(chrono::high_resolution_clock::rep).name() << "\n"
				 << "seconds ratio:\t\t" << std::chrono::high_resolution_clock::period::num << "/" << std::chrono::high_resolution_clock::period::den << "\n";
			nanoTick = chrono::high_resolution_clock::duration(1);
			cout << "accuracy:\t\t" << nanoTick.count() << " ns\n\n";

			clearAdvance();
			break;
		case '3':  // using ctime to output a date stamp

			cout << "Date Stamp\n"
				 << "----------\n"

				 << "epoch:\t\t" << systemDateStamp(epoch_tp) << "\n\n"

				 << "program start:\t" << systemDateStamp(system_tp1) << "\n\n"

				 << "current:\t" << systemDateStamp(sysClock.now()) << "\n\n";

			clearAdvance();

			break;
		case '4':  // duration casts, (time point - time point) to make durations and basic output formatting

			system_tp2 = sysClock.now();
			steady_tp2 = steadyClock.now();
			highRes_tp2 = highResClock.now();
			chrono::seconds steady_result(chrono::duration_cast<chrono::seconds>(steady_tp2 - steady_tp1).count());

			cout << "Session Time\n"
				 << "------------\n"

				 << "no cast system_clock:\t\t" << (system_tp2 - system_tp1).count() << "\n"
				 << "no cast steady_clock:\t\t" << (steady_tp2 - steady_tp1).count() << "\n"
				 << "no cast high_resolution:\t" << (highRes_tp2 - highRes_tp1).count() << "\n\n"

				 << "seconds system_clock:\t\t" << chrono::duration_cast<sec> (system_tp2 - system_tp1).count() << "\n"
				 << "seconds steady_clock:\t\t" << chrono::duration_cast<sec>(steady_tp2 - steady_tp1).count() << "\n"
				 << "seconds high_resolution:\t" << chrono::duration_cast<sec>(highRes_tp2 - highRes_tp1).count() << "\n\n"

				 << "minutes system_clock:\t\t" << chrono::duration_cast<chrono::minutes> (system_tp2 - system_tp1).count() << "\n"
				 << "minutes steady_clock:\t\t" << chrono::duration_cast<chrono::minutes>(steady_tp2 - steady_tp1).count() << "\n"
				 << "minutes high_resolution:\t" << chrono::duration_cast<chrono::minutes>(highRes_tp2 - highRes_tp1).count() << "\n\n";

			cout << "formatted steady_clock:\t";
				chrono::hours   hh = chrono::duration_cast<chrono::hours>(steady_result);
				chrono::minutes mm = chrono::duration_cast<chrono::minutes>(steady_result % chrono::hours(1));
				chrono::seconds ss = chrono::duration_cast<chrono::seconds>(steady_result % chrono::minutes(1));
			
		
			cout << "     " << setfill('0') << setw(2) << hh.count() << ":"
													   << setw(2) << mm.count() << ":"
													   << setw(2) << ss.count() <<  "\n\n";

			clearAdvance();
		
			break;
		case '5': // default random engine initialization and timer

			do {
				cout << "Simple Random Number Timer\n"
					 << "--------------------------\n";
			
				cout << "Enter min value:";
				
				min = numericInput(5);
				
				cout << "\nEnter max value:";
				max = numericInput(5);
				cout << endl;
				if (min < max){
					cont = true;

					cout << "Enter number of values to generate:";
					iter = numericInput(7);
				}
				else{
					cout << "Min value must be smaller than max value!\n";
					clearAdvance();
				}



			} while (cont == false);
			{ //uniform_int_distribution needs a scope because we're in a switch
			//	uniform_int_distribution<int> dist1(min, max);
				dist2.param(uniform_int<int>::param_type (min,max));

				cout << "\n\nPrinting numbers...\n";
				chrono::steady_clock::time_point start = steadyClock.now();
				for(int i = 0; i< iter;i++)
				{
					cout << dist2(DeRaEn1)<< " ";
			
				}
				chrono::steady_clock::time_point end = steadyClock.now();
				cout << "\n\nTime to print:\t" << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns\n\n" << steadyMsecTimeStamp(start, end) << "\n\n";
					

			}

			cont = false;		
			clearAdvance();
			break;
		case '6': // default random engine with numeric seed

			cout << "Seeded Random\n"
				 << "-------------\n";
			do{
				cout << "Enter new seed: ";
				seed = numericInput(10);
				DeRaEn2.seed(seed);
				cout << "\n\n\t";
				for (int i = 0; i< 10;i++)
				{
					cout << dist1(DeRaEn2) << " ";

				}
				cout << "\n\nAgain? Y/N: ";
				cont = yesNoInput();
				cout <<"\n\n";
			} while (cont == true);

			cont = false;
			clearScreen();
			break;

		case '7':  // simulated dice roll

			cout << "Dice Roll\n"
				 << "---------\n";
			do {
				cout << "Rolling 4d6...\n\n\t";
				seedTime = chrono::steady_clock::now();
				DeRaEn3.seed(chrono::duration_cast<chrono::seconds>(seedTime.time_since_epoch()).count());
				for (int i = 0; i < 4;i++)
				{
					diceRolls[i] = distDice(DeRaEn3);
					cout << diceRolls[i] << "\t";

				}
				smallest = min_element(begin(diceRolls), end(diceRolls));
				cout << "\n\nDropping lowest... " << *smallest;
				*smallest = 0;
				sum = accumulate(begin(diceRolls), end(diceRolls), 0);
				cout << "\n\nTotal score:\t\t" << sum;
				cout << "\n\nAgain? Y/N: ";
				cont = yesNoInput();
				cout << "\n\n";
			} while (cont == true);

			cont = false;
			clearScreen();
			break;
		case '8': // shuffle

			cout << "Deck Shuffle\n"
				 << "------------\n";
			cont = true;
			do{
				for(int i = 0; i<deck.size();i++)
				{
					cout << setw(2) << deck[i].rank;
					switch (deck[i].suit)
					{
					case CLUB:
						printUnicode(club);
						break;
					case DIAMOND:
						printUnicode(diamond);
						break;
					case HEART:
						printUnicode(heart);
						break;
					case SPADE:
						printUnicode(spade);
						break;
					default:
						break;
					}
					cout << "  ";
					if ((i+1)%13 == 0)
						cout << "\n";

				}
				cout << "\n";
				cout << "1 - shuffle | 2 - reorder | 3 - exit \t";
				do
				{
					menu = _getch();
					if (isdigit(menu)) {
						_putch(menu);
					}
				
				} while (!isdigit(menu));
				cout << "\n\n";
				switch (menu) {
					case '1':
						shuffle(deck.begin(),deck.end(),shuffleEn);			
						break;
					case '2':
						sort(deck.begin(), deck.end(), suitSort());
						for(int i=0; i<4;i++)
						{
							sort(deck.begin()+(i*13), deck.begin()+((i+1)*13), rankSort());
						}						
						break;
					case '3':
						cont = false;
						break;
					default:
						break;
				}
			} while (cont == true);

			cont = false;
			clearScreen();
			break;
	
		default:
			break;


		}





	} while (menu != '0');

#pragma endregion

	programEnd = steadyClock.now();

	cout << "Program Ended...Duration: " << steadySecTimeStamp(programStart,programEnd);
	
	cout << "\n\nPress ANYKEY to exit";
	temp = _getch();

    return 0;
}

