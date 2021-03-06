#include <YSI_Coding\y_hooks>

hook OnMySQLConnected() {
    static const query[] = "\
    CREATE TABLE IF NOT EXISTS testers \
    ( \
    	u_id INT(11) NOT NULL, \
    	tester_level TINYINT(2) NOT NULL DEFAULT 0, \
    	PRIMARY KEY (u_id), \
    	FOREIGN KEY (u_id) REFERENCES players(u_id) \
        ON DELETE CASCADE \
        ON UPDATE CASCADE \
    )";
    mysql_tquery(MySQL_GetHandle(), query);
    Logger_Log("setting up 'admins' table...");
    return 1;
}