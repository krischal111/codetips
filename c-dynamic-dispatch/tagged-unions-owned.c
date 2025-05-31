#include <stdio.h>

// Cat can talk and eat, like any other animal.
struct Cat {
    const char * name;
    int purr;
};
void cat_talk(struct Cat *cat) {
    if (cat->purr > 0) cat->purr--;
    printf("%s meows (Purr left: %d)\n", cat->name, cat->purr);
}
void cat_eat(struct Cat *cat) {
    cat->purr++;
    printf("%s eats fish (+1 purr, now %d)\n", cat->name, cat->purr);
}

// Dog can talk and eat, like any other animal.
struct Dog {
    int wag;
    const char * name;
};
void dog_talk(struct Dog *dog) {
    if (dog->wag > 0) dog->wag--;
    printf("%s woofs (Wag left: %d)\n", dog->name, dog->wag);
}
void dog_eat(struct Dog *dog) {
    dog->wag++;
    printf("%s eats bone (+1 wag, now %d)\n", dog->name, dog->wag);
}

// Animal is either a cat or a dog, that can both talk and eat.
struct Animal {
    union {
        struct Cat cat;
        struct Dog dog;
    };
    enum { CAT, DOG } type;
};
void animal_talk(struct Animal *animal) {
    switch (animal->type) {
        case CAT:
            cat_talk(& animal->cat);
            break;
        case DOG:
            dog_talk(& animal->dog);
            break;
        default:
            printf("Unknown animal type.\n");
    }
}
void animal_eat(struct Animal *animal) {
    switch(animal->type) {
        case CAT:
            cat_eat(& animal->cat);
            break;
        case DOG:
            dog_eat(& animal->dog);
            break;
        default:
            printf("Unknown animal type.\n");
    }
}

int main() {
    struct Cat kitty = {"Kitty", 5};
    struct Dog doggo = {3, "Doggo"};

    struct Animal animals[2];
    animals[0] = (struct Animal){.cat=kitty, CAT};
    animals[1] = (struct Animal){.dog=doggo, DOG};


    for (int i = 0; i < 2; i++) {
        animal_talk(&animals[i]);
    }

    printf("\n");
    for (int i = 0; i < 2; i++) {
        animal_eat(&animals[i]);
    }
}