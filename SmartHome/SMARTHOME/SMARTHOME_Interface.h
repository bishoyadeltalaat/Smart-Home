#ifndef SMARTHOME_SMARTHOME_INTERFACE_H_
#define SMARTHOME_SMARTHOME_INTERFACE_H_

#define USERNAME_SIZE 16
#define PASSWORD_SIZE 4
#define MAX_USERS 10

// Structure to hold user information
typedef struct {
	char username[USERNAME_SIZE + 1];  // Increased size to accommodate null-terminator
	char password[PASSWORD_SIZE + 1];  // Increased size to accommodate null-terminator
} User;

// Buffer to store user input
char enteredUsername[USERNAME_SIZE + 1];
char enteredPassword[PASSWORD_SIZE + 1];

int VerifyCredentials(const char* enteredUsername, const char* enteredPassword, const User* user);
int Smart_Home(u8 local_u8ReceivedData);
void Display_Menu(void);
void Display_WelcomeMessage(void);
void WrongInput(void);
int BuzzerOn(u8 Frequecy);
void BuzzerOff(void);


#endif /* SMARTHOME_SMARTHOME_INTERFACE_H_ */
