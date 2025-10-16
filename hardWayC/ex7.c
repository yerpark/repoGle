#include <stdio.h>

int         main(int argc, char *argv[])
{
    int     bugs = 100;
    double  bug_rate = 1.2;

    printf("You have %d bugs at the imaginary rage of %f.\n", bugs, bug_rate);

    unsigned long    universe_of_defects = 1L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L * 7L;
    printf("The entire universe has %ld bugs.\n", universe_of_defects);
    // %ld -> long 출력 형식

    double  expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs.\n", expected_bugs);

    double  part_of_universe = expected_bugs / universe_of_defects;
    printf("That is only a %e portion of the universe.\n", part_of_universe);
    // %e -> 지수 표기법 (%f로 하면 정밀도 잘려서 정보 손실됨 )
    //    -> 작거나 큰 실수를 출력할 때 필수 무기 

    // 이것은 말도 안된다. 이상한 코드의 예를 든 것뿐이다.
    char    nul_byte = '\0';
    int     care_percentage = bugs * nul_byte;
    printf("Which means you should care %d%%.\n", care_percentage);
    
    return (0);
}