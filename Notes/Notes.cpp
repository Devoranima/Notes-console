#include "sqlite3.h"

#include <iostream>
#include <charconv>
#include <string>
#include <limits>

#include "DBlite.h"
#include "app.h"


//Basic classes for notes
#if 0

class noteTitle {
protected: std::string text;
public: 
	noteTitle() {
		text = "noteName";
	}
	void titleChange(std::string s) {
		text = s;
	}
	
	std::string getString() {
		return text;
	}
};

class noteContent {
protected: std::string text;
public:
	noteContent() {
		text = "s";
	}
	void contentChange(std::string s) {
		text = s;
	}

	std::string getString() {
		return text;
	}
};

class note {
protected: noteTitle title;
		 noteContent content;
public:
	~note() { std::cout << "\n\n~N0te destroyed successfully~\n\n";}
	void showNote() {
		std::string tempTitle, tempContent;
		tempTitle = title.getString();
		tempContent = content.getString();
		std::cout << "\n\n" <<  tempTitle << "\n"
			<<std::string(tempTitle.length(), '*')
			<<"\n\n" << tempContent;
	}

	void changeTitle(std::string s){
		title.titleChange(s);
	}

	void changeContent(std::string s) {
		content.contentChange(s);
	}

};

int new_note() {
	note temp;
	std::string tempTitle, tempContent;
	
	std::cout << "Enter note title: ";
	getline(std::cin, tempTitle);
	temp.changeTitle(tempTitle);
	std::cout << "Enter note content: ";
	getline(std::cin, tempContent);
	temp.changeContent(tempContent);
	temp.showNote();
	return 0;
}

#endif


//Crutch class
#if 0
class justOneMethod {
public:
	void error() {
		std::cout << "\n!!! Wrong command, dumbass, try again !!!\n\n";
	}
};
#endif




int main(int argc, char** argv) {

//Drop the table
#if 0
	sqlite3* db;
	sqlite3_open("notesDB.dblite", &db);
	std::string sql = "DROP TABLE 'NOTES';";
	sqlite3_exec(db, sql.c_str(), 0, 0, 0);
#endif

	app();
}

//Testing block
#if 0
int main() {

	// Save any error messages
	char* err = 0;

	// Save the result of opening the file
	int rc;

	// Save any SQL
	std::string sql;

	// открываем соединение
	if (sqlite3_open("notesDB.dblite", &db)) {
		fprintf(stderr, "Ошибка открытия/создания БД: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	sql = "CREATE TABLE IF NOT EXISTS NOTES(ID INT NOT NULL PRIMARY KEY, TITLE TEXT NOT NULL, CONTENT TEXT NULL);";

	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);

	

	sql = "INSERT INTO NOTES ('ID', 'TITLE', 'CONTENT') VALUES ('1','ttle', 'cntent');";

	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);

	insertNote(db, err, 4, "suka", "blyat");


	sql = "SELECT * FROM 'NOTES';";

	rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	// закрываем соединение
	sqlite3_close(db);
	return 0;



	

}


#endif