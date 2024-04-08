#ifndef PARAMS_HPP
#define PARAMS_HPP

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

#endif