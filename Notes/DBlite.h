#pragma once

#include "sqlite3.h"

#include <iostream>
#include <charconv>
#include <string>
#include <limits>

class DBlite
{
private: sqlite3* db;
	   char* err;
	   int rc;
	   std::string sql;
	   sqlite3_stmt* stmt;
	   static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
		   for (int i = 0; i < argc; i++) {
			   printf("~~~%s = %s\n", azColName[i], argv[i] ? argv[i] : "Empty");
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
		sql = ("CREATE TABLE IF NOT EXISTS NOTES(ID INTEGER PRIMARY KEY, TITLE TEXT NOT NULL, CONTENT TEXT NULL);");
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Insert row
#if 0
	void insertData(int id, std::string title, std::string content) {
		sql = "INSERT INTO NOTES ('ID','TITLE', 'CONTENT') VALUES ('";
		sql += std::to_string(id);
		sql += "', '";
		sql += title;
		sql += "', '";
		sql += content;
		sql += "');";
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}
#endif

	void insertData(std::string title, std::string content) {
		sql = "INSERT INTO NOTES ('TITLE', 'CONTENT') VALUES ('";
		sql += title;
		sql += "', '";
		sql += content;
		sql += "');";
		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
		std::cout << "~Note created~\n";
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
		sql += "'; UPDATE 'NOTES' SET ID = (ID - 1) WHERE ID > '";
		sql += std::to_string(id);
		sql += "';";


		rc = sqlite3_exec(db, sql.c_str(), callback, 0, &err);
	}


	//Close connection

	void closeDB() {
		sqlite3_close(db);
	}
};

