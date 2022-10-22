#include <iostream>
#include <string>
#include <vector> // self explanatory
#include <fstream>
#include <random> // for getRandom();
#include <windows.h> // for sleep();

using std::cout; using std::cin; using std::string; using std::vector; using std::getline; using std::ws; using std::to_string; using std::system; using std::ofstream; using std::ifstream;

// ------- \\

// written by chapel1337
// started on 10/21/2022
// this took me awhile to make, and i'm completely sapped of my energy
// i'll be falling asleep quickly tonight
// currently 11pm !!!!

// i'll probably add a flash card saving feature tomorrow, as it was planned (look at the commented code)
// 678 lines
// i believe this is my longest project
// my largest and most ambitious project yet™️

// weird executable icon glitch has occured
// the icon in file explorer is different from the one used by the application
// no idea how this happened, it might've been caused by the overwriting of the icon?
// a silly indeed

// finished on 10/22/2022
// 963 lines!!!!!!
// my longest and most ambitious project yet™️
// this is beginning to get hard to read, even for me
// added save feature, i'm surprised it didn't error too much
// vectors really saved my sanity on this one
// not much else to say about this, i might actually use this

// ------- \\

ofstream output{};

vector<string> questions{ "what does ben say?", "what does ben not say?", "is ben a fictional character?", "is ben real?"}; // placeholder, ben being the dog from the hit game talking ben
vector<string> answers{ "yes", "no", "no", "yes" };

string colorsList[]{ "black", "blue", "green", "aqua", "red", "purple", "yellow", "white", "gray", "light blue", "light green", "light aqua", "light red", "light purple", "light yellow", "bright white" };

int cardsAmount{ 10 }; // 10 being the preset value
int cardsLeft{ cardsAmount }; // set to 1 so it doesn't automatically die
int lastCard{};

int correctCards{};
int incorrectCards{};

// ------- \\

void returnTo(string returnFunction);

void clear()
{
	system("cls");
}

void title(string title)
{
	system(("title " + title).c_str());
}

void title(string title, int time)
{
	system(("title " + title + " " + to_string(time)).c_str());
}

void sleep(auto time)
{
	Sleep(time * 1000);
}

void invalidInput(string message, string returnFunction)
{
	clear();
	title("flash cards - invalid input");

	cout << message << '\n';

	sleep(2);
	returnTo(returnFunction);
}

void pause()
{
	cout << "press enter to continue...\n";

	cin.get();
	cin.ignore();
}

int getRandom(int minimum, int maximum)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution random{ minimum, maximum };

	return random(mt);
}

// ------- \\

void returnTo(string returnFunction);

void listFlashCards()
{
	// unsigned int because the compiler is giving annoying warning
	for (unsigned int i{ 0 }; i < questions.size(); ++i)
	{
		cout << "question: " << questions.at(i) << '\n';
		// cout << "answer: " << answers.at(i) << "\n\n";
	}

	cout << '\n';
}

// ------- \\

void displayResults()
{
	clear();
	title("flash cards - results");

	int totalScore{ incorrectCards - cardsAmount };

	if (totalScore < 0)
	{
		totalScore = cardsAmount - incorrectCards;
	}

	cout << "correct answers: " << correctCards << '\n';
	cout << "incorrect answers: " << incorrectCards << '\n';
	cout << "total score: " << totalScore << '\\' << cardsAmount << "\n\n";

	cardsLeft = cardsAmount;

	pause();
	returnTo("menu");
}

void CIHandler(string& response, bool comingFrom, string& input, string& answer);

void correct(string& input, string& answer)
{
	clear();
	title("flash cards - correct!");

	string response{};

	correctCards++;

	cout << "cards left: " << cardsLeft << "\n\n";

	cout << "correct!\n\n";

	cout << "your answer: " << input << '\n';
	cout << "correct answer: " << answer << "\n\n";

	cout << "continue?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	CIHandler(response, true, input, answer);
}

void incorrect(string& input, string& answer)
{
	clear();
	title("flash cards - incorrect!");

	string response{};

	incorrectCards++;

	cout << "cards left: " << cardsLeft << "\n\n";

	cout << "incorrect!\n\n";

	cout << "your answer: " << input << '\n';
	cout << "correct answer: " << answer << "\n\n";

	cout << "continue?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	CIHandler(response, false, input, answer);
}

void CIHandler(string& response, bool comingFrom, string& input, string& answer) // true = correct, false = incorrect
{
	if (response == "yes" || response == "y")
	{
		returnTo("displayRandomCard");
	}
	else if (response == "no" || response == "n")
	{
		cardsLeft = cardsAmount;
		returnTo("menu");
	}
	else
	{
		clear();

		// invalid input doesn't support arguments
		cout << "invalid input: please specify yes or no\n";

		sleep(2);
		if (comingFrom)
		{
			correct(input, answer);
		}
		else
		{
			incorrect(input, answer);
		}
	}
}

// ------- \\

// unfamiliar with algoritms, and this is the easiest way to convert a lowercase string to uppercase
// https://stackoverflow.com/questions/735204/convert-a-string-in-c-to-upper-case

string toUpperCase(string str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);

	return str;
}

void displayRandomCard()
{
	clear();
	title("flash cards");

	int random{ getRandom(1, questions.size() - 1) };

	string question{ questions.at(random) };
	string answer{ answers.at(random) };
	string upperAnswer{ toUpperCase(answer) };

	string input{};

	if (cardsLeft <= 0)
	{
		displayResults();
	}
	else
	{
		if (random == lastCard)
		{
			displayRandomCard();
		}
		else
		{
			cout << question << "\n\n";

			cout << "> ";
			getline(cin >> ws, input);

			lastCard = random;
			cardsLeft--;

			int correctCharacters{};
			for (unsigned int i{ 0 }; i < input.length(); ++i)
			{
				if (input[i] == answer[i] || input[i] == upperAnswer[i])
				{
					correctCharacters++;
				}
			}

			if (correctCharacters == answer.length())
			{
				correct(input, answer);
			}
			else
			{
				incorrect(input, answer);
			}
		}
	}
}

// ------- \\

void saveFlashCards()
{
	clear();
	title("flash cards - save flash cards");

	string response{};

	cout << "are you sure you want to save?\n";
	cout << "note: this will overrite your current save\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		output.open("save.txt");

		for (unsigned int i{ 0 }; i < questions.size(); ++i)
		{
			// ! is for identifying questions, @ is for identifying answers
			output << '!' << questions.at(i) << '\n';
			output << '@' << answers.at(i) << '\n';
		}

		output.close();

		cout << "saved flash cards to save.txt\n\n";
		cout << "> ";

		sleep(2);
		returnTo("flashCardMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("saveFlashCardsMenu");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "saveFlashCards");
	}
}

void loadFlashCards()
{
	clear();
	title("flash cards - load flash card save");

	string response{};

	cout << "are you sure you want to load a save?\n";
	cout << "note: this will wipe your current pile\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		ifstream input{ "save.txt" };
		string line{};

		questions.clear();
		answers.clear();

		while (getline(input, line))
		{
			if (line[0] == '!')
			{
				line = line.substr(1, line.length());
				questions.push_back(line);
			}
			else if (line[0] == '@')
			{
				line = line.substr(1, line.length());
				answers.push_back(line);
			}
		}

		clear();

		cout << "successfully loaded save file\n\n";
		cout << "> ";

		sleep(2);
		returnTo("saveFlashCardsMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("saveFlashCardsMenu");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "loadFlashCards");
	}
}

void wipeFlashCardsSave()
{
	clear();
	title("flash cards - wipe flash cards save");

	string response{};

	cout << "are you sure you want to wipe the current save?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		output.open("save.txt");
		output.close();

		clear();

		cout << "successfully cleared save file\n\n";
		cout << "> ";

		sleep(2);
		returnTo("saveFlashCardsMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("saveFlashCardsMenu");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "wipeFlashCardsSave");
	}
}

void flashCardsSaveHelp()
{
	clear();
	title("flash cards - flash cards save help");

	cout << "saving your pile will save it's contents to a text file, which can be opened and edited\n";
	cout << "the save file is always saved with the word save, if it's renamed, you will not be able to load it\n";
	cout << "to load a save file, you have to place it in the same directory as the executable\n\n";

	cout << "you can create your own questions and answers inside the text file, then load it\n";
	cout << "if you are editing the text file, the ! symbol before a line is a question\n";
	cout << "and the @ symbol before a line is the answer to the question on the previous line\n\n";

	cout << "wiping a save file deletes all of the questions and answers in the currently loaded save file\n";
	cout << "everything else is self explanatory\n";
	cout << "have fun!!\n\n";

	pause();
	returnTo("saveFlashCardsMenu");
}

// ------- \\

void saveFlashCardsMenu()
{
	clear();
	title("flash cards - save flash cards menu");

	char response{};

	cout << "save flash cards menu\n\n";

	cout << "1. save flash cards\n";
	cout << "2. load flash cards save\n";
	cout << "3. wipe flash cards save\n";
	cout << "4. help\n";
	cout << "5. back\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		saveFlashCards();
		break;

	case '2':
		loadFlashCards();
		break;

	case '3':
		wipeFlashCardsSave();
		break;

	case '4':
		flashCardsSaveHelp();
		break;

	case '5':
		returnTo("flashCardMenu");
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, 3, 4, or 5", "saveFlashCardsMenu");
	}
}

// -------  \\

void addFlashCard()
{
	clear();
	title("flash cards - add flash card");

	string question{};
	string answer{};
	string response{};

	listFlashCards();

	cout << "card question: \n\n";

	cout << "> ";
	getline(cin >> ws, question);

	clear();

	for (unsigned int i{ 0 }; i < questions.size(); ++i)
	{
		if (question == questions.at(i))
		{
			cout << "this flash card already exists\n\n";
			cout << "> ";

			sleep(2);
			returnTo("flashCardMenu");
		}
	}

	listFlashCards();

	cout << "card answer: \n\n";

	cout << "> ";
	getline(cin >> ws, answer);

	clear();

	cout << "question: " << question << '\n';
	cout << "answer: " << answer << "\n\n";

	cout << "is this what you want?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		questions.push_back(question);
		answers.push_back(answer);

		clear();

		cout << "added flash card\n\n";
		cout << "> ";

		sleep(2);
		returnTo("flashCardMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("flashCardMenu");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "addFlashCard");
	}
}

void removeFlashCard()
{
	clear();
	title("flash cards - remove flash card");

	string question{};
	string removedQuestion{};

	listFlashCards();

	cout << "input flash card question: \n\n";

	cout << "> ";
	getline(cin >> ws, question);

	clear();

	bool questionRemoved{ false };
	for (unsigned int i{ 0 }; i < questions.size(); ++i)
	{
		if (question == questions.at(i))
		{
			questions.erase(questions.begin() + i);
			answers.erase(answers.begin() + i);

			removedQuestion = questions.at(i);
			questionRemoved = true;

			break;
		}
	}

	if (questionRemoved == false)
	{
		cout << "this question does not exist\n\n";
		cout << "> ";

		sleep(2);
		returnTo("flashCardMenu");
	}

	cout << "removed question: " << removedQuestion << "\n\n";
	cout << "> ";

	sleep(2);
	returnTo("flashCardMenu");
}

void removeAllCards()
{
	clear();
	title("flash cards - remove all cards");

	string response{};

	cout << "are you sure you want to remove all of your flash cards?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		questions.clear();
		answers.clear();

		clear();

		cout << "removed all flash cards\n\n";
		cout << "> ";

		sleep(2);
		returnTo("flashCardMenu");
	}
	else if (response == "no" || response == "n")
	{
		returnTo("flashCardMenu");
	}
}

void changeFlashCardAmount()
{
	clear();
	title("flash cards - change flash card amount");

	cout << "input new amount: \n\n";

	cout << "> ";
	cin >> cardsAmount;

	cardsLeft = cardsAmount;

	clear();

	cout << "changed flash cards amount to " << cardsAmount << "\n\n";
	cout << "> ";

	sleep(2);
	returnTo("flashCardMenu");
}


// ------- \\

void flashCardMenu()
{
	clear();
	title("flash cards - flash card menu");

	char response{};

	cout << "flash card menu\n\n";

	cout << "1. save card menu\n";
	cout << "2. add a card\n";
	cout << "3. remove a card\n";
	cout << "4. remove all cards\n";
	cout << "5. change card amount\n";
	cout << "6. back\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		saveFlashCardsMenu();
		break;

	case '2':
		addFlashCard();
		break;

	case '3':
		removeFlashCard();
		break;

	case '4':
		removeAllCards();
		break;

	case '5':
		changeFlashCardAmount();
		break;

	case '6':
		returnTo("menu");
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, 3, 4, or 5", "flashCardMenu");
	}
}

// ------- \\

void changeColor(string textColor, string backgroundColor)
{
	system(("color " + textColor + backgroundColor).c_str());

	clear();

	cout << "changed text color to " << textColor << '\n';
	cout << "changed background color to " << backgroundColor << "\n\n";

	cout << "> ";

	sleep(2);
	returnTo("settings");
}

void listColors()
{
	for (int i{ 0 }; i <= 8; ++i)
	{
		cout << colorsList[i] << " - " << i << '\n';
	}

	char character = 'a';
	for (int i{ 0 }; i <= 7; ++i)
	{
		cout << colorsList[i + 8] << " - " << character << '\n';

		character++;
	}

	cout << '\n';
}

void changeColorMenu()
{
	clear();
	title("flash cards - change color");

	string response{};
	string textColor{ 0 };
	string backgroundColor{ 7 };

	listColors();

	cout << "new text color: \n\n";

	cout << "> ";
	cin >> textColor;

	clear();

	listColors();

	cout << "new background color: \n\n";

	cout << "> ";
	cin >> backgroundColor;

	clear();

	cout << "are you sure you want to change the color?\n\n";

	cout << "> ";
	cin >> response;

	if (response == "yes" || response == "y")
	{
		changeColor(textColor, backgroundColor);
	}
	else if (response == "no" || response == "n")
	{
		returnTo("settings");
	}
	else
	{
		invalidInput("invalid input: please specify yes or no", "settings");
	}
}

// ------- \\

void resetSettings()
{
	clear();
	title("flash cards - reset settings");

	system("color 07");
	cardsAmount = 10;

	cout << "successfully reset the settings\n\n";
	cout << "> ";

	sleep(2);
	returnTo("settings");
}

void settings()
{
	clear();
	title("flash cards - settings");

	char response{};

	cout << "1. change color\n";
	cout << "2. reset settings\n";
	cout << "3. back\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		changeColorMenu();
		break;

	case '2':
		resetSettings();
		break;

	case '3':
		returnTo("menu");
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, or 3", "settings");
	}
}

void quit()
{
	clear();
	title("flash cards - quit");

	for (int i{ 3 }; i >= 1; i--)
	{
		cout << "okay, exiting in " << i;
		title("flash cards - quitting in", i);

		sleep(1);
		clear();
	}

	exit(1);
}

// ------- \\

void menu()
{
	clear();
	title("flash cards - menu");

	char response{};

	cout << "flash cards\n\n";

	cout << "1. start\n";
	cout << "2. flash card menu\n";
	cout << "3. settings\n";
	cout << "4. quit\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		displayRandomCard();
		break;

	case '2':
		flashCardMenu();
		break;

	case '3':
		settings();
		break;

	case '4':
		quit();
		break;

	default:
		invalidInput("invalid input: please specify 1, 2, 3, or 4", "menu");
		break;
	}
}

void returnTo(string returnFunction)
{
	if (returnFunction == "displayRandomCard")
	{
		displayRandomCard();
	}
	else if (returnFunction == "menu")
	{
		menu();
	}
	else if (returnFunction == "settings")
	{
		settings();
	}

	else if (returnFunction == "flashCardMenu")
	{
		flashCardMenu();
	}
	else if (returnFunction == "saveFlashCardsMenu")
	{
		saveFlashCardsMenu();
	}

	else if (returnFunction == "addFlashCard")
	{
		addFlashCard();
	}
	else if (returnFunction == "removeFlashCard")
	{
		removeFlashCard();
	}

	else if (returnFunction == "loadFlashCards")
	{
		loadFlashCards();
	}
	else if (returnFunction == "saveFlashCards")
	{
		saveFlashCards();
	}
	else if (returnFunction == "wipeFlashCardsSave")
	{
		wipeFlashCardsSave();
	}
}

int main()
{
	title("flash cards - credits");

	cout << "written by chapel1337\n";
	cout << "started on 10/21/2022, finished on 10/22/2022\n";

	sleep(2);
	menu();
}

// ------- \\
