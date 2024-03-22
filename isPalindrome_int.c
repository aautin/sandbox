bool isPalindrome(int x) {
    long int    temp = x;
    long int    xReverse = 0;
    long int    power = 10;

    if (x < 0)
        return 0;

    while (x / power)
        power *= 10;

    while (temp)
    {
        power /= 10;
        xReverse += (temp % 10) * power;
        temp /= 10; 
    }

    return (xReverse == x);
}

