//Values that changes game:
const int Number_Ships = 10;
const int Number_Shots = 10;
const int Size_X = 7;
const int Size_Y = 6;

//Login/Keypad
const std::string A_key = "A";
const std::string B_key = "B";
const std::string C_key = "C";
const std::string D_key = "D";
const std::string E_key = "E";
const std::string F_key = "F";
const std::string G_key = "G";
const std::string H_key = "H";
const std::string I_key = "I";
const std::string J_key = "J";
const std::string K_key = "K";
const std::string L_key = "L";
const std::string M_key = "M";
const std::string N_key = "N";
const std::string O_key = "O";
const std::string P_key = "P";
const std::string filename = "Text.txt";
const std::vector<std::vector<std::string>> keypad
{
    {A_key,B_key,C_key,D_key},
    {E_key,F_key,G_key,H_key},
    {I_key,J_key,K_key,L_key},
    {M_key,N_key,O_key,P_key}
};
int pos_x = 0;
int pos_y = 0;

//battleship
std::string solution_board[Size_X][Size_Y];
std::string board[Size_X][Size_Y];
std::string hit = "H";
std::string miss = "M";
const std::string Ship = "S";
const char letters[26]{ 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','W','X','Y','Z' };
int Ships_Hit = 0;
int Shots_fired = 0;
bool replay = false;




void func_keypad() {
    for (int x = 0; x < keypad.size(); x++) {
        for (int y = 0; y < keypad[x].size(); y++) {
            if (pos_x == x & pos_y == y) {
                std::cout << keypad[x][y] << "*| ";
            }
            else {
                std::cout << keypad[x][y] << " | ";
            }
        };
        std::cout << "\n";
    };

};

void func_navigate_keypad() {
    unsigned char a;
    for (int some_stupid_reason = 0; some_stupid_reason < 2; some_stupid_reason++) {
        a = _getch();
    };

    if (a == 72) { //up
        //std::cout << "UP";
        if (pos_x == 0) {
            pos_x += 3;
        }
        else {
            pos_x--;
        };
    }
    else if (a == 80) { //down
       // std::cout << "Down";
        if (pos_x == 3) {
            pos_x -= 3;
        }
        else {
            pos_x++;
        };
    }
    else if (a == 75) { //left
        //std::cout << "Left";
        if (pos_y == 0) {
            pos_y += 3;
        }
        else {
            pos_y--;
        };
    }
    else if (a == 77) { //right
        //std::cout << "Right";
        if (pos_y == 3) {
            pos_y -= 3;
        }
        else {
            pos_y++;
        };
    };
    system("CLS");
    //std::cout << "posX: " << pos_x << " posY: " << pos_y;
}

void func_create_password()
{
    std::string new_password = "";
    std::cout << "\nPlease create your password\n";
    pos_x = 0;
    pos_y = 0;
    for (int i = 0; i < 9; i++) {
        new_password += keypad[pos_x][pos_y];
        func_keypad();
        func_navigate_keypad();
    };
    std::ofstream Profile;
    Profile.open("Text.txt");
    if (Profile.is_open()) {
        perror("Text.txt");
        Profile << new_password;
        //std::cout << new_password;
        Profile.close();
    }
    else {
        perror("Text.txt");
    };
};

void func_letters() {
    std::cout << "  ";
    for (int i = 0; i < Size_Y; i++) {
        std::cout << letters[i] << " ";
    }
}

//made some changes and don't actually need to input any values to the function if I just switch out the variable that is being used, but I'm lazy
void func_shoot(int Shots) {
    //the x coordinates in the program are what would typically be the y coordinates. Didn't think about it when I made the earlier functions and I'm too lazy to change it.
    //also you ask us to make the input in the form column row, like B3, but isn't that row column?
    std::cout << "\nYou have " << Shots - Shots_fired << " shots left and " << Number_Ships - Ships_Hit << " ships left on the board. Where would you like to shoot?\n";
    int Loc_X;
    char Loc_Y;
    int Loc_Y_num;
    for (int i = 0; i < 1;) {
        std::cin >> Loc_Y >> Loc_X;
        //std::cout << "locX: " << Loc_X << " locY: " << Loc_Y;
        if (Loc_X == 0) {
            std::cout << "Something was off about the coordinates you entered. Please enter a letter, then a number, like A1";
            Loc_X = 0;
            Loc_Y = ' ';
            Loc_Y_num = 0;

        }
        else {
            Loc_X--;
            for (int p = 0; p < 26; p++) {
                if (letters[p] == Loc_Y) {
                    Loc_Y_num = p;
                    p = 26;
                }
            }
            i++;
            if (solution_board[Loc_X][Loc_Y_num] == Ship | solution_board[Loc_X][Loc_Y_num] == hit) {
                board[Loc_X][Loc_Y_num] = hit;
                Ships_Hit++;
            }
            else {
                board[Loc_X][Loc_Y_num] = miss;
            }
            Loc_X = 0;
            Loc_Y = ' ';
            Loc_Y_num = 0;
            Shots_fired++;
        }



    }



}

int func_random_row() {
    //srand(time(0));
    int row = rand() % Size_X;
    return(row);
}

int func_random_column() {
    //srand(time(0));
    int column = rand() % Size_X;
    return(column);
}

void func_solution_board(int num_ships) {

    for (int i = 0; i < Size_X; i++) {

        for (int p = 0; p < Size_Y; p++) {
            solution_board[i][p] = " ";

        }
    }
    int ship_x;
    int ship_y;
    srand(time(0));
    for (int i = 0; i < num_ships; i++) {
        ship_x = func_random_row();
        ship_y = func_random_column();
        if (solution_board[ship_x][ship_y] == Ship) {
            i--;
        }
        solution_board[ship_x][ship_y] = Ship;
    }

}

void func_show_solution() {
    for (int i = 0; i < Size_X; i++) {
        std::cout << i + 1;
        for (int p = 0; p < Size_Y; p++) {
            if (p == Size_Y - 1) {
                std::cout << "|" << solution_board[i][p] << "|";
            }
            else {
                std::cout << "|" << solution_board[i][p];
            }
        }
        std::cout << "\n";
    }
    func_letters();
}

void func_empty_board() {
    //The only BLANK variable I could find was _BLANK, and that creates an @, so i made it blank manually with " ".


    //std::cout << "test";
    for (int i = 0; i < Size_X; i++) {
        //std::cout << "test";
        for (int p = 0; p < Size_Y; p++) {
            board[i][p] = " ";
            //std::cout << board[i][p];// << "test";
        }
    }
    //func_show_board(board);

}

void func_show_board() {
    for (int i = 0; i < Size_X; i++) {
        std::cout << i + 1;
        for (int p = 0; p < Size_Y; p++) {

            if (p == Size_Y - 1) {
                std::cout << "|" << board[i][p] << "|";
            }
            else {
                std::cout << "|" << board[i][p];
            }
        }
        std::cout << "\n";
    }
    func_letters();
}

void func_replay() {
    for (int i = 0; i < 1;) {
        int choice;
        std::string Menu = "\n1. Retry\n"
            "2. Menu\n"
            "3. Quit\n";
        std::cout << Menu;
        std::cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            i++;
            replay = true;
            break;
        case 2:
            system("CLS");
            i++;
            break;
        case 3:

            std::cout << "Exiting the program";
            exit(0);
            break;
        default:
            std::cout << "Number not valid, try again.";
        };
    }
}

void func_play() {
    func_empty_board();
    func_solution_board(Number_Ships);
    for (int i = 0; i < Number_Shots; i++) {
        system("cls");
        func_show_board();
        func_shoot(Number_Shots);
        if (Ships_Hit == Number_Ships) {
            std::cout << "\nCongratulations! You found all the ships!\n";
            Ships_Hit = 0;
            Shots_fired = 0;
            func_replay();

        }
        else if (Shots_fired == Number_Shots) {
            std::cout << "\nYou Failed to find all the ships!\nThis is the solution\n";
            func_show_solution();
            Ships_Hit = 0;
            Shots_fired = 0;
            func_replay();
        }
    }

}

void func_menu()
{
    for (int i = 0; i < 1;) {
        int choice;
        std::string Menu = "\n1. New password\n"
            "2. Battleships\n"
            "3. Quit\n";
        std::cout << Menu;
        std::cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            func_create_password();
            break;
        case 2:
            system("CLS");
            for (int p = 0; p < 1;) {
                func_play();
                if (replay == false) {
                    p++;
                }
                else {
                    replay = false;
                }
            }
            break;
        case 3:
            std::cout << "Exiting the program";
            exit(0);
            break;
        default:
            std::cout << "Number not valid, try again.";

        };
    };

};

void func_login()
{
    std::string password = "";
    std::ifstream Profile;
    Profile.open(filename);
    if (Profile.is_open()) {
        std::getline(Profile, password);
    }
    else {
        Profile.close();
        func_create_password();
        std::ifstream Profile;
        Profile.open(filename);
        if (Profile.is_open()) {
            std::getline(Profile, password);
        }
        else {
            perror("Text.txt");
            std::cout << "\nSomething went wrong, can't create password.";
            return;
        }
        pos_x = 0;
        pos_y = 0;
    }
    std::string Code = "";
    std::cout << "Use the arrow keys to move. You are the star. The password requires nine moves.\n";
    for (int Im_Stupid = 0; Im_Stupid < 1;) {

        for (int i = 0; i < 9; i++) {
            Code += keypad[pos_x][pos_y];
            func_keypad();
            std::cout << "\n";

            func_navigate_keypad();
            //std::cout << "posX: " << pos_x << " posY: " << pos_y;
        };
        //std::cout << "\nEnterd Code: " << Code << "\nCorrect Password: " << password;
        if (Code == password) {
            std::cout << "Correct password!\n";
            pos_x = 0;
            pos_y = 0;
            Im_Stupid = 1;
            func_menu();
        }
        else {
            std::cout << "Wrong password, try again\n";
        }
        Code = "";
        pos_x = 0;
        pos_y = 0;
        //    std::cout << "Correct password!";
        //    
        //    //func_Menu();


        //}
        //else {
        //    std::cout << "WRONG!\n";
        //};
    };
};