#include <cstdlib>
#include <ctime>
#include <fstream>  
#include <iostream>

using namespace std;

void printt(int a[21][21], int num_pokolenia, int mode_how, int how_live) {
    if (mode_how == 1) {
        ofstream f("work.out");
        f << "Pokolenie: " << num_pokolenia << endl;
        if (how_live != 0) {
            f << "Live in this area (kol-vo 1): " << how_live << endl;
        }
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                f << a[i][j] << " ";
                cout << a[i][j] << " ";
            }
            f << endl;
            cout << endl;
        }
        f << endl;
        cout << endl;
        f.close();
    }
    else if (mode_how == 2) {
        ofstream f("work.out", ios::app);
        f << "Pokolenie: " << num_pokolenia << endl;
        if (how_live != 0) {
            f << "Live in this area (kol-vo 1): " << how_live << endl;

        }
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                f << a[i][j] << " ";
                cout << a[i][j] << " ";
            }
            f << endl;
            cout << endl;
        }
        f << endl;
        cout << endl;
        f.close();
    }
}

void next_generation(int nowlive[21][21]) {
    int futurelive[21][21] = { {0} };
    int nowlive222[21][21] = { {0} };
    int count_generation;
    cout << "Enter how much pokolenis: ";
    cin >> count_generation;
    int cntr = 0;
    bool flag = 0;
    for (int g = 1; g <= count_generation; g++) {
        for (int i = 0; i < 21; i++)
            for (int j = 0; j < 21; j++)
                nowlive222[i][j] = nowlive[i][j];
        for (int k = 0; k < 21; k++) {
            for (int p = 0; p < 21; p++) {
                if (nowlive[k][p] == 0) {
                    flag = 1;
                }
                else if (nowlive[k][p] == 12) {
                    nowlive[k][p] = 0;
                    nowlive222[k][p] = 0;
                }
            }
        }
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                // if (nowlive[i][j] == 0){nowlive[i][j] = 1; flag = 1;}
                // else if (nowlive[i][j] == 12){nowlive[i][j] = 0;}
                if (nowlive[i][j] > 0 && nowlive[i][j] < 12) {
                    int countNeighbour = 0;
                    for (int x = i - 1; x < i + 2; x++) {
                        for (int y = j - 1; y < j + 2; y++) {
                            if (x > -1 && x < 21 && y > -1 && y < 21 && (x != i || y != j)) {
                                if (nowlive222[x][y] != 0) {
                                    countNeighbour += 1;
                                }
                            }
                        }
                    }
                    if (countNeighbour == 2 || countNeighbour == 3) {
                        nowlive[i][j] += 1;
                        flag = 1;
                    }
                    else {
                        nowlive[i][j] = -1;
                    }
                }
            }
        }
        for (int k = 0; k < 21; k++) {
            for (int p = 0; p < 21; p++) {
                if (nowlive[k][p] == 0)
                    nowlive[k][p] = 1;
                else if (nowlive[k][p] == -1)
                    nowlive[k][p] = 0;
            }
        }
        cntr = 0;
        for (int i = 0; i < 21; i++) {
            for (int j = 0; j < 21; j++) {
                if (nowlive[i][j] == 1) {
                    cntr += 1;
                }
                futurelive[i][j] = nowlive[i][j];
            }
        }
        printt(futurelive, g, 2, cntr);
        if (flag == 0) {
            cout << "All died";
            exit(0);
        }
    }
}

void create_first_live() {
    int nowlive[21][21] = { {0} };
    ifstream file("work.dat");
    char text[256];
    string st;
    int cnt = 0;
    int cc = 0;
    while (file) {
        file.getline(text, 256);
        st = text;
        for (int i = 0; i < st.size(); i++) {
            if (st[i] == 'X') {
                nowlive[cnt][i] = 1;
                cc += 1;
            }
            else {
                nowlive[cnt][i] = 0;
            }
        }
        cnt += 1;
    }
    file.close();
    next_generation(nowlive);
}

void create_first_file() {
    ofstream file("work.dat");
    srand((unsigned)time(0));
    int randombukv;
    for (int i = 0; i < 21; i++) {
        string tt = "";
        for (int g = 0; g < 21; g++) {
            randombukv = ((rand() % 26) + 65);
            tt += (char)randombukv;
        }
        file << tt;
        file << endl;
    }
    file.close();
    create_first_live();
}

int main() { create_first_file(); }