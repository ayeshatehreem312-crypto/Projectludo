#include <iostream>
#include <string>

using namespace std;


// ANSI COLORS (ECLIPSE / LINUX)

string reset = "\033[0m";

string fg(int c) {
    switch (c) {
    case 0: return "\033[30m";
    case 1: return "\033[34m";
    case 2: return "\033[32m";
    case 4: return "\033[31m";
    case 7: return "\033[37m";
    case 8: return "\033[90m";
    case 14: return "\033[93m";
    case 15: return "\033[97m";
    default: return "\033[37m";
    }
}

string bg(int c) {
    switch (c) {
    case 0: return "\033[40m";
    case 1: return "\033[44m";
    case 2: return "\033[42m";
    case 4: return "\033[41m";
    case 14: return "\033[43m";
    case 7: return "\033[47m";
    case 8: return "\033[100m";
    default: return "\033[40m";
    }
}

const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int RED = 4;
const int YELLOW = 14;
const int WHITE = 7;
const int GRAY = 8;
const int BRIGHT_WHITE = 15;

string label[15][15];
int bgColor[15][15];
int fgColor[15][15];

int pr[4][4], pc[4][4];
char psym[4][4];
int pcolor[4][4];
int pid[4][4];
struct pathData
{
    int c;
    int r;
};
void play()
{
    static int turn = 0;
    int dice;
}
void path()
{
    pathData ourPath[52] = {
        {6,1},{6,2},{6,3},{6,4},{6,5},
        {5,6},{4,6},{3,6},{2,6},{1,6},{0,6},
        {0,7},{0,8},
        {1,8},{2,8},{3,8},{4,8},{5,8},
        {6,9},{6,10},{6,11},{6,12},{6,13},{6,14},
        {7,14},{8,14},
        {8,13},{8,12},{8,11},{8,10},{8,9},
        {9,8},{10,8},{11,8},{12,8},{13,8},{14,8},
        {14,7},{14,6},
        {13,6},{12,6},{11,6},{10,6},{9,6},
        {8,5},{8,4},{8,3},{8,2},{8,1},{8,0},
        {7,0},{6,0}
    };


    pathData wayTohome[4][5] = {
        {{7,1},{7,2},{7,3},{7,4},{7,5}},
        {{1,7},{2,7},{3,7},{4,7},{5,7}},
        {{7,13},{7,12},{7,11},{7,10},{7,9}},
        {{13,7},{12,7},{11,7},{10,7},{9,7}}
    };

    int startIndex[4] = { 0, 13, 26, 39 }; //green sa start kia ha
}
void initBoard() {

    for (int r = 0; r < 15; r++) {
        for (int c = 0; c < 15; c++) {
            label[r][c] = "   ";
            bgColor[r][c] = BLACK;
            fgColor[r][c] = GRAY;
        }
    }

    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) bgColor[r][c] = GREEN;
        for (int c = 9; c < 15; c++) bgColor[r][c] = YELLOW;
    }

    for (int r = 9; r < 15; r++) {
        for (int c = 9; c < 15; c++) bgColor[r][c] = RED;
        for (int c = 0; c < 6; c++) bgColor[r][c] = BLUE;
    }

    for (int i = 1; i < 6; i++) {
        bgColor[i][7] = YELLOW;
        bgColor[14 - i][7] = BLUE;
        bgColor[7][i] = GREEN;
        bgColor[7][14 - i] = RED;
    }

    for (int r = 6; r <= 8; r++)
        for (int c = 6; c <= 8; c++)
            label[r][c] = " H ";

    label[6][2] = " @ ";
    label[2][8] = " @ ";
    label[8][12] = " @ ";
    label[12][6] = " @ ";
}

void initPieces() {

    int gR[4] = { 1,1,4,4 }, gC[4] = { 1,4,1,4 };
    int yR[4] = { 1,1,4,4 }, yC[4] = { 10,13,10,13 };
    int rR[4] = { 10,10,13,13 }, rC[4] = { 10,13,10,13 };
    int bR[4] = { 10,10,13,13 }, bC[4] = { 1,4,1,4 };

    for (int i = 0; i < 4; i++) {
        pr[0][i] = gR[i]; pc[0][i] = gC[i];
        psym[0][i] = 'G'; pcolor[0][i] = BRIGHT_WHITE; pid[0][i] = i + 1;

        pr[1][i] = yR[i]; pc[1][i] = yC[i];
        psym[1][i] = 'Y'; pcolor[1][i] = WHITE; pid[1][i] = i + 1;

        pr[2][i] = rR[i]; pc[2][i] = rC[i];
        psym[2][i] = 'R'; pcolor[2][i] = BRIGHT_WHITE; pid[2][i] = i + 1;

        pr[3][i] = bR[i]; pc[3][i] = bC[i];
        psym[3][i] = 'B'; pcolor[3][i] = BRIGHT_WHITE; pid[3][i] = i + 1;
    }
}

void draw() {

    cout << "\033[2J\033[H"; // clear screen

    cout << "\n\t\t\t\t==== LUDO STAR  ====\n\n";

    for (int r = 0; r < 15; r++) {
        cout << "\t      ";

        for (int c = 0; c < 15; c++) {

            int found = 0;
            char sym = ' ';
            int col = WHITE;
            int id = 0;

            for (int p = 0; p < 4; p++) {
                for (int i = 0; i < 4; i++) {
                    if (pr[p][i] == r && pc[p][i] == c) {
                        found = 1;
                        sym = psym[p][i];
                        col = pcolor[p][i];
                        id = pid[p][i];
                    }
                }
            }

            if (found) {
                cout << fg(col) << bg(bgColor[r][c])
                    << sym << id << " " << reset;
            }
            else {
                cout << fg(fgColor[r][c]) << bg(bgColor[r][c])
                    << label[r][c] << reset;
            }

            cout << "|";
        }
        cout << "\n";
    }
}

int main() {

    initBoard();
    initPieces();

    draw();

    cout << "\n\tPress Enter to exit...";
    cin.get();

    return 0;
}