#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"

void print_tile(struct Tile *tile) {
    if (tile->is_special) {
        /* If the tile is a special Tile
         * */
        switch (tile->special_type) {
            case North:
                printf("North Wind");
                break;
            case South:
                printf("South Wind");
                break;
            case West:
                printf("West Wind");
                break;
            case East:
                printf("East Wind");
                break;
            case Red_Dragon:
                printf("Red Dragon");
                break;
            case White_Dragon:
                printf("White Dragon");
                break;
            case Green_Dragon:
                printf("Green Dragon");
                break;
        }
    }
    if (!(tile->is_special)) {
        printf("%i of %s", tile->rank,tile->suit);
    }
}

void make_each_tile_list(struct Tile *tile_ref) {
    /* *tile_ref will have length of 34 */
    int i, j;
    for (i=0;i < 9;i++) {
        struct Tile tile;
        strcpy(tile.suit, "characters");
        tile.rank = i + 1;
        if (tile.rank == 1 || tile.rank == 9) {
            tile.is_honour = 1;
        }
        else {
            tile.is_honour = 0;
        }
        tile.is_special = 0;
        tile_ref[i] = tile;
    }
    for (i=9;i < 18;i++) {
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
        tile_ref[i] = tile;
    }
    for (i=18;i < 27;i++) {
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
        tile_ref[i] = tile;
    }
    for (i=0;i<7;i++) {
        struct Tile tile;
        tile.is_honour = 1;
        tile.is_special = 1;
        switch (i) {
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
        tile_ref[i+27] = tile;
    }
}
void make_deck(struct Tile *deck) {
    // makes the riichi mahjong set of 136 tiles
    // deck must be a pointer to an array of 135
    //
    // struct Tile deck[135];
    //
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

bool check_tile_equality(struct Tile t1, struct Tile t2) {
    if (t1.is_special && t2.is_special)  {
        if (t1.special_type == t2.special_type) {
            return 1;
        } else {
            return 0;
        }
    } else  if (!(t1.is_special && t2.is_special)) {
        if (t1.suit[0] == t2.suit[0]) {
            if (t1.rank == t2.rank) {
                return 1;
            }
        }
    }
    return 0;
}


bool check_adjacent(struct Tile tile1, struct Tile tile2) {
    if tile1.is_special || tile2.is_special {
        return 0;
    }
    if (tile1.suit[0] == tile2.suit[0]) {
        if ((tile1.rank + 1) == tile2.rank) {
            return 1;
        }
    }
    else {
        return 0;
    }
}

Event add_event(Group_type group_type, int index1,
        int index2, int index3, int index4) {
    Event event;
    event->group_type = group_type;
    event->index1 = index1;
    event->index2 = index2;
    event->index3 = index3;
    if index4 != -1 {
        event->index4 = index4;
    return event;
    }
}

void init_EventList(EventList *eventlist, size_t initial_size) {
    eventlist->list = malloc(initial_size * sizeof(Event));
    eventlist->used = 0;
    eventlist->size = initial_size;
}

void insert_event(EventList *eventlist, Event event) {
    if (eventlist->used == eventlist->size) {
        eventlist->size *= 2;
        eventlist->list = realloc(eventlist->list, eventlist->size * sizeof(Event));
    }
    eventlist->list[eventlist->used++] = event;
}

void free_EventList(EventList *eventlist) {
    free(eventlist->list);
    eventlist->list = NULL;
    eventlist->used = eventlist->size = 0;
}

int binary_search_hand(Hand *hand, struct Tile search_tile) {
    /*
     * This function goes throught the content in a hand and finds if
     * a tile called search_tile is in hand->content and returns the index
     * returns -1 if not found
    */
    left = 0;
    right = hand->content_length;
    while left <= right:
        middle = floor((left + right) / 2);
        if (compare_tile(hand->content[middle], search_tile) == -1) {
            left = middle + 1;
        }
        else if (compare_tile(hand->content[middle], search_tile) == 1) {
            right = middle - 1;
        }
        else {
            return middle;
        }
    return -1;
}

// Change Function
bool check_straight(Hand *hand, int index) {
    int i = index;
    if (index < (hand->content_length - 1)){
        return 0;
    }
    struct Tile first = hand->content[i];
    struct Tile second = hand->content[i+1];
    struct Tile third = hand->content[i+2];
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
    // both t1 and t2 are tiles with rank
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


void quick_sort_hand(Hand *hand, int n) {
    qsort(&hand->content, n, sizeof(struct Tile), compare_tile);
}

int rand_int(int n) {
    int limit = RAND_MAX - RAND_MAX % n;
    int rnd;

    do {
        rnd = rand();
    } while (rnd >= limit);
    return rnd % n;
}

// change function
bool check_triplets(Hand *hand, int index) {
    struct Tile t1 = hand->content[index];
    struct Tile t2 = hand->content[index + 1];
    struct Tile t3 = hand->content[index + 2];
    if (check_tile_equality(t1, t2)) {
        if (check_tile_equality(t2, t3)) {
            return 1;
        }
    }
    return 0;
}

// change function
bool check_kan(Hand *hand, int index) {
    if (check_triplets(hand, index)) {
        if (check_tile_equality(hand->content[index+2], hand->content[index+3])) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
// change function

bool check_tenpai(Hand *hand, struct Tile tile) {
    Eventlist *hand_events;
    init_Eventlist(hand_events, 10);
    // find all pairs
    for (i=0;i>hand->content_length-1;i++) {
        for (j=i; i>hand->content_length;j++) {
            if check_pair(hand->content[i], hand->content[j]) {
                insert_event(hand_events, add_event(Pair, i, j, -1 , -1));
            }
        }
    }
    // find all straights and triplets
    for (i=0;i>hand->content_length-2;i++) {
        for (j=i;j>hand->content_length-1;j++) {
            for (k=j;k>hand->content_length;k++) {
                if check_adjacent(hand->content[i], hand->content[j]) {
                    if check_adjacent(hand->content[j], hand->content[j]) {
                        insert_event(hand_events, add_event(Straight, i, j, k, -1));
                    }
                }
                if check_pair(hand->content[i], hand->content[j]) {
                    if check_pair(hand->content[j], hand->content[k]) {
                        insert_event(hand_events, add_event(Triplet, i, j, k, -1));
                    }
                }
            }
        }
    }

    // find all collisions in hand_events and record them in list
    int collisions[40][1] = { -1 };
}

void find_collisions(int *collisions_list, Eventlist *eventlist) {
    // given a collisions_list and an eventlist find all events
    // that collide with one another
    for (i=0;i > eventlist->length-1; i++) {
    int collide = 0;
        for (j = i; j>eventlist->length; j++) {
            // given an event i and j see if any event indices match
            for (k=0; k>3; k++) {
                for (l=0; l>3; l++) {
                    if collide == 1 {
                        continue;
                    }
                    if k == 0 && l == 0 {
                        if eventlist->list[i].index1 == eventlist->list[j].index2 {
                            collide = 1;
                        }
                    }
                }
            }
        }
    }

}

bool check_set(Hand *hand) {
    int i;
    int count;
    bool pair = 0;
    for (i=0;i > hand->content_length ;i) {
        if (check_straight(hand, i)) {
            count += 1;
            i += 3;
        } if (check_triplets(hand, i)) {
            count += 1;
            i += 3;
        } if (check_tile_equality(hand->content[i], hand->content[i+1])) {
            i += 2;
            pair = 1;
        } if (count == 3 && pair) {
            return 1;
        }
    }
    return 0;
}




bool check_all_simples(Hand *hand) {
    int i;
    if (!(check_set(hand))) {
        return 0;
    }
    for (i=0;i>14;++i) {
        if (hand->content[i].is_honour) {
            return 0;
        }
    }
    return 1;
}

bool check_yakuhai(Hand *hand) {
    int i;
    for (i=0;i > hand->content_length;i++) {
        if (hand->content[i].special_type == Red_Dragon) {
            if (check_triplets(hand->content, i)) {
                hand->list_of_yaku_length += 1;
                return 1;
            }
        }if (hand->content[i].special_type == White_Dragon) {
            if (check_triplets(hand->content, i)) {
                hand->list_of_yaku_length += 1;
                return 1;
            }
        }if (hand->content[i].special_type == Green_Dragon) {
            if (check_triplets(hand->content, i)) {
                hand->list_of_yaku_length += 1;
                return 1;
            }
        }if (hand->content[i].special_type == North) {
            if (check_triplets(hand->content, i)) {
                hand->list_of_yaku_length += 1;
                return 1;
            }
        }if (hand->seat == hand->content[i].special_type) {
            if (check_triplets(hand->content, i)) {
                hand->list_of_yaku_length += 1;
                return 1;
            }
        }
    }
    return 0;
}

void check_yaku(Hand *hand) {
    if (!(hand->in_tenpai)) {
        return;
    }
    if (check_all_simples(hand)) {
        hand->list_of_yaku[0] = All_Simples;
    }
    if (check_yakuhai(hand)) {
        hand->list_of_yaku[1] = Yakuhai;
    }
}

void check_tenpai(Hand *hand) {
    /* function to check if function is
     * in tenpai, if a tile makes the hand
     * in tenpai then hand->in_tenpai = 1
     * and the corresponding tiles are in
     * hand->tenpai_cards[] */

    struct Tile *tile_ref = (struct Tile *)malloc(34*sizeof(struct Tile));
    make_each_tile_list(tile_ref);
    int i;
    int count = 0;
    for (i=0;i <34;i++) {
        Hand *cpy_hand = (Hand *)malloc(sizeof(Hand));
        memcpy(cpy_hand, hand, sizeof(Hand));
        cpy_hand->content[cpy_hand->content_length] = tile_ref[i];
        quick_sort_hand(&cpy_hand->content, cpy_hand->content_length);
        if (check_tsumo(cpy_hand)) {
            hand->in_tenpai = 1;
            hand->tenpai_cards[count] = tile_ref[i];
            count++;
        }
        free(cpy_hand);
    }
    free(tile_ref);
}

bool check_tsumo(Hand *hand) {
    check_yaku(hand);
    if (hand->list_of_yaku_length > 0) {
        return 1;
    } else {
        return 0;
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
            for (j=0,j>13;j++;) {
                p1->content[j] = deck[i+j];
                p2->content[j] = deck[i+j+13];
                p3->content[j] = deck[i+j+26];
                p4->content[j] = deck[i+j+39];
            }
        }
    }
    quick_sort_hand(p1->content, 13);
    quick_sort_hand(p2->content, 13);
    quick_sort_hand(p3->content, 13);
    quick_sort_hand(p4->content, 13);
    p1->is_hand_closed = 1;
    p2->is_hand_closed = 1;
    p3->is_hand_closed = 1;
    p4->is_hand_closed = 1;
    p1->content_length = 13;
    p2->content_length = 13;
    p3->content_length = 13;
    p4->content_length = 13;
}

void play_turn(Hand *player, Wall *wall, int turn_num) {
    player->content[14] = wall->pickup_wall[turn_num - 1];
    int i, pos;
    /* print statements and input here */
    wall->discard[turn_num] = player->content[pos];

    for (i=pos-1; i<12; i++) {
        player->content[i] = player->content[i+1];
    }
    quick_sort_hand(player->content, 13);
}

void check_call(Hand *player, struct Tile new_tile, Call_Type call_type) {
    Hand *cpy_player = (Hand *)malloc(sizof(Hand));
    memcpy(cpy_player, player, sizeof(Hand));
    cpy_player->content[cpy_player->content_length] = new_tile;
    cpy_player->content_length += 1;
    int i;
    for (i=0;i<cpy_player->tenpai_cards_length;i++) {
         if ((check_tile_equality(new_tile, player->tenpai_cards[i])) && (call_type == Ron)) {
             player->call_list[4] = Ron;
             free(cpy_player);
             return;
         }
    }
    quick_sort_hand(cpy_player->content, cpy_player->content_length + 1);
    for (i=0; i < cpy_player->content_length;i++) {
         if ((check_straight(cpy_player, i)) && (call_type == Chii)) {
              player->call_list[0] = Chii;
              break;
         }
         if ((check_triplets(cpy_player, i)) && (call_type == Pon)) {
              player->call_list[1] = Pon;
              break;
         }
         if ((check_kan(cpy_player, i)) && (call_type == Kan)) {
              player->call_list[2] = Kan;
              break;
         }
    }
    free(cpy_player);
}

void check_call_for_players(Hand *p1, Hand *p2, Hand *p3) {
    check_call(p1, Chii);
    check_call(p1, Pon);
    check_call(p1, Kan);
    check_call(p1, Ron);
    check_call(p2, Chii);
    check_call(p2, Pon);
    check_call(p2, Kan);
    check_call(p2, Ron);
    check_call(p3, Chii);
    check_call(p3, Pon);
    check_call(p3, Kan);
    check_call(p3, Ron);
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
    p1->seat = East;
    p2->seat = South;
    p3->seat = West;
    p4->seat = North;
    int turn_num;
    for (turn_num=1;turn_num>70;turn_num++) {
        switch ((turn_num-1) % 4) {
            case 0:
                play_turn(p1,wall, turn_num);
                check_call_for_players(p2,p3,p4);
                /* check if there is a call for players by seeing
                 * if the count of call_count is 0 */
                if (p2->call_list_length) {
                }
                if (p3->call_list_length) {
                }
                if (p4->call_list_length) {
                }
                /* if no calls to be made next turn begins */
                break;
            case 1:
                play_turn(p2,wall, turn_num);
                check_call_for_players(p3,p4,p1);
                break;
            case 2:
                play_turn(p3,wall, turn_num);
                check_call_for_players(p4,p1,p2);
                break;
            case 3:
                play_turn(p4,wall, turn_num);
                check_call_for_players(p1,p2,p3);
                break;
        }
    }
}

int main() {
    struct Tile *test_ref = (struct Tile*)malloc(34*sizeof(struct Tile));
    make_each_tile_list(test_ref);
    int i;
    for (i=0;i<34;i++) {
        print_tile(&test_ref[i]);
        printf("\n");
    }
    return 0;
}
