#include "Command_Line.h"

int main() {
    Command_Line cmd_line;
    cmd_line.update();

    return 0;
}


/*
 * load tt D:\FMI\Second year\Third semester\DSA\trees\tt.txt
 * load tt2 D:\FMI\Second year\Third semester\DSA\trees\tt2.txt
 * contains tt tt2
 *
 * load t1 D:\FMI\Second year\Third semester\DSA\tree1.txt
 * load t2 D:\FMI\Second year\Third semester\DSA\tree2.txt
 * contains t1 t2
 *
 * load eq1 D:\FMI\Second year\Third semester\DSA\trees\equal1.txt
 * load eq2 D:\FMI\Second year\Third semester\DSA\trees\equal2.txt
 * contains eq1 eq2
 *
 * load ex1 D:\FMI\Second year\Third semester\DSA\trees\ex1.txt
 * load ex2 D:\FMI\Second year\Third semester\DSA\trees\ex2.txt
 * contains ex1 ex2
 *
 * load 0 D:\FMI\Second year\Third semester\DSA\trees\ex1.txt
 * load 1 D:\FMI\Second year\Third semester\DSA\trees\ex2.txt
 * remove 0 1
 *
 * load t1 D:\FMI\Second year\Third semester\DSA\tree1.txt
 * load t2 D:\FMI\Second year\Third semester\DSA\tree2.txt
 * remove t1 t2
 *
 * load tt D:\FMI\Second year\Third semester\DSA\trees\tt.txt
 * load tt2 D:\FMI\Second year\Third semester\DSA\trees\tt2.txt
 * remove tt tt2
 *
 * load tt D:\FMI\Second year\Third semester\DSA\trees\tt.txt
 * load tt2 D:\FMI\Second year\Third semester\DSA\trees\tt2.txt
 * remove tt2 tt
 *
 * load ex1 D:\FMI\Second year\Third semester\DSA\trees\ex1.txt
 * load ex2 D:\FMI\Second year\Third semester\DSA\trees\ex2.txt
 * remove ex1 ex2
 * save ex1 D:\FMI\Second year\Third semester\DSA\trees\result_ex.txt
 *
 * load eq1 D:\FMI\Second year\Third semester\DSA\trees\equal1.txt
 * load eq2 D:\FMI\Second year\Third semester\DSA\trees\equal2.txt
 * remove eq1 eq2
 *
 * load r1 D:\FMI\Second year\Third semester\DSA\trees\r1.txt
 * load r2 D:\FMI\Second year\Third semester\DSA\trees\r2.txt
 * remove r1 r2
 *
 * load rr1 D:\FMI\Second year\Third semester\DSA\trees\rr1.txt
 * load rr2 D:\FMI\Second year\Third semester\DSA\trees\rr2.txt
 * remove rr1 rr2
 */