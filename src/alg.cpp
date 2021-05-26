// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char x) {
    switch (x) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    default:
        return -1;
    }
}
std::string infx2pstfx(std::string inf) {
    std::string pstfx;
    int i = 0;
    char x = inf[i];
    char tem = 0;
    TStack <char> stackChar;
    while (x) {
        int pr;
        pr = priority(x);
        if (pr > -1) {
            if ((pr == 0 || pr > priority(tem) ||
                stackChar.isEmpty()) && x != ')') {
                if (stackChar.isEmpty())
                    tem = x;
                stackChar.push(x);
            } else if (x == ')') {
                while (stackChar.get() != '(') {
                    pstfx.push_back(stackChar.get());
                    pstfx.push_back(' ');
                    stackChar.pop();
                }
                stackChar.pop();
                if (stackChar.isEmpty())
                    tem = 0;
            } else {
                while (!stackChar.isEmpty() &&
                       priority(stackChar.get()) >= pr) {
                    pstfx.push_back(stackChar.get());
                    pstfx.push_back(' ');
                    stackChar.pop();
                }
                if (stackChar.isEmpty())
                    tem = x;
                stackChar.push(x);
            }
        } else {
            pstfx.push_back(x);
            pstfx.push_back(' ');
        }
        x = inf[++i];
    }
    while (!stackChar.isEmpty()) {
        pstfx.push_back(stackChar.get());
        pstfx.push_back(' ');
        stackChar.pop();
    }
    pstfx.erase(pstfx.end() - 1, pstfx.end());
    return pstfx;
}
int calculating(char oper, int num1, int num2) {
    switch (oper) {
    case '+':
        return num1 + num2;
        break;
    case '-':
        return num1 - num2;
        break;
    case '*':
        return num1 * num2;
        break;
    case '/':
        return num1 / num2;
        break;
    }
}

int eval(std::string pst) {
    TStack <int> stackInt;
    int i = 0, res = 0;
    char x = pst[i];
    while (x) {
        if (x >= '0' && x <= '9') {
            int insertInt = 0;
            int y = 1;
            while (x != ' ') {
                insertInt += (x - 48) * y;
                y *= 10;
                x = pst[++i];
            }
            stackInt.push(insertInt);
        } else {
            char oper = x;
            i++;
            int num2 = stackInt.get();
            stackInt.pop();
            int num1 = stackInt.get();
            stackInt.pop();
            int res = calculating(oper, num1, num2);
            stackInt.push(res);
        }
        if (i < pst.size())
            x = pst[++i];
        else
            x = 0;
    }
    res = stackInt.get();
    stackInt.pop();
    return res;
}
