char flipCharacter(char c){

    double ASCII = (int) c;
    double dif;
    // Get the midpoint of each of these and we are going to rotate around it by getting the difference and adding
    // Or subtracting based on if the letter is higher or lower the midpoint
    double middle = ((double) 'a' + (double) 'z') / 2;
    double mIDDLE = ((double) 'A' + (double) 'Z') / 2;
    double middleNumber = ((double) '0' + (double) '9') / 2;

    // Subtract letter from center
    // Add the + or - difference to it to get the inverse
    if ((ASCII >= 'a') && (ASCII <= 'z')){
        dif = middle - ASCII;
        ASCII = middle + dif;
    }else if((ASCII >= 'A') && (ASCII <= 'Z')){
        dif = mIDDLE - ASCII;
        ASCII = mIDDLE + dif;
    }else if((ASCII >= '0') && (ASCII <= '9')) {
        dif = middleNumber - ASCII;
        ASCII = middleNumber + dif;
    }
    // Cast it as int, then char
    return (char) (int) ASCII;
}