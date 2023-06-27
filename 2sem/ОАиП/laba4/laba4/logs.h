void getString(char* string);
struct tm* getTime(void);
void createLog(FILE** fp);
char* fileMark(void);
void createMessage(FILE** fp, char* message);
void createAddMessage(FILE** fp, char* message, char* object);