#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    North, South, West, East,
    Red_Dragon, White_Dragon,
    Green_Dragon
} Special;

typedef enum {
    All_Simples,
    Yakuhai
} Yaku;


typedef enum {
    S_North,
    S_South,
    S_East,
    S_West
} Seat;

typedef enum {
    No_Call, Chii, Pon, Kan, Ron
} Call_Type;

typedef enum {
    Pair, Triplet, Quad, Straight
} Group_Type;

struct Tile {
	char suit[20];
	unsigned int rank;
	bool is_honour;
	bool is_special;
    Special special_type;
};

typedef struct {
    struct Tile content[16];
    int content_length;
    struct Tile open_content[11];
    int open_content_length;
    bool is_hand_closed;
    bool has_yaku;
    Yaku list_of_yaku[10];
    int list_of_yaku_length;
    Special seat;
    Call_Type call_list[4];
    int call_list_length;
    bool in_tenpai;
    struct Tile tenpai_cards[12];
    int tenpai_cards_length;
} Hand;


typedef struct {
    struct Tile dead_wall[13];
    struct Tile pickup_wall[69];
    struct Tile discard[69];
} Wall;

typedef struct {
    Group_type group_type;
    int index1;
    int index2;
    int index3;
    int index4;
} Event;

typedef struct {
    Event *list;
    size_t used;
    size_t size;
} EventList;

void print_tile(struct Tile *tile);

bool check_straight(struct Tile *hand, int index);

void quick_sort_hand(struct Tile *hand, int n);


void make_deck(struct Tile *deck);

void print_deck(struct Tile *deck, int n);

bool check_tile_equality(struct Tile t1, struct Tile t2);

void init_EventList(EventList *eventlist, size_t initial_size);
void insert_event(EventList *eventlist, Event event); 
void free_EventList(EventList *eventlist); 

int compare_tile(const void * tile1, const void * tile2);

bool check_straight(struct Tile *hand, int index);

void quick_sort_hand(struct Tile *hand, int n);

int rand_int(int n);

bool check_adjacent(struct Tile tile1, struct Tile tile2);

int binary_search_hand(Hand *hand, struct Tile search_tile);

bool check_pair(struct Tile *t1, struct Tile *t2);

bool check_triplets(struct Tile *hand, int index);

bool check_kan(struct Tile *hand, int index);

bool check_all_simples(Hand *hand);

bool check_yakuhai(Hand *hand);

void check_yaku(Hand *hand);

void shuffle_deck(struct Tile *deck, int length);

void build_wall_and_deal(struct Tile *deck, Hand *p1, Hand *p2, Hand *p3, Hand *p4, Wall *wall);

void play_turn(Hand *player, Wall *wall, int turn_num);

void check_call(Hand *player, Call_Type call_type);

void check_call_for_players(Hand *p1, Hand *p2, Hand *p3);

void play_round();



#endif
