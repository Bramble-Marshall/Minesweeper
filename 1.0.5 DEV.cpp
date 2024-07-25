#include <stdio.h>
#include <utility>
#include <ctime>
#include <string>
#include <conio.h>
#include <fstream>
#include <windows.h>

using std::string;
using std::pair;

string lin = "----------------------------------------------------------------------------------------------------------------";
string item1[5] = {"Start", "Settings", "History", "About", "Exit"};
string itemSet[3] = {"Accounts", "Difficulty", "ClearData"};
string username[10], pasw[10];

int usernum = 0, totuser, diflen = 8, difdie = 20;  // difdie holds max
int HistTot = 0;

int HistArr[10086];
int lyh[105][105], choc[105][105];

void menu();

void wel() {
    printf(" _    _      _                            _          __  __                                   \n");
    printf("| |  | |    | |                          | |        |  \\/  |                                  \n");
    printf("| |  | | ___| | ___ ___  _ __ ___   ___  | |_ ___   | \\  / | __ _ _ __   __ _  __ _  ___ _ __ \n");
    printf("| |  | |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|\n");
    printf("| |__| |  __/ | (_| (_) | | | | | |  __/ | || (_) | | |  | | (_| | | | | (_| | (_| |  __/ |   \n");
    printf(" \\____/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/  |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|   \n");
    printf("                                                                              __/ |          \n");
    printf("                                                                             |___/           \n");
}

void saveData() {
    std::ofstream file("Data.txt");
    if (file.is_open()) {
        file << usernum << "\n";
        for (int i = 1; i <= usernum; i++) {
            file << username[i] << " " << pasw[i] << "\n";
        }
        file << HistTot << "\n";
        for (int i = 1; i <= HistTot; i++) {
            file << HistArr[i] << "\n";
        }
        file.close();
    }
}

void loadData() {
    std::ifstream file("Data.txt");
    if (file.is_open()) {
        file >> usernum;
        for (int i = 1; i <= usernum; i++) {
            file >> username[i] >> pasw[i];
        }
        file >> HistTot;
        for (int i = 1; i <= HistTot; i++) {
            file >> HistArr[i];
        }
        file.close();
    } else {
        printf("No data file found. Starting with no user data.\n");
    }
}

void login() {
    printf("User Name >>");
    char input[100];
    scanf("%s", input);
    for (int i = 1; i <= usernum; i++) {
        if (strncmp(input, username[i].c_str(), strlen(input)) == 0) {
            printf("Password: >>");
            char tmp;
            string password;
            while ((tmp = _getch()) != '\r') {
                if (tmp == '\b') printf("\b \b");
                else {
                    password += tmp;
                    putchar('*');
                }
            } if (password == pasw[i]) {
                printf("\nLogin successful!\n");
                Sleep(1000);
                system("cls");
                return;
            } else {
                printf("\nIncorrect password. Please try again.\n");
                return login();
            }
        }
    }
    // If no matching username is found, create a new user
    username[++usernum] = string(input);
    printf("Password: >>");
    char tmp;
    while ((tmp = _getch()) != '\r') {
        if (tmp == '\b') printf("\b \b");
        else {
            pasw[usernum] += tmp;
            putchar('*');
        }
    }
    totuser = usernum;
    printf("\nCreated an account \"%s\" successfully", username[totuser].c_str());
    Sleep(1000);
    system("cls");
    saveData();
}

void SetAccount() {
    int choice = 0;
    while (true) {
        system("cls");
        printf("Accounts Management\n");
        printf("1. View all accounts\n");
        printf("2. Add a new account\n");
        printf("3. Delete an account\n");
        printf("4. Back to settings\n");
        printf("Choose an option: ");
        choice = _getch() - '0';
        if (choice == 4) break;

        char newUser[100];
        string newPassword;
        char tmp;
        switch (choice) {
        case 1:
            system("cls");
            printf("Existing accounts:\n");
            for (int i = 1; i <= usernum; i++) {
                printf("%d. Username: %s;\n", i, username[i].c_str());
            }
            printf("Press any key to continue...");
            _getch();
            break;

        case 2:
            system("cls");
            printf("Enter new username: ");
            scanf("%s", newUser);
            username[++usernum] = string(newUser);
            printf("Enter new password: ");
            while ((tmp = _getch()) != '\r') {
                if (tmp == '\b') printf("\b \b");
                else {
                    newPassword += tmp;
                    putchar('*');
                }
            }
            pasw[usernum] = newPassword;
            printf("\nNew account created successfully.\n");
            printf("Press any key to continue...");
            _getch();
            saveData();
            break;

        case 3:
            system("cls");
            printf("Enter username to delete: ");
            char delUser[100];
            scanf("%s", delUser);
            for (int i = 1; i <= usernum; i++) {
                if (username[i] == string(delUser)) {
                    for (int j = i; j < usernum; j++) {
                        username[j] = username[j + 1];
                        pasw[j] = pasw[j + 1];
                    }
                    usernum--;
                    printf("Account deleted successfully.\n");
                    saveData();
                    break;
                }
            }
            printf("Press any key to continue...");
            _getch();
            break;

        default:
            printf("Invalid option. Please try again.\n");
            _getch();
            break;
        }
    }
    system("cls");
    menu();
}

void startFun() {
    memset(lyh, 0, sizeof(lyh));
    memset(choc, -1, sizeof(choc));
    int tmp = 0,  // The number of lyh
        blocktmp = 0;  // The number of opened block
    for (int i = 1; i <= diflen; i++)
        for (int j = 1; j <= diflen; j++)
            if (tmp >= difdie)
                i = diflen + 1,
                j = diflen + 1;
            else lyh[i][j] = rand() % 2, tmp++;
    bool lif = true;
    pair<int, int> ctot;
    ctot.first = 1;
    ctot.second = 1;
    int len2 = diflen * diflen;  // The number of all block
    while (lif && blocktmp + tmp < len2) {
        system("cls");
        for (int i = 1; i <= diflen; i++) {
            for (int j = 1; j <= diflen; j++)
                putchar(choc[i][j] != -1 ? '0' + choc[i][j] : (ctot.first == i && ctot.second == j ? '_' : '#'));
            putchar('\n');
        } char tmp1 = _getch();
        if (tmp == 0 || tmp == (char)0xe0)
            tmp1 = _getch();

        int itmp1, itmp2;
        switch (tmp1) {
        case 72:
            if (ctot.first == 1) ctot.first = diflen + 1;
            ctot.first--;
            break;

        case 80:
            if (ctot.first == diflen) ctot.first = 0;
            ctot.first++;
            break;

        case 75:
            if (ctot.second == 1) ctot.second = diflen + 1;
            ctot.second--;
            break;

        case 77:
            if (ctot.second == diflen) ctot.second = 0;
            ctot.second++;
            break;

        case 13:
            itmp1 = ctot.first, itmp2 = ctot.second;
            if (lyh[itmp1][itmp2] == 1) lif = false;
            else {
                int ctmp = 0;
                for (int i = -1; i < 2; i++)
                    for (int j = -1; j < 2; j++)
                        if (i != 0 && j != 0) ctmp += lyh[itmp1 + i][itmp2 + j];
                choc[itmp1][itmp2] = ctmp;
            }
        } if (!lif) printf("\n\nYou lose\n");
        else if (blocktmp + tmp >= len2)
            printf("You win\n");
    } Sleep(1000);
    menu();
}

void changeDifficulty() {
    system("cls");
    printf("Current Difficulty: %d\n", difdie);
    printf("Enter new difficulty level (1-50): ");
    scanf("%d", &difdie);
    if (difdie < 1) difdie = 1;
    if (difdie > 50) difdie = 50;
    system("cls");
    printf("Difficulty changed to %d\n", difdie);
    Sleep(1000);
    system("cls");
    menu();
}

void settings() {
    system("cls");
    int highlight = 0;
    while (true) {
        system("cls");
        printf("%s\n", lin.c_str());
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                printf("\t> %s <\n", itemSet[i].c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                printf("\t  %s  \n", itemSet[i].c_str());
            }
        }
        printf("%s\n", lin.c_str());

        switch (_getch()) {
        case 72:
            highlight--;
            if (highlight < 0) highlight = 2;
            break;
        case 80:
            highlight++;
            if (highlight > 2) highlight = 0;
            break;
        case 13:
            switch (highlight) {
            case 0:
                SetAccount();
                break;
            case 1:
                changeDifficulty();
                break;
            case 2:
                system("cls");
                printf("Data cleared successfully.\n");
                usernum = 0;
                HistTot = 0;
                saveData();
                Sleep(1000);
                system("cls");
                menu();
                break;
            }
            break;
        default:
            break;
        }
    }
}

void showHistory() {
    system("cls");
    printf("Game History:\n");
    if (HistTot == 0) {
        printf("No history available.\n");
    } else {
        for (int i = 1; i <= HistTot; i++) {
            printf("Game %d: %s\n", i, HistArr[i] ? "Win" : "Loss");
        }
    }
    printf("Press any key to continue...");
    _getch();
    system("cls");
    menu();
}

void about() {
    system("cls");
    printf("About the Game:\n");
    printf("MineSweeper Game\n");
    printf("Developed by: Bramble_Marshall\n");
    printf("Github: https://github.com/Bramble-Marshall/Minesweeper\n");
    printf("Version: 1.1.0 DEV\n");
    printf("Enjoy the game!\n");
    printf("Press any key to continue...");
    _getch();
    system("cls");
    menu();
}

void menu() {
    system("cls");
    int highlight = 0;
    while (true) {
        system("cls");
        printf("%s\n", lin.c_str());
        for (int i = 0; i < 5; i++) {
            if (i == highlight) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                printf("\t> %s <\n", item1[i].c_str());
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                printf("\t  %s  \n", item1[i].c_str());
            }
        }
        printf("%s\n", lin.c_str());

        switch (_getch()) {
        case 72:
            highlight--;
            if (highlight < 0) highlight = 4;
            break;
        case 80:
            highlight++;
            if (highlight > 4) highlight = 0;
            break;
        case 13:
            switch (highlight) {
            case 0:
                startFun();
                break;
            case 1:
                settings();
                break;
            case 2:
                showHistory();
                break;
            case 3:
                about();
                break;
            case 4:
                printf("Goodbye!\n");
                Sleep(1000);
                exit(0);
                break;
            }
            break;
        default:
            break;
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    loadData();
    wel();
    login();
    menu();
    return 0;
}
