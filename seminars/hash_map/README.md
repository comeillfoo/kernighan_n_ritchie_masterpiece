# Phylosophical C

There are two common architectural approaches:

+ down-up
+ up-down

## Hash Map

### idea.md:

  hashmap requirements:

  * need to put keys
  * need to get values
  * maps the elements between something
  * uses special hash-function gets the data bytes and returned special number called "hash"
  * in the utopia there are no identical hashes which hash-function returns
  * the hash must have a fixed size (4, 2 bytes)
  * in practice there are a lot of collisions for hashes
  * collisions mean that there are similar hashes for different data calculated with hash-function

  hashmap structure:
  
  * array of linked list
  * index of array calculates as hash(element) % s, where s - size of array
  * elements - link to the data that storaged

  hashmap functionality:
  
  * contains key: calculate hash, get linked list by index and iterate through the list to find the searched element
  * 

We'll use down-up approach that includes the following items:

  ###### down-up approach:

  + calculate hashes
  + print numbers on the screen
  + etc...

## Linked List

The data Structure that stores elements which must be the same time (unlike python). It looks like the pair (node) of *data* and *link to the next element* (pointer in C).

        +---+---+   +---+---+   +---+---+
        + 2 + x-+-->+ 3 + x-+-->+ 4 + x-+-->NULL
        +---+---+   +---+---+   +---+---+

## Notes

### Memory

Simplified, your program memory space divided into 3 parts:

+ globals --- space for global variables;
+ heap --- space for dynamic memory allocating (during runtime);
+ stack --- space for local variables

        .         .
        +---------+
        + globals +
        +---------+
        +  heap   +
        +---------+
        +  stack  +
        +---------+
        .         .

### Text line hash

To calculate hash for text line we can use polynomial hash that look like:

        (a0 + a1 * p + a2 * p^2 + a3 * p^3 + ...) % P

where a0, a1, a2... - codes for string chars, p - some prime constant, some large prime number
