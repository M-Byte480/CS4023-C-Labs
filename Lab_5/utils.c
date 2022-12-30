int approxEquals(float num, float reference, float tolerance){
    // Get the upper range, and lower range
    float upper = reference + tolerance;
    float lower = reference - tolerance;

    // Return 1 if its within them
    if(num <= upper){
        if(num >= lower){
            return 1;
        }
    }

    // return 0 if its outside
    return 0;
}
