#include <iostream>
#include <vector>  
#include <set>
#include <map>
#include <string>
#include <algorithm>     
#include <iomanip>

using namespace std;

set <vector <char>> allel;

int Find1(char k, vector<char> bunch, int n) {
    for (int i = 0; i < bunch.size(); i++)
        if (k == bunch[i])
            return i;
}

bool Chek_ass(vector <vector <char>> res, vector<char> bunch, int n) {
    for (int a = 0; a < n; a++)
        for (int b = a; b < n; b++)
            for (int c = 0; c < n; c++)
                if (res[Find1(res[a][b], bunch, n)][c] != res[a][Find1(res[b][c], bunch, n)])
                    return false;
    return true;
}

bool Find(char k, vector<char> bunch, int n) {
    for (int i = 0; i < bunch.size(); i++)
        if (k == bunch[i])
            return true;
}

bool Ideals(vector <char> a, vector <char> bunch, vector <vector <char>> Kel, int s) {
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < bunch.size(); j++) {
            if (s == 1) {
                if (!Find(Kel[Find1(a[i], bunch, bunch.size())][j], a, a.size()))
                    return false;
            }
            else {
                if (!Find(Kel[j][Find1(a[i], bunch, bunch.size())], a, a.size()))
                    return false;
            }
        }
    return true;
}


set <vector<char>> Make(set <vector<char>> v1, set <vector<char>> v2) {
    set <vector<char>> res;
    for (vector<char> a : v1)
        for (vector<char> b : v2)
            if (a == b)
                res.insert(a);
    return res;
}

void exit(set <vector <char>> res) {
    for (vector <char> a : res) {
        cout << "{";
        for (int j = 0; j < a.size(); j++)
            if (j == a.size() - 1)
                cout << a[j];
            else
                cout << a[j] << " ";
        cout << "} ";
    }
}

void Ex1() {
    int n, m;
    char t1;
    cout << "Введите количество элементов в полугруппе S: ";
    cin >> n;
    vector <char> bunch;
    cout << "Введите элементы полугруппы: ";
    for (int i = 0; i < n; i++) {
        cin >> t1;
        bunch.push_back(t1);
    }

    vector <vector <char>> Kel;
    Kel.resize(n);
    cout << "Введите таблицу Кэлли:\n";
    for (int i = 0; i < n; i++) {
        Kel[i].resize(n);
        for (int j = 0; j < n; j++)
            cin >> Kel[i][j];
    }

    if (!Chek_ass(Kel, bunch, n)) {
        cout << "\nАссоциативность полугруппы НЕ выполняется!\n";
        return;
    }

    for (int i = (1 << n) - 1; i >= 0; i--) {
        vector <char> res2;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                res2.push_back(bunch[j]);
            }
        }
        if (res2.size() > 0)
            allel.insert(res2);
    }

    set <vector <char>> res;
    for (vector <char> a : allel)
        if (Ideals(a, bunch, Kel, 1))
            res.insert(a);
    cout << "Правые идеалы: ";
    exit(res);
    cout << endl;

    set <vector <char>> res3;
    for (vector <char> a : allel)
        if (Ideals(a, bunch, Kel, 0))
            res3.insert(a);
    cout << "Левые идеалы: ";
    exit(res3);
    cout << endl;

    cout << "Двусторонние идеалы: ";
    set <vector<char>> res4 = Make(res, res3);
    exit(res4);
    cout << endl;
}

/*-----------*/

set < pair <char, char>> Comp(set<pair <char, char>> R, set<pair <char, char>> L) {
    set < pair <char, char>> res;
    for (pair <char, char> a : R)
        for (pair <char, char> b : L) 
            if (a.second == b.first) 
                res.insert(make_pair(a.first, b.second));
    return res;
}

set <pair <char, char>> Peres(set <pair <char, char>> v1, set <pair <char, char>> v2) {
    set <pair <char, char>> res;
    for (pair <char, char> a : v1)
        for (pair <char, char> b : v2)
            if (a == b)
                res.insert(a);
    return res;
}

vector<int> Per(vector<int> v1, vector<int> v2) {
    vector<int> res;
    for (int el1 : v1)
        for (int el2 : v2)
            if (el1 == el2)
                res.push_back(el1);
    return res;
}

set<int> Per2(vector<int> v1, vector<int> v2) {
    set<int> res;
    for (int el1 : v1)
        for (int el2 : v2)
            if (el1 == el2)
                res.insert(el1);
    return res;
}

vector<vector<int>> Equi(int** v, int n, char* els) {

    vector<vector<int>> res;
    int* count = new int[n];
    for (int i = 0; i < n; i++) {
        count[i] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (count[i]) {
            vector<int> srez;
            for (int j = i; j < n; j++) {
                if (v[i][j] && count[j]) {
                    count[j] = 0;
                    srez.push_back(j);
                }
            }
            count[i] = 0;
            res.push_back(srez);
        }
    }

    cout << endl << "{";
    for (int i = 0; i < res.size(); i++) {
        cout << "{";
        for (int j = 0; j < res[i].size(); j++) {
            cout << els[res[i][j]];
            if (j != res[i].size() - 1)
                cout << ", ";
        }
        cout << "}";
        if (i != res.size() - 1)
            cout << ", ";
    }
    cout << "}" << endl;
    
    return res;
}

void Ex2() {
    int n, m;
    char t1;
    cout << "Введите число элементов в полугруппе S: ";
    cin >> n;
    vector <char> bunch;
    cout << "Введите элементы полугруппы: ";
    for (int i = 0; i < n; i++) {
        cin >> t1;
        bunch.push_back(t1);
    }

    char* a = new char[n];
    for (int i = 0; i < bunch.size(); i++) {
        a[i] = bunch[i];
    }

    vector <vector <char>> Kel;
    Kel.resize(n);
    cout << "Введите таблицу Кэлли\n";
    for (int i = 0; i < n; i++) {
        Kel[i].resize(n);
        for (int j = 0; j < n; j++)
            cin >> Kel[i][j];
    }
    cout << "\nОтношения Грина:\n";
    //R
    set <pair <char, char>> res1;
    for (int i = 0; i < bunch.size(); i++)
        for (int j = 0; j < bunch.size(); j++) {
            set <char> set11;
            set11.insert(bunch[i]);
            for (int k = 0; k < Kel[i].size(); k++)
                set11.insert(Kel[i][k]);
            set <char> set12;
            set12.insert(bunch[j]);
            for (int k = 0; k < Kel[j].size(); k++)
                set12.insert(Kel[j][k]);
            if (set11 == set12)
                res1.insert(make_pair(bunch[i], bunch[j]));
        }
    //L
    set <pair <char, char>> res2;
    for (int i = 0; i < bunch.size(); i++)
        for (int j = 0; j < bunch.size(); j++) {
            set <char> set11;
            set11.insert(bunch[i]);
            for (int k = 0; k < n; k++)
                set11.insert(Kel[k][i]);
            set <char> set12;
            set12.insert(bunch[j]);
            for (int k = 0; k < n; k++)
                set12.insert(Kel[k][j]);
            if (set11 == set12)
                res2.insert(make_pair(bunch[i], bunch[j]));
        }
    //J
    set <pair <char, char>> res3;
    for (int i = 0; i < bunch.size(); i++)
        for (int j = 0; j < bunch.size(); j++) {
            set <char> set11;
            set11.insert(bunch[i]);
            set <char> set111;
            for (int k = 0; k < n; k++)
                set111.insert(Kel[k][i]);
            for (char r : set111) {
                for (int k = 0; k < n; k++)
                    set11.insert(Kel[Find1(r, bunch, bunch.size())][k]);
            }

            set <char> set12;
            set12.insert(bunch[j]);
            set <char> set112;
            for (int k = 0; k < n; k++)
                set112.insert(Kel[k][j]);
            for (char r : set112) {
                for (int k = 0; k < n; k++)
                    set12.insert(Kel[Find1(r, bunch, bunch.size())][k]);
            }
            if (set11 == set12)
                res3.insert(make_pair(bunch[i], bunch[j]));
        }

    cout << "R = {";
    for (pair <char, char> a : res1)
        cout << "(" << a.first << ", " << a.second << ") ";
    cout << "}\n";

    cout << "L = {";
    for (pair <char, char> a : res2)
        cout << "(" << a.first << ", " << a.second << ") ";
    cout << "}\n";

    cout << "J = {";
    for (pair <char, char> a : res3)
        cout << "(" << a.first << ", " << a.second << ") ";
    cout << "}\n";

    set <pair <char, char>> res4 = Peres(res1, res2);
    cout << "H = {";
    for (pair <char, char> a : res4)
        cout << "(" << a.first << ", " << a.second << ") ";
    cout << "}\n";

    set <pair <char, char>> res5 = Comp(res1, res2);
    cout << "D = {";
    for (pair <char, char> a : res5)
        cout << "(" << a.first << ", " << a.second << ") ";
    cout << "}\n";

    int** matr1;
    matr1 = new int* [n];
    for (int i = 0; i < n; i++) {
        matr1[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matr1[i][j] = 0;
        }
    }
    for (pair <char, char> a : res1) {
        matr1[Find1(a.first, bunch, bunch.size())][Find1(a.second, bunch, bunch.size())] = 1;
    }
    cout << "\nКлассы эквивалентности в R:";
    vector<vector<int>> r = Equi(matr1, n, a);
    
    int** matr2;
    matr2 = new int* [n];
    for (int i = 0; i < n; i++) {
        matr2[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matr2[i][j] = 0;
        }
    }
    for (pair <char, char> a : res2) {
        matr2[Find1(a.first, bunch, bunch.size())][Find1(a.second, bunch, bunch.size())] = 1;
    }
    cout << "\nКлассы эквивалентности в L:";
    vector<vector<int>> l = Equi(matr2, n, a);

    int** matr5;
    matr5 = new int* [n];
    for (int i = 0; i < n; i++) {
        matr5[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matr5[i][j] = 0;
        }
    }
    for (pair <char, char> a : res5) {
        matr5[Find1(a.first, bunch, bunch.size())][Find1(a.second, bunch, bunch.size())] = 1;
    }
    cout << "\nКлассы эквивалентности в D:";
    vector<vector<int>> d = Equi(matr5, n, a);

    cout <<"<<egg-box>> - картина:\n";
    for (vector<int> cl : d) {
        vector<vector<int>> res_l;
        vector<vector<int>> res_r;
        for (vector<int> el : l) {
            if (Per(cl, el) == el)
                res_l.push_back(el);
        }
        for (vector<int> el : r)
            if (Per(cl, el) == el)
                res_r.push_back(el);
        cout << setw(15);
        for (vector<int> ans : res_l) {
            cout << "{";
            string res = "";
            for (int x : ans) {
                res = res + a[x] + ", ";
            }
            res.pop_back();
            res.pop_back();
            res += "}";
            cout << res;
        }
        cout << endl;
        for (vector<int> ans : res_r) {
            cout << "{";
            string res = "";
            for (int x : ans) {
                res = res + a[x] + ", ";
            }
            res.pop_back();
            res.pop_back();
            res += "}";
            cout << res << setw(14);
            for (vector<int> ans2 : res_l) {
                string res2 = "";
                res2 += "{";
                set<int> k = Per2(ans, ans2);
                for (int x : k) {
                    res2 = res2 + a[x] + ", ";
                }
                res2.pop_back();
                res2.pop_back();
                res2 += "}";
                cout << res2;
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    for (;;) {
        cout << "1 - Построить идеал полугруппы по таблице Кэли\n2 - Вычислить отношения Грина и построить <<egg-box>>-картины\n";
        int x;
        cin >> x;
        switch (x) {
        case 1:
            Ex1();
            cout << endl;
            break;
        case 2:
            Ex2();
            cout << endl;
            break;
        case 0:
            break;
        }
    }
}
