int discriminant(int a, int b, int c) {
    return b * b - 4 * a * c;
}

int root_count(int a, int b, int c) {
   int D = discriminant(a, b, c);
   if (D > 0) return 2;
   else if (D == 0) return 1;
   else return 0;
}

int main() {
    // Считайте три числа в локальные переменные
    int a = read_int();
    int b = read_int();
    int c = read_int();


    // выведите результат запуска root_count с аргументами a, b и c.
    printf("%d\n", root_count(a, b, c));

    return 0;
}