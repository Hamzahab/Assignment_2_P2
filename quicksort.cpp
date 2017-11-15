// This might be easiest to develop as a desktop program, and then move
// it over to an Arduino program once you know it is working.

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include "lcd_image.h"

#include "quicksort.h"
#include "restaurant.h"


/* Given an array of length n > 0 and an index 0 <= pi < n, this rearranges
the array so all items <= a[pi] appear before a[pi] and all items > a[pi]
appear after a[pi].

Returns the index of a[pi] after the rearrangement.
*/

// struct RestDist {
//   uint16_t index; // index of restaurant from 0 to NUM_RESTAURANTS-1
//   uint16_t dist;  // Manhatten distance to cursor position
// };


void swap_rest1(RestDist& r1, RestDist& r2) {
	RestDist tmp = r1;
	r1 = r2;
	r2 = tmp;
}

int pivot(RestDist restaurants[], int n, int pi) {
  swap_rest1(restaurants[pi],restaurants[n-1]);

  int lo = 0, hi = n-2;

  while(true){
    // Serial.print("lo");
    // Serial.println(lo);
    // Serial.print("hi");
    // Serial.println(hi);

    if(restaurants[hi].dist > restaurants[n-1].dist){
      hi--;
    }
    else if(restaurants[lo].dist <= restaurants[n-1].dist){
      lo++;
    }

    else{
      swap_rest1(restaurants[lo],restaurants[hi]);
      lo++;
    }

    if(lo > hi){
      swap_rest1(restaurants[lo],restaurants[n-1]);
      break;
    }

  }
  return lo;
}

/*
Don't forget to test the pivot operation!

You don't know exactly where all items will appear after a pivot so it is
hard to fully automate this test. Here is what you can do. Suppose pivot()
returns index npi:
- check a[i] <= a[npi] for i < npi
- check a[i] > a[npi] for i > npi
- check that a[npi] (after the pivot) is the same as the
value of a[pi] (before the pivot)

A test that is not fully automatic would be to print the resulting array
to the screen, so you can at least see visually that the pivot procedure
worked as expected.
*/

// Sort an array with n elements using Quick Sort
void qsort(RestDist restaurants[], int n) {
  // if n <= 1 do nothing (just return)
  if(n <=1) return;
  // pick a pivot index pi
  int pi = n/2;
  // call pivot with this pivot index, store the returned
  // location of the pivot in a new variable, say new_pi
  // cout << "pi is" << pi << endl;
  int new_pi = pivot(restaurants,n,pi);
  // recursively call qsort twice:
  // - once with the part before index new_pi
  // - once with the part after index new_pi
  // cout << "new_pi is: " <<new_pi << endl;
  qsort(restaurants,new_pi);
  qsort(restaurants + new_pi,n-new_pi);

  // and that’s it!
}

// Don't forget some tests! Use the tests from ssort as a starting point.
