#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Tile {
	char suit[20];
	unsigned int num;
	bool is_honour;
	bool is_special;
	char special[20];
};

void make_deck() {
	struct Tile deck[135];
	int i;
	
	for (i = 0; i <9; ++i) {
		struct Tile tile;
		strcpy(tile.suit, "characters");
		tile.num = i+1;
		if (tile.num == 1 || tile.num == 9) {
			tile.is_honour = 1;
		}
		else {
			tile.is_honour = 0;
		}
		tile.is_special = 0;
		deck[i] = tile;
		printf("%d, %s\n", deck[i].num, deck[i].suit);
	}
	for (i = 0; i <9; ++i) {
		struct Tile tile;
		strcpy(tile.suit, "bamboo");
		tile.num = i+1;
		if (tile.num == 1 || tile.num == 9) {
			tile.is_honour = 1;
		}
		else {
			tile.is_honour = 0;
		}
		tile.is_special = 0;
		deck[i+9] = tile;
		printf("%d, %s\n", deck[i+9].num, deck[i+9].suit);
	}	
	for (i = 0; i <9; ++i) {
		struct Tile tile;
		strcpy(tile.suit, "pins");
		tile.num = i+1;
		if (tile.num == 1 || tile.num == 9) {
			tile.is_honour = 1;
		}
		else {
			tile.is_honour = 0;
		}
		tile.is_special = 0;
		deck[i+18] = tile;
		printf("%d, %s\n", deck[i+18].num, deck[i+18].suit);
	}
}

void shuffle_deck(struct Tile tile) {
	

}

int main() {
	make_deck();

	return 0;
}
