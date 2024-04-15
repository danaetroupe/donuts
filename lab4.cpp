// Danae Troupe & Elikem Kalitsi
// Lab 04: The Doughnut Shop
// Wednesday, April 10, 2024

#include <unistd.h>
#include <iostream>
#include <pthread.h>
using namespace std;


class Factory
{
    int* donutCount; // number of doughnuts made by the factory
    bool* inventoryFull; //flag indicating whether or not the warehouse if full
    int* inventoryCount; //number of saleable boxes in the warehouse
    bool* factoryActive; // factory status

    pthread_t threads[2];

    void* factoryThread(void* vp);
    void* warehouseThread(void* vp);
public:
    Factory(int, bool, int);
};

/// ----------------------------------------------------------------------
/// @brief main thread
/// @return 1
int main()
{
    Factory* factory = new Factory(0, false, 0);
    return 1;
}

/// ----------------------------------------------------------------------
/// @brief initalizes Factory class
/// @param donuts number of doughnuts made by the factory
/// @param isFull flag indicating whether or not the warehouse is full
/// @param inventory number of saleable boxes in the warehouse
Factory::Factory(int donuts, bool isFull, int inventory)
{
    *donutCount = donuts;
    *inventoryFull = isFull;
    *inventoryCount = inventory;
    *factoryActive = true;

    int status;

    status = pthread_create(&threads[0], NULL, factoryThread, NULL);
    cout << (status) ? "S: factoryThread created with error status: " << status << endl; : "S: factoryThread created successfully." << endl;
    status = pthread_create(&threads[1], NULL, warehouseThread, NULL);
    cout << (status) ? "S: factoryThread created with error status: " << status << endl; : "S: factoryThread created successfully." << endl;

    int boxes = 0;
    while (boxes >= 0)
    {
        cout << "S: How many boxes of doughnuts would you like to purchase?\n", cin >> boxes;
        if (boxes <= *inventoryCount)
        {
            cout << "S: Thank you for your business" << endl;
            *inventoryCount -= boxes;
        }
        else
        {
            cout << "S: Sale not accepted." << endl;
        }
    }
    *factoryActive = false;
}

/// ----------------------------------------------------------------------
void* Factory::factoryThread(void* vp)
{
    while (*factoryActive)
    {
        cout << "F: Production Started" << endl;
        while (*inventoryFull)
        {
            usleep(500000);
            *donutCount++;
        }
        cout << "F: Production halted" << endl;
        while (!*inventoryFull)
        {
            continue;
        }
    }
    pthread_exit(0);
}

/// ----------------------------------------------------------------------
void* Factory::warehouseThread(void* vp)
{
    while (factoryActive)
    {
        if (donutCount % 12 == 0)
        {
            *inventoryFull = ++ * inventoryCount == 10;
            cout << "W: " << *inventoryCount << " in inventory." << endl;
        }
        else
        {
            *inventoryFull = *inventoryCount == 10;
        }
        if (*inventoryFull) { cout << "W: Inventory full." << endl; }
        while (*inventoryCount == 10)
        {
            continue;
        }
    }
    pthread_exit(0);
}