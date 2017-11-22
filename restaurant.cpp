#include "restaurant.h"
#include "quicksort.h"

// CHANGE THE RATINGS PREFEREr





void qsort(RestDist restaurants[], int n);


/*
	Sets *ptr to the i'th restaurant. If this restaurant is already in the cache,
	it just copies it directly from the cache to *ptr. Otherwise, it fetches
	the block containing the i'th restaurant and stores it in the cache before
	setting *ptr to it.
*/



void getRestaurant(restaurant* ptr, int i, Sd2Card* card, RestCache* cache) {
	uint32_t block = REST_START_BLOCK + i/8;
	if (block != cache->cachedBlock) {
		while (!card->readBlock(block, (uint8_t*) cache->block)) {
			Serial.print("readblock failed, try again");
		}
		cache->cachedBlock = block;
	}
	*ptr = cache->block[i%8];
}


// Computes the manhattan distance between two points (x1, y1) and (x2, y2).
int16_t manhattan(int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
	return abs(x1-x2) + abs(y1-y2);
}

/*
	Fetches all restaurants from the card, saves their RestDist information
	in restaurants[], and then sorts them based on their distance to the
	point on the map represented by the MapView.
*/
void getAndSortRestaurants(const MapView& mv, RestDist restaurants[], Sd2Card* card, RestCache* cache) {
	restaurant r;
	uint32_t jj;
	//int SELECTOR = 5;
	// first get all the restaurants and store their corresponding RestDist information.
	for (int i = 0; i < NUM_RESTAURANTS; ++i) {


			getRestaurant(&r, i, card, cache);
			//Serial.print(r.name);Serial.print(" ");Serial.println(rating);


			restaurants[i].index = i;
			restaurants[i].dist = manhattan(lat_to_y(r.lat), lon_to_x(r.lon),
																			mv.mapY + mv.cursorY, mv.mapX + mv.cursorX);

	}
	//Serial.print("J: ");Serial.println(j);
	for (int i=0; i<NUM_RESTAURANTS; ++i){
		getRestaurant(&r, i, card, cache);

		int x = r.rating;
		int rating = max(floor(x+1)/2, 1);
		int index = restaurants[i].index;
		//Serial.print(rating);
		if (rating >= RATING){
			restaurants[i].index = index;
			jj++;
		}
		else{
			restaurants[i].index = 0;
			restaurants[i].dist = 12345678+i;

		}
		//Serial.println(restaurants[i].index);

	}
	//Serial.print("MIN res: ");Serial.println(jj);
	// Now sort them.
	qsort(restaurants, NUM_RESTAURANTS);

}
