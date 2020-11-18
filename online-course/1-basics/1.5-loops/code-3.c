int divides(int a, int b) { return a % b == 0; }
void print_newline() { printf("\n"); }

void divisors(int limit) {
    for (int i = 1; i <= limit; ++i) {
        printf("%d: ", i);
        for (int j = 2; j <= i; ++j)
            if (divides(i, j)) printf("%d ", j);
        print_newline();
    }
}


int main() {
    divisors(100);
    return 0;
}