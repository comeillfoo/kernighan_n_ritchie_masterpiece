void fizzbuzz(int arg) {
    if (arg <= 0) printf("no\n");
    else {
        if (arg % 3 == 0) printf("fizz");
        if (arg % 5 == 0) printf("buzz\n");
    }
}