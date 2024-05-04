#pragma once
#ifndef UTILS_H
#define UTILS_H


inline bool isNumeric(const std::string& s)
{
    if (s.length() == 0) return false;
    for (int32_t i = 0; i < s.length(); ++i)
    {
        if ((s[i] >= '0' && s[i] <= '9')
            || s[i] == ' '
            || s[i] == '.'
            || (s[i] == '-' && i == 0))
            continue;
        return false;
    }
    return true;
}

#endif // UTILS_H



// save code for speedtest:
    // SPEEDTEST

    // if (1 == 1)
    // { // 1==1 if you want it!
    //     text = "b=a*a*a/100000000";
    //     vector<RPNToken> tokensRPN0 = makeRPN(text, keywords, VARIABLES, reportLevel);
    //     int n = 0;
    //     while (n < 50000)
    //     {
    //         std::cout << "\033[H\033[2J\033[3J";
    //         VARIABLES.setVar(0, n);
    //         calcandprint(tokensRPN0, VARIABLES, 0);
    //         n++;
    //     }
    //     sleep(200); // without sleep, cout gets in trouble in this final phase
    //     // calc.calcandprint(tokensRPN, true);
    //     return 0;
    // }
    // SPEEDTEST END


