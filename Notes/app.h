#pragma once


#include "sqlite3.h"

#include <iostream>
#include <charconv>
#include <string>
#include <limits>
#include "DBlite.h"

class app
{
private:
	DBlite db;
public:
	app() {
		std::cout << "@- Starting app...\n\n";


		DBlite db;

		db.createTable();

		std::cout << R"(
                      :::!~!!!!!:.
                  .xUHWH!! !!?M88WHX:.
                .X*#M@$!!  !X!M$$$$$$WWx:.
               :!!!!!!?H! :!$!$$$$$$$$$$8X:
              !!~  ~:~!! :~!$!#$$$$$$$$$$8X:
             :!~::!H!<   ~.U$X!?R$$$$$$$$MM!
             ~!~!!!!~~ .:XW$$$U!!?$$$$$$RMM!
               !:~~~ .:!M"T#$$$$WX??#MRRMMM!
               ~?WuxiW*`   `"#$$$$8!!!!??!!!
             :X- M$$$$       `"T#$T~!8$WUXU~
            :%`  ~#$$$m:        ~!~ ?$$$$$$
          :!`.-   ~T$$$$8xx.  .xWW- ~""##*"
.....   -~~:<` !    ~?T#$$@@W@*?$$      /`
W$@@M!!! .!~~ !!     .:XUW$W!~ `"~:    :
#"~~`.:x%`!!  !H:   !WM$$$$Ti.: .!WUn+!`
:::~:!!`:X~ .: ?H.!u "$$$B$$$!W:U!T$$M~
.~~   :X@!.-~   ?@WTWo("*$$$W$TH$! `                  What the actual fuck are you talking about, shizo?
Wi.~!X$?!-~    : ?$$$B$Wu("**$RM!
$R@i.~~ !     :   ~$$$$$B$$en:``
?MXT@Wx.~    :     ~"##*$$$$M~ 
)" << "\n";

		int init_state = 1;
		while (init_state) init_state = appMainMenu();

		db.closeDB();
	}

	int appMainMenu() {

		int choice;
		int state = 1;

		std::cout << "@- Da fuc you want brah? \n\t 1.Create new note \n\t 2.Show all notes \n\n\n\t-1.Exit\n\n";
		std::cin >> choice;
		std::cout << "\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1: {
			noteAdd();
			return 1;
		}
		case 2: {
			while (state) state = listOfNotes();
			return 1;
		}
		case -1: {
			std::cout << "@- And never come back!\n";
			return 0;
			break;
		}
		default: {
			//std::string ss;
			//std::getline(std::cin, ss);

			std::cout << "\n!!! Wrong command, dumbass, try again !!!\n\n";
			return 1;
		}
		}
		return 0;
	}

	int listOfNotes() {

		std::cout << "\n@- All notes for now:\n\n\n";

		db.showList();

		int choice = 0;

		std::cout << "@- What do you want now? \n\t 1.Select note\n\n\n\t-1.Exit to main menu\n\n";

		std::cin >> choice;
		std::cout << "\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1: {
			std::cout << "@- Enter id of the note = ";

			int id;
			std::cin >> id;
			std::cout << "\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			noteSelect(id);
			return 1;
			break;
		}
		case -1: {
			return 0;
			break;
		}
		default: {

			std::cout << "\n!!! Wrong command, dumbass, try again !!!\n\n";
			return 1;
		}
		}
		return 0;
	}

	int noteSelect(int id) {
		db.showRow(id);

#if 1
		int choice;
		std::cout << "@- We have the note, now what? \n\t 1.Edit note\n\t 2.Delete note\n\n\n\t-1.Go back\n\n";

		std::cin >> choice;
		std::cout << "\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1: {
			noteUpdate(id);
			return 1;
			break;
		}
		case 2: {

			int state = 1;

			while (state) state = noteDelete(id);

			return 0;
			break;
		}
		case -1: {
			return 0;
			break;
		}
		default: {
			//std::string ss;
			//std::getline(std::cin, ss);

			std::cout << "\n!!! Wrong command, dumbass, try again !!!\n\n";
			return 1;
		}
		}
#endif
		return 0;
	}

	//Method to add note

	int noteAdd() {
		std::string title, content;
		/*
		int id;
		std::cout << "Enter unique id: ";
		std::cin >> id;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');*/
		std::cout << "@- Enter title: ";
		getline(std::cin, title);
		std::cout << "@- Enter content: ";
		getline(std::cin, content);
		std::cout << "\n";
		db.insertData(title, content);
		std::cout << "\n";
		return 0;
	}


	//Method to delete note

	int noteDelete(int id) {
		std::cout << "@- Bro, you sure? (y/n)\n\n";

		char choice;
		std::cin >> choice;
		std::cout << "\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		switch (choice) {
		case 'y': {
			std::cout << "@- Chill, I got you madman\n";

			db.deleteNote(id);

			std::cout << "@- ~Note deleted successfully~\n";

			break;
		}
		case 'n': {
			break;
		}
		default: {
			//std::string ss;
			//std::getline(std::cin, ss);

			std::cout << "\n!!! Wrong command, dumbass, try again !!!\n\n";
			return 1;
		}
		}
		return 0;
	}


	//Method to edit note

	int noteUpdate(int id) {
		std::string title, content;
		std::cout << "@- Enter title: ";
		getline(std::cin, title);
		std::cout << "@- Enter content: ";
		getline(std::cin, content);
		std::cout << "\n";

		db.updateRow(id, title, content);
		return 0;
	}
};

