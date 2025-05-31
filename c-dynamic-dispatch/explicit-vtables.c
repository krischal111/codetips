#include <stdio.h>

// Creating vtable interface for Animal
struct AnimalVTable {
    void (*talk)(void *animal);
    void (*eat)(void *animal);
};

// Animal class and its methods using vtable
struct Animal {
    void * animal_pointer;
    struct AnimalVTable *vtable;
};
void animal_talk(struct Animal *animal) {
    animal->vtable->talk(animal->animal_pointer);
}
void animal_eat(struct Animal *animal) {
    animal->vtable->eat(animal->animal_pointer);
}

// Definitions child classes (Cat and Dog) and their methods.
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

// Overridden methods (for vtable)
void cat_talk_override(void *animal) {
    struct Cat *cat = (struct Cat *)animal;
    cat_talk(cat);
}
void cat_eat_override(void *animal) {
    struct Cat *cat = (struct Cat *)animal;
    cat_eat(cat);
}

void dog_talk_override(void *animal) {
    struct Dog *dog = (struct Dog *)animal;
    dog_talk(dog);
}
void dog_eat_override(void *animal) {
    struct Dog *dog = (struct Dog *)animal;
    dog_eat(dog);
}

// VTable for Cat and Dog
struct AnimalVTable cat_vtable = {
    .talk = cat_talk_override,
    .eat = cat_eat_override
};
struct AnimalVTable dog_vtable = {
    .talk = dog_talk_override,
    .eat = dog_eat_override
};

// Main function to demonstrate the dynamic dispatch
int main() {
    struct Cat kitty = { "Kitty", 5 };
    struct Dog doggo = { 3, "Doggo" };

    struct Animal animals[2];
    animals[0] = (struct Animal){&kitty, .vtable = &cat_vtable};
    animals[1] = (struct Animal){&doggo, .vtable = &dog_vtable};

    for (int i = 0; i < 2; i++) {
        animal_talk(&animals[i]);
    }
    printf("\n");
    for (int i = 0; i < 2; i++) {
        animal_talk(&animals[i]);
    }
}