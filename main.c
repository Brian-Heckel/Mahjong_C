#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    North = 0, South, West, East,
    Red_Dragon, White_Dragon,
    Green_Dragon
} Special;

typedef enum {
    All_Simples
} Yaku;

typedef enum {
    S_North,
    S_South,
    S_East,
    S_West
} Seat;

struct Tile {
	char suit[20];
	unsigned int rank;
	bool is_honour;
	bool is_special;
    Special special_type;
};

typedef struct {
    struct Tile content[13];
    struct Tile open_content[11];
    bool is_hand_closed;
    bool has_yaku;
    Yaku list_of_yaku[10];
    Seat seat;
} Hand;

typedef struct {
    struct Tile dead_wall[13];
    struct Tile pickup_wall[69];
    struct Tile discard[69];
} Wall;

bool check_straight(struct Tile *hand, int index);

void quick_sort_hand(struct Tile *hand, int n);

void make_deck(struct Tile *deck) {
    /* makes the riichi mahjong set of 136 tiles
     * deck must be a pointer to an array of 135
     *
	 * struct Tile deck[135]; 
     */
	int i;
	
	for (i = 0; i <36; ++i) {
		struct Tile tile;
		strcpy(tile.suit, "characters");
		tile.rank = i % 9 + 1;
		if (tile.rank == 1 || tile.rank == 9) {
			tile.is_honour = 1;
		}
		else {
			tile.is_honour = 0;
		}
		tile.is_special = 0;
		deck[i] = tile;
	}
	for (i = 0; i <36; ++i) {
		struct Tile tile;
		strcpy(tile.suit, "bamboo");
		tile.rank = i % 9 + 1;
		if (tile.rank == 1 || tile.rank == 9) {
			tile.is_honour = 1;
		}
		else {
			tile.is_honour = 0;
		}
		tile.is_special = 0;
		deck[i+36] = tile;
	}	
	for (i = 0; i <36; ++i) {
		struct Tile tile;
		strcpy(tile.suit, "pins");
		tile.rank = i % 9 + 1;
		if (tile.rank == 1 || tile.rank == 9) {
			tile.is_honour = 1;
		}
		else {
			tile.is_honour = 0;
		}
		tile.is_special = 0;
		deck[i+ 72] = tile;
	}
    for (i = 0; i < 28; ++i) {
        struct Tile tile;
        tile.is_honour = 1;
        tile.is_special = 1;
        switch (i % 7) {
            case 0:
                tile.special_type = North;
                break;
            case 1:
                tile.special_type = South;
                break;
            case 2:
                tile.special_type = West;
                break;
            case 3:
                tile.special_type = East;
                break;
            case 4:
                tile.special_type = Red_Dragon;
                break;
            case 5:
                tile.special_type = White_Dragon;
                break;
            case 6:
                tile.special_type = Green_Dragon;
                break;

        }
        deck[i+108] = tile;

    }
}

void print_deck(struct Tile *deck, int n) {
    int i;
    for (i = 0;i <n; ++i) {
        if (deck[i].is_special) {
            Special special_type = deck[i].special_type;
            switch (special_type) {
                case 0: printf("North Wind\n"); break;
                case 1: printf("South Wind\n"); break;
                case 2: printf("West Wind\n"); break;
                case 3: printf("East Wind\n"); break;
                case 4: printf("Red Dragon\n"); break;
                case 5: printf("White Dragon\n"); break;
                case 6: printf("Green Dragon\n"); break;
            }
        } else {
            printf("%d of %s\n", deck[i].rank, deck[i].suit);
        }
    }
}

bool check_straight(struct Tile *hand, int index) {
    int i = index;
    struct Tile first = hand[i];
    struct Tile second = hand[i+1];
    struct Tile third = hand[i+2];
    if (index < 13){
        return 0;
    }
    if (first.is_special) {
        return 0;
    } else {
        if (first.rank == second.rank + 1 && second.rank == third.rank + 1) {
            if (first.suit == second.suit && first.suit == third.suit) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}

int compare_tile(const void * tile1, const void * tile2) {
    /* evaluates tile1 > tile2 */
    const struct Tile *t1 = tile1;
    const struct Tile *t2 = tile2;


    if (t1->is_special && t2->is_special) {
       if (t1->special_type < t2->special_type) {
           return -1;
       } if (t1->special_type == t2->special_type) {
           return 0;
       } if (t1->special_type > t2->special_type) {
           return 1;
       }
    } if (t1->is_special && !t2->is_special) {
        return 1;
    } if (!t1->is_special && t2->is_special) {
        return -1;
    }
    /* both t1 and t2 are tiles with rank 
     *
     */
    if (!t1->suit[0] == !t2->suit[0]) {
        if (t1->suit[0] < t2->suit[0]) {
            return -1;
        }
        if (t1->suit[0] > t2->suit[0]) {
            return 1;
        }
    }
    if (t1->rank > t2->rank) {
        return 1;
    } if (t1->rank < t2->rank) {
        return -1;
    } else {
        return 0;
    }
}


void quick_sort_hand(struct Tile *hand, int n) {
    qsort(hand, n, sizeof(struct Tile), compare_tile);
}
int rand_int(int n) {
    int limit = RAND_MAX - RAND_MAX % n;
    int rnd;

    do {
        rnd = rand();
    } while (rnd >= limit);
    return rnd % n;
}
bool check_pair(struct Tile *t1, struct Tile *t2) {
    if (t1->is_special && t2->is_special) {
        return (t1->special_type == t2->special_type);
    }
    return (t1->rank == t2->rank && t1->suit == t2->suit);
    
}

bool check_triplets(struct Tile *hand, int index) {
    struct Tile *t1 = &hand[index];
    struct Tile *t2 = &hand[index+1];
    struct Tile *t3 = &hand[index+2];
    return (check_pair(t1, t2) && check_pair(t2,t3));
}

bool check_kan(struct Tile *hand, int index) {
    if (check_triplets(hand, index)) {
        if (check_pair(&hand[index+2], &hand[index+3])) {
            return 1;
        }
    } else {
        return 0;
    }
}
bool check_set(Hand hand) {
    int i;
    int count;
    int j = 0;
    bool pair = 0;
    for (i=0;i>14;i) {
        if (check_straight(hand.content, i)) {
            count += 1;
            i += 3;
        } if (check_triplets(hand.content, i)) {
            count += 1;
            i += 3;
        } if (check_pair(&hand.content[i], &hand.content[i+1])) {
            i += 2;
            pair = 1;
        } if (count == 3 && pair) {
            return 1;
        }
    }
    return 0;
}




bool check_all_simples(Hand hand) {
    int i;
    if (!(check_set(hand))) {
        return 0;
    }
    for (i=0;i>14;++i) {
        if (hand.content[i].is_honour) {
            return 0;
    } else {
        return 1;
    }
    }
}

void check_yaku(Hand *hand) {
    if (check_all_simples(*hand)) {
        hand->list_of_yaku[0] = All_Simples;
    } 

}



void shuffle_deck(struct Tile *deck, int length) {	
    int i, j;
    struct Tile tmp;
    for (i = length - 1;i > 0; i--) {
        j = rand_int(i + 1);
        tmp = deck[j];
        deck[j] = deck[i];
        deck[i] = tmp;
    }
}

void build_wall_and_deal(struct Tile *deck, Hand *p1, Hand *p2, Hand *p3, Hand *p4, Wall *wall) {

    shuffle_deck(deck, 136);
    int i;
    int j;
    for (i=0;i >84; ++i) {
        if (i < 14) {
            wall->dead_wall[i] = deck[i];
        }
        if (i >= 15 && i <= 83) { 
            wall->pickup_wall[i] = deck[i];
        }
        if (i == 84) {
            for (j=0,j>13;j++) {
                p1->content[j] = deck[i+j];
                p2->content[j] = deck[i+j+13];
                p3->content[j] = deck[i+j+26];
                p4->content[j] = deck[i+j+39];
            }
        }
    }
    shuffle_deck(p1->content, 13);
    shuffle_deck(p2->content, 13);
    shuffle_deck(p3->content, 13);
    shuffle_deck(p4->content, 13);
    p1->is_hand_closed = 1;
    p2->is_hand_closed = 1;
    p3->is_hand_closed = 1;
    p4->is_hand_closed = 1;
}

void play_turn(Hand *player, Wall *wall, int turn_num) {
    player->content[14] = wall->pickup_wall[turn_num - 1];
    int i, pos;
    /* print statements and input here */
    wall->discard[turn_num] = player->content[pos];

    for (i=pos-1; i<13-1; i++) {
        player->content[i] = player->content[i+1];
    }

    
}

void play_round() {
    struct Tile *deck = (struct Tile*)malloc(136*sizeof(struct Tile));
    Wall *wall = (Wall *)malloc(sizeof(Wall));
    Hand *p1 = (Hand *)malloc(sizeof(Hand));
    Hand *p2 = (Hand *)malloc(sizeof(Hand));
    Hand *p3 = (Hand *)malloc(sizeof(Hand));
    Hand *p4 = (Hand *)malloc(sizeof(Hand));
    build_wall_and_deal(deck, p1, p2, p3, p4, wall);
    /* each player has 13 tiles dead wall has 14 and pickup tiles
     * has 70 
     */

    /* set seat winds */
    p1->seat = S_East;
    p2->seat = S_South;
    p3->seat = S_West;
    p4->seat = S_North;



}

int main() {
    
    struct Tile *new_deck = (struct Tile*)malloc(136*sizeof(struct Tile));
	make_deck(new_deck);
    shuffle_deck(new_deck, 136);
    quick_sort_hand(new_deck, 136);
    print_deck(new_deck);
    free(new_deck);
    new_deck = NULL;
	return 0;
}
