// START - Imports & Namespaces
#include <iostream>  // For printing to console, etc.
#include <cstdlib>   // For random
#include <ctime>     // For time() function
#include <cmath>     // For rounding

using namespace std; // For more simple printing to console
// STOP  - Imports & Namespaces

// START - Global Variables
// Array attributes
const int rows = 100;
const int cols = 100;
const int catArrayLength = 50; // Cat array stuff
const int dogArrayLength = 50; // Dog array
const int maxNumOfDays = 100000; // Max iterations of sim. loop (also determines length of analytical arrays)

// Define the Analytics Array
int dogAnalyticsArray[maxNumOfDays];
int catAnalyticsArray[maxNumOfDays];
int fightsAnalyticsArray[maxNumOfDays];
int catFightSuccessAnalyticsArray[maxNumOfDays];

// Variable to determine the average % of cat win rate in fights
int catWinRateVar = 80;

// # Of Given Animal Vars
const int numOfCats = 3; // Number of cats to be placed
const int numOfDogs = 50; // Number of dogs to be placed
// STOP  - Global Variables



// START - RANDOM FUNCTION
int randomNum(int max) { // Function that generates a random number up to the number inputted as an argument (max)
    int randomNum = rand() % max; // Generate a random number between 0 and max
    return randomNum;
}
// STOP  - RANDOM FUNCTION



// START - Classes
class Animal {
private:
    int x;
    int y;
    int strength;

public:
    Animal() { // Default constructor
        setX(0);
        setY(0);
        setStrength(0);
    }

    Animal(int initialX, int initialY, int initialStrength) { // Custom Constructor
        setX(initialX);
        setY(initialY);
        setStrength(initialStrength);
    }

    // Setter functions
    void setX(int newX) {
        x = newX;
    }

    void setY(int newY) {
        y = newY;
    }

    void setStrength(int newStrength) {
        strength = newStrength;
    }

    void decrementStrenght() {
        if ( strength >=1 ) {
            setStrength(strength - 1);
        }
    }

    // Getter functions
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getStrength() const {
        return strength;
    }

    // Methods
    void move(int deltaX, int deltaY) {
        x += deltaX;
        y += deltaY;
    }

    // Virtual destructor
    virtual ~Animal() {}
};

// PLAYSPACE MATRIX:
Animal* matrix[rows][cols]; // Matrix holding the simulation
// PlAYSPACE MATRIX

class Dog : public Animal {
private:
    int id;

public:
    // Default constructor
    Dog() {
        id = 0;
    }

    // Custom constructor
    Dog(int initialX, int initialY, int dogID, int initialStrength)
            : id(dogID), Animal(initialX, initialY, initialStrength) {}

    // Setters
    void setID(int newID) {
        id = newID;
    }

    // Getters
    int getID() const {
        return id;
    }

    // Virtual move method for Dog
    void move() {
        int newX, newY;
        do {
            int direction = randomNum(4); // Generate a random direction (0: up, 1: down, 2: left, 3: right)
            switch (direction) {
                case 0: // Up
                    newX = getX() - 3;
                    newY = getY();
                    break;
                case 1: // Down
                    newX = getX() + 3;
                    newY = getY();
                    break;
                case 2: // Left
                    newX = getX();
                    newY = getY() - 3;
                    break;
                case 3: // Right
                    newX = getX();
                    newY = getY() + 3;
                    break;
                default:
                    // Handle any unexpected cases
                    newX = getX();
                    newY = getY();
                    break;
            }
        } while ((newX < 0 || newX >= rows || newY < 0 || newY >= cols) || (matrix[newX][newY] != nullptr)); // Retry if out of bounds or destination is occupied

        // Move the Dog
        setX(newX);
        setY(newY);
    }

    ~Dog() {
        //
    }
};

class Cat : public Animal {
private:
    int id;

public:
    // Default constructor
    Cat() {
        id = 0;
    }

    // Custom constructor
    Cat(int initialX, int initialY, int catID, int initialStrength)
            : id(catID), Animal(initialX, initialY, initialStrength) {}

    // Setters
    void setID(int newID) {
        id = newID;
    }

    // Getters
    int getID() const {
        return id;
    }

    // Virtual move method for Cat
    void move() {
        int newX, newY;
        do {
            int direction = randomNum(4); // Generate a random direction (0: up, 1: down, 2: left, 3: right)
            switch (direction) {
                case 0: // Up
                    newX = getX() - 1;
                    newY = getY();
                    break;
                case 1: // Down
                    newX = getX() + 1;
                    newY = getY();
                    break;
                case 2: // Left
                    newX = getX();
                    newY = getY() - 1;
                    break;
                case 3: // Right
                    newX = getX();
                    newY = getY() + 1;
                    break;
                default:
                    // Handle any unexpected cases
                    newX = getX();
                    newY = getY();
                    break;
            }
        } while ((newX < 0 || newX >= rows || newY < 0 || newY >= cols) || (matrix[newX][newY] != nullptr)); // Retry if out of bounds or destination is occupied

        // Move the cat
        setX(newX);
        setY(newY);
    }


    // Method to fight a dog
    bool fightDog(Dog* dog) {
        if (dog == nullptr) {
            return true; // Assuming cat loses if there's no dog to fight
        }
        int random = randomNum(99);
        if ( (getStrength() > dog->getStrength()) and (random > catWinRateVar) ) {
            return true; // Cat wins
        } else {
            return false; // Cat loses
        }
    }


    // Function to check for nearby dogs
    Dog* checkForNearbyDogs(Animal* matrix[rows][cols]) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newX = getX() + i;
                int newY = getY() + j;
                // Check boundaries
                if (newX >= 0 && newX < rows && newY >= 0 && newY < cols) {
                    // Check if there's a Dog at this position
                    if (matrix[newX][newY] != nullptr && typeid(*matrix[newX][newY]) == typeid(Dog)) {
                        return dynamic_cast<Dog*>(matrix[newX][newY]);
                    }
                }
            }
        }
        return nullptr;
    }

    ~Cat() {
        //
    }
};
// STOP  - Classes



// START - ANIMAL MATRICES
Cat* catArray[catArrayLength];
Dog* dogArray[dogArrayLength];
// STOP  - ANIMAL MATRICES



// START - Functions
void populateMatrixWithNull() { // Function that fills the array with nullptr values to make it "empty"
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = nullptr;
        }
    }
}

void placeAnimalInPlayspace(Animal &animal) {
    int posX = animal.getX();
    int posY = animal.getY();

    // Check if the spot in the playspace array is taken
    while (matrix[posX][posY] != nullptr) {
        cout << "Position Not Available, Trying Again..." << endl;

        // If the spot is taken, change the animal's position and try again
        posX++;
        if (posX >= rows) {
            posX = 0;
            posY++;
            if (posY >= cols) {
                posY = 0;
            }
        }
    }

    // Place the animal in the playspace array
    matrix[posX][posY] = &animal;
}

void placeAnimalsInPlayspace(Animal* animalArray[], int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        int posX = animalArray[i]->getX();
        int posY = animalArray[i]->getY();

        // Check if the spot in the playspace array is taken
        while (matrix[posX][posY] != nullptr) {
            cout << "Position Not Available, Trying Again..." << endl;

            // If the spot is taken, change the animal's position and try again
            posX++;
            if (posX >= rows) {
                posX = 0;
                posY++;
                if (posY >= cols) {
                    posY = 0;
                }
            }
        }

        // Place the animal in the playspace array
        matrix[posX][posY] = animalArray[i];
    }
}

void placeCatsInPlayspace(Cat* catArray[], int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        if ( catArray[i] != nullptr ){
            int posX = catArray[i]->getX();
            int posY = catArray[i]->getY();

            // Check if the spot in the playspace array is taken
            while (matrix[posX][posY] != nullptr) {
                //cout << "Position Not Available, Trying Again..." << endl;

                // If the spot is taken, change the cat's position and try again
                posX++;
                if (posX >= rows) {
                    posX = 0;
                    posY++;
                    if (posY >= cols) {
                        posY = 0;
                    }
                }
            }
            // Place the cat in the playspace array
            matrix[posX][posY] = catArray[i];
        }
    }
}

void placeDogsInPlayspace(Dog* dogArray[], int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        if ( dogArray[i] != nullptr ){
            int posX = dogArray[i]->getX();
            int posY = dogArray[i]->getY();

            // Check if the spot in the playspace array is taken
            while (matrix[posX][posY] != nullptr) {
                //cout << "Position Not Available, Trying Again..." << endl;

                // If the spot is taken, change the cat's position and try again
                posX++;
                if (posX >= rows) {
                    posX = 0;
                    posY++;
                    if (posY >= cols) {
                        posY = 0;
                    }
                }
            }
            // Place the cat in the playspace array
            matrix[posX][posY] = dogArray[i];
        }
    }
}

void populateCatArray(int randomFlag, Cat* catArray[]) {
    if (randomFlag == 0) { // Not random placing of cats, will place at (0,0) and then (0,1) , and so on
        for (int i = 0; i < numOfCats; i++) { // Generate cats
            catArray[i] = new Cat(0, i, i, 10); // Allocate memory for new Cat objects and store their pointers in the array
        }
        // Place nullptrs in the rest of the places
        for (int i = numOfCats; i < catArrayLength; i++) {
            catArray[i] = nullptr;
        }
    } else if (randomFlag == 1) { // Will randomize the placing of cats
        for (int i = 0; i < numOfCats; i++) { // Generate cats
            int randomX = randomNum(99);
            int randomY = randomNum(99);
            int randomStrength = randomNum(50);
            catArray[i] = new Cat(randomX, randomY, i, (randomStrength + 10) ); // Allocate memory for new Cat objects and store their pointers in the array
        }
        // Place nullptrs in the rest of the places
        for (int i = numOfCats; i < catArrayLength; i++) {
            catArray[i] = nullptr;
        }
    } else {
        cout << "INVALID FLAG. MUST BE 0 OR 1!" << endl;
    }
}

void printCatArray(Cat* catArray[]) {
    for (int i = 0; i < catArrayLength; i++) {
        if (catArray[i] != nullptr ) {
            cout << catArray[i]->getID() << " "; // Corrected to access object members through pointers
        } else if ( catArray[i] == nullptr ) {
            cout << "N ";
        } else {
            cout << "AN ERROR IN THE printCatArray() FUNCTION HAS OCCURRED!";
        }
    }
    cout << endl;
}

void populateDogArray(int randomFlag, Dog* dogArray[]) {
    if (randomFlag == 0) { // Not random placing of dogs, will place at 0,0 and then 0,1 , and so on
        for (int i = 0; i < numOfDogs; i++) { // Generate 3 dogs
            dogArray[i] = new Dog(1, i, i, 10); // Allocate memory for new Dog objects and store their pointers in the array
        }
        // Place nullptrs in the rest of the places
        for (int i = numOfDogs; i < dogArrayLength; i++) {
            dogArray[i] = nullptr;
        }
    } else if (randomFlag == 1) { // Will randomize the placing of dogs
        for (int i = 0; i < numOfDogs; i++) { // Generate dogs
            int randomX = randomNum(99);
            int randomY = randomNum(99);
            int randomStrength = randomNum(30);
            dogArray[i] = new Dog(randomX, randomY, (i + 3), randomStrength); // Allocate memory for new Cat objects and store their pointers in the array
        }
        // Place nullptrs in the rest of the places
        for (int i = numOfDogs; i < dogArrayLength; i++) {
            dogArray[i] = nullptr;
        }
    } else {
        cout << "INVALID FLAG. MUST BE 0 OR 1!" << endl;
    }
}

void printDogArray(Dog* dogArray[]) {
    for (int i = 0; i < dogArrayLength; i++) {
        if (dogArray[i] != nullptr ) {
            cout << dogArray[i]->getID() << " "; // Corrected to access object members through pointers
        } else if ( dogArray[i] == nullptr ) {
            cout << "N ";
        } else {
            cout << "AN ERROR IN THE printCatArray() FUNCTION HAS OCCURRED!";
        }
    }
    cout << endl;
}

void printMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (matrix[i][j] != nullptr) {
                if (typeid(*matrix[i][j]) == typeid(Cat)) {
                    cout << "C";
                } else if (typeid(*matrix[i][j]) == typeid(Dog)) {
                    cout << "D";
                } else {
                    cout << "A"; // Print "A" for unknown animal types
                }
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void clearMatrix() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = nullptr;
        }
    }
} // Clears the matrix of all objects

int countDogs(Dog* dogArray[]) {
    int count = 0;
    for (int i = 0; i < dogArrayLength; ++i) {
        if (dogArray[i] != nullptr) {
            count++;
        }
    }
    return count;
} // Returns the number of dogs in the dog array

int countCats(Cat* dogArray[]) {
    int count = 0;
    for (int i = 0; i < catArrayLength; ++i) {
        if (catArray[i] != nullptr) {
            count++;
        }
    }
    return count;
} // Returns the number of dogs in the dog array

void placeNewCatIntoCatArray(Cat* newCat) { // Places the new cat at the first open spot in the cat array
    for (int i = 0; i < catArrayLength; ++i) {
        if (catArray[i] == nullptr) {
            catArray[i] = newCat;
            break;
        } else if (catArray[i] != nullptr) {
            continue;
        } else {
            cout << "AN ERROR HAS OCCURRED IN THE placeNewCatIntoCatArray FUNCTION!" << endl;
        }
    }
}

int findTotalNumberOfFights() {
    int totalFights = 0;
    for (int i = 0; i < maxNumOfDays; i++) {
        totalFights += fightsAnalyticsArray[i];
    }
    return totalFights;
}

float findCatFightSuccessRate() {
    int totalFightsWon = 0;
    int totalFightsLost = 0;
    for (int i = 0 ; i < maxNumOfDays ; i++) {
        if ( catFightSuccessAnalyticsArray[i] == 1 ){ // Cat wins fight case
            totalFightsWon += 1;
        } else if ( catFightSuccessAnalyticsArray[i] == -1 ){ // Cat lose fight case
            totalFightsLost += 1;
        } else {
            continue; // For when there was no information (no 1 or -1)
        }
    }
    if (totalFightsLost == 0) {
        return 100; // Return100 if there are no lost fights to prevent division by zero and tell the user that they won all fights
    } else {
        float successRate = static_cast<float>(totalFightsWon) / findTotalNumberOfFights(); // Perform division with floating-point numbers
        return round(successRate * 100); // Round the result to two decimal places
    }
}

// STOP  - Functions



int main() {
    cout << "Main Function Has Commenced..." << endl << endl;
    srand(time(nullptr)); // Seed the random number generator with the current time
    int fightCounter = 0; // Resets counter to 0 to ensure accuracy of analytics array

    populateMatrixWithNull(); // Fills the play space array with nullptr in all indexes

    // Populate catArray with Cat objects with random attributes (x,y,strength)
    populateCatArray(1, catArray);
    // Print catArray (will print the ID's of the cats in the array)
    cout << "Cat Array: ";
    cout << "# Of Cats: " << countCats(catArray) << endl;
    printCatArray(catArray);

    // Populate dogArray with Dog objects with random attributes (x,y,strength)
    populateDogArray(1, dogArray);
    // Print dogArray (will print the ID's of the dogs in the array)
    cout << "Dog Array: ";
    cout << "# Of Dogs: " << countDogs(dogArray) << endl;
    printDogArray(dogArray);
    cout << endl;

    // Places all the cats and dogs into the play space matrix
    placeCatsInPlayspace((catArray), catArrayLength);
    placeDogsInPlayspace((dogArray), dogArrayLength);

    printMatrix(); // Prints the play space matrix

    int loopVar = 0;
    while ( loopVar < 100000 and countDogs(dogArray) > 0 and countCats(catArray) > 0) {
        // Reset Fight counter
        fightCounter = 0;
        // Check for fights
        for (int i = 0; i < catArrayLength; ++i) {
            if (catArray[i] != nullptr) {
                Dog* nearbyDog = catArray[i]->checkForNearbyDogs(matrix);
                if (nearbyDog != nullptr) { // If there is a dog nearby
                    fightCounter += 1; // Increments fight counter
                    if (catArray[i]->fightDog(nearbyDog)) {
                        catFightSuccessAnalyticsArray[loopVar] = 1; // 1 means that the cat won the fight
                        cout << "Cat ID: " << catArray[i]->getID() << " won the fight!" << loopVar << endl;
                        // Kill the dog and make a new cat in its image (not a christianity reference, I promise)
                        int dogX = nearbyDog->getX();
                        int dogY = nearbyDog->getY();
                        int dogID = nearbyDog->getID();
                        int dogStrength = nearbyDog->getStrength();
                        // cout << "Dog Info: (" << dogX << "," << dogY << "," << dogID << "," << dogStrength << ")" << endl;
                        //matrix[dogX][dogY] = nullptr; // Delete the dog from the game board

                        // START - TRYING TO MAKE DOGS TURN INTO CATS
                        Cat* newCat = new Cat(dogX, dogY, dogID, dogStrength);
                        matrix[dogX][dogY] = newCat; // Delete the dog from the game board and put the new cat there
                        placeNewCatIntoCatArray(newCat); // Place the cat made from the dog into the cat array
                        // STOP  - TRYING TO MAKE DOGS TURN INTO CATS

                        for (int j = 0; j < dogArrayLength; ++j) { // Find the defeated dog in the dogArray and delete it
                            if (dogArray[j] == nearbyDog) {
                                dogArray[j] = nullptr; // Set the pointer in the array to nullptr
                                delete(dogArray[j]); // THIS MIGHT BE CAUSING ISSUES
                                break; // Stop searching once the defeated dog is found and deleted
                            }
                        }
                        //delete nearbyDog; // Delete the defeated dog object (this line might be causing issues!)
                    } else {
                        catFightSuccessAnalyticsArray[loopVar] = -1; // 0 means that the cat lost the fight
                        cout << "Cat ID: " << catArray[i]->getID() << " lost the fight!" << loopVar << endl;
                        if ( catArray[i]->getStrength() <= 0 ){
                            catArray[i] = nullptr; // Kill the cat if it has no strength left
                            delete(catArray[i]);
                        } else {
                            //cout << "Strength before fight: " << catArray[i]->getStrength() << endl;
                            catArray[i]->decrementStrenght(); // Decrements the cat's strength by 1 upon losing
                            //cout << "Strength after  fight: " << catArray[i]->getStrength() << endl;
                        }
                    }
                } else {
                    continue;
                    //cout << "No nearby dogs for Cat ID: " << catArray[i]->getID() << endl;
                }
            }
        }

        // MOVEMENT LOOPS
        for (int i = 0; i < catArrayLength; i++) { // Iterates over the cat array and moves all the cats
            if (catArray[i] != nullptr) { // Ensures that it doesn't try to move a non-existent cat
                catArray[i]->move();
            }
        }
        for (int i = 0; i < catArrayLength; i++) { // Iterates over the dog array and moves all the dogs
            if (dogArray[i] != nullptr) { // Ensures that it doesn't try to move a non-existent dog
                dogArray[i]->move();
            }
        }

        clearMatrix(); // Clears the matrix of ALL objects
        placeCatsInPlayspace((catArray), catArrayLength); // Replaces all the cats to their new positions
        placeDogsInPlayspace((dogArray), dogArrayLength); // Replaces all the dogs to their new positions

        // Analytics
        catAnalyticsArray[loopVar] = countCats(catArray); // Stores the # of cats during that day into the analytics arr
        dogAnalyticsArray[loopVar] = countDogs(dogArray); // Stores the # of cats during that day into the analytics arr
        fightsAnalyticsArray[loopVar] = fightCounter; // Stores the # of fights during that day into the analytics array

        //cout << "Day #" << loopVar << " has completed." << endl;
        loopVar++;
    }

    printMatrix(); // Prints the play space matrix at the end
    cout << "Cat Array: ";
    printCatArray(catArray); // Prints the cat array at the end
    cout << "Dog Array: ";
    printDogArray(dogArray); // Prints the dog array at the end

    // Basic logic to determine console dialogue regarding which side won (Cats or Dogs)
    if ( (countCats(catArray) > 0) and (countDogs(dogArray) == 0) ) {
        cout << "It took " << loopVar << " days to defeat the dogs!" << endl;
    } else if ( countCats(catArray) == 0 and countDogs(dogArray) > 0  ) {
        cout << "It took " << loopVar << " days to defeat the cats!" << endl;
    } else { // Error checker
        cout << "CHECK LOGIC AT END OF MAIN()" << endl;
    }

    // DELETES OBJECTS AT THE END OF THE SIMULATION!
    // Delete (free memory) dog objects
    for (int i = 0; i < dogArrayLength; ++i) {
        if (dogArray[i] != nullptr) {
            delete(dogArray[i]);
        }
    }
    // Delete (free memory) cat objects
    for (int i = 0; i < catArrayLength; ++i) {
        if (catArray[i] != nullptr) {
            delete(catArray[i]);
        }
    }

    // Analytical console dialogue
    float ratioOfFightsToDays = static_cast<float>(findTotalNumberOfFights()) / loopVar;
    float catFightSuccessRate = findCatFightSuccessRate();
    cout << endl;
    cout << "+===============================================+" << endl;
    cout << "| FIGHT ANALYTICS                               |" << endl;
    cout << "+===============================================+" << endl;
    cout << "Total # Of Fights: " << findTotalNumberOfFights()  << endl;
    cout << "Average # Of Fights Per Day: " << ratioOfFightsToDays  << endl;
    cout << "Average # Of Days Between Fights: " << floor(( 1 / ratioOfFightsToDays ))  << endl;
    cout << "Cat Win Rate: " << catFightSuccessRate << "%" << endl;
    cout << "Dog Win Rate: " << (100 - catFightSuccessRate) << "%" << endl;
    cout << "=================================================" << endl;


    return 0;
}
