int is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n'; }

int string_count(char* str) {
   int length = 0;
   while (str[length]) length++;
   return length;
}

int string_words(char* str)  {
    int words = 0, isnt_pre_space = 0;
    for (int i = 0; str[i]; ++i)
        if (!is_whitespace(str[i]) && !isnt_pre_space) {
            words++; isnt_pre_space = !isnt_pre_space;
        } else if (is_whitespace(str[i])) isnt_pre_space = 0;
    return words;
}