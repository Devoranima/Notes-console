
#include "sqlite3.h"

#include <iostream>
#include <charconv>
#include <string>
#include <limits>



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


class DBlite {
private: sqlite3* db;
	   char* err;
	   int rc;
	   std::string sql;
	   sqlite3_stmt* stmt;
	   static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
		   for (int i = 0; i < argc; i++) {
			   printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "Empty");
		   }
		   std::cout << "\n"; 
		   return 0;
	   }

	   void checkDBErrors() {
		   if (rc) {
			   std::cout << "DB error: " << sqlite3_errmsg(db) << "\n";

			   closeDB();
		   }
	   }


public:
	DBlite() {
		rc = sqlite3_open("notesDB.dblite", &db);

		checkDBErrors();
	}

	void createTable() {
		sql = ("CREATE TABLE IF NOT EXISTS NOTES(ID INT NOT NULL PRIMARY KEY, TITLE TEXT NOT NULL, CONTENT TEXT NULL);");
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Insert row

	void insertData(int id, std::string title, std::string content) {
		sql = "INSERT INTO NOTES ('ID', 'TITLE', 'CONTENT') VALUES ('";
		sql += std::to_string(id);
		sql += "', '";
		sql += title;
		sql += "', '";
		sql += content;
		sql += "');";
		std::cout << sql << "\n";
		rc=sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Update row

	void updateRow(int id, std::string title, std::string content) {
		sql = "UPDATE NOTES SET TITLE = '";
		sql += title;
		sql += "', CONTENT = '";
		sql += content;
		sql += "' WHERE ID = '";
		sql += std::to_string(id);
		sql += "';";

		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Show methods

	void showTable() {
		sql = "SELECT * FROM 'NOTES';";
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}
	
	void showList() {
		sql = "SELECT ID, TITLE FROM 'NOTES';";
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}

	void showRow(int id) {
		sql = "SELECT * FROM 'NOTES' WHERE ID = '";
		sql += std::to_string(id);
		sql += "';";

		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Delete row

	void deleteNote(int id) {
		sql = "DELETE FROM 'NOTES' WHERE ID = '";
		sql += std::to_string(id);
		sql += "';";

	
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Close connection

	void closeDB() {
		sqlite3_close(db);
	}
};



class app {
private:
	DBlite db;
public:
	app() {
		std::cout << "@- Starting app...\n\n";


		DBlite db;

		db.createTable();

		int init_state = 1;
		while (init_state) init_state = appMainMenu();

		db.closeDB();
	}

	int appMainMenu() {

		int choice;
		int state=1;

		std::cout << "@- Wtf do you want? \n\t 1.Create new note \n\t 2.Show all notes \n\n\n\t-1.Exit\n\n";
		std::cin >> choice;
		std::cout << "\n";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (choice) {
		case 1: {

			break;
			return 1;
		}
		case 2: {
			while(state) state = listOfNotes();
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

			std::cout << "@- Wrong command dumbass, try again\n\n";
			return 1;
		}
		}
		return 0;
	}

	int listOfNotes(){

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

			std::cout << "@- Wrong command dumbass, try again\n\n";
			return 1;
		}
		}
		return 0;
	}

	int noteSelect(int id){
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

			while(state) state = noteDelete(id);
			
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

			std::cout << "@- Wrong command dumbass, try again\n\n";
			return 1;
		}
		}
#endif
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

			std::cout << "@- Wrong command dumbass, try again\n\n";
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




int main(int argc, char** argv) {
	
	app();
}

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