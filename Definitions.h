#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <time.h>
#include <stdlib.h>

#define ARRAY_LEN(fixed_len_array) (sizeof(fixed_len_array) / sizeof((fixed_len_array)[0]))
#define CLAMP(num, minimum, maximum) (((num) < (minimum)) ? ((num) = (minimum)) : (((num) > (maximum)) ? ((num) = (maximum)) : 0))

typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

#define G_FPS 60
#define MAX_PROFONDEUR 50
#define W_LARGEUR 1920
#define W_HAUTEUR 1080
#define W_SEMI_LARGEUR (W_LARGEUR / 2)
#define W_SEMI_HAUTEUR (W_HAUTEUR / 2)

#define NB_ENNEMIS 30
#define NB_PROJECTILES 50
#define NB_ITEMS 10
#define NB_EXPLOSIONS 30

struct Jeu;
struct Sprite;
struct Joueur;
struct Item;
struct Ennemi;
struct Explosion;
struct Projectile;
struct Curseur;
struct BombePulsar;

enum TypeEnnemi;
enum StatusEnnemi;
enum TypeItem;
enum OptionsCurseur;
enum Gamemode;
enum Touches;
enum ProprietaireProjectile;

#define SAUTS_MODELE_AUCUN -1

typedef struct Sprite {
	Jeu* jeu;

	Vector3* modele;
	i32 modele_longueur;
	i32* indexs_lignes_sauter;

	Vector3 position;
	SDL_Color couleure;

	float taille;
	float pitch;
	float roll;

	i32 indexs_de_tir[2];
	i32 timer;
	SDL_bool afficher;
} Sprite;

#define JOUEUR_MAX_VAGUES 3.0f
#define VAGUE_ELECTRIQUE_REGENERATION 1.0f / (30.0f * G_FPS)
#define JOUEUR_VITESSE_TIR 25
#define JOUEUR_MAX_HP 150
#define JOUEUR_DEFAULT_HP 100
#define JOUEUR_LARGEUR 50
#define JOUEUR_HAUTEUR 20

typedef struct Joueur {
	Sprite self;
	Vector2 velocite;
	TypeItem powerup;
	float vagues_electriques;
	i32 HP;
	i32 vitesse_tir;
} Joueur;

typedef enum TypeEnnemi {
	TYPEENNEMI_OCTAHEDRON,
	TYPEENNEMI_DIAMANT,
	TYPEENNEMI_TOURNANT,
	TYPEENNEMI_ENERGIE,
	TYPEENNEMI_CROISSANT,
	TYPEENNEMI_DUPLIQUEUR,
	TYPEENNEMI_PATRA,
	TYPEENNEMI_OCTAHEDRON_DUR,
	TYPEENNEMI_DIAMANT_DUR,
	TYPEENNEMI_TOURNANT_DUR,
	TYPEENNEMI_ENERGIE_DUR,
	TYPEENNEMI_CROISSANT_DUR,
	TYPEENNEMI_DUPLIQUEUR_DUR,
	TYPEENNEMI_PATRA_DUR,
	TYPEENNEMI_BOSS,
	TYPEENNEMI_PATRA_MINION,
	TYPEENNEMI_PATRA_MINION_DUR
} TypeEnnemi;

typedef enum StatusEnnemi {
	STATUSENNEMI_VIDE = 0,
	STATUSENNEMI_INITIALIZATION,
	STATUSENNEMI_NORMAL,
	STATUSENNEMI_MORT,

	STATUSENNEMI_DUPLIQUEUR_0_RESTANT = 60,
	STATUSENNEMI_DUPLIQUEUR_1_RESTANT,
	STATUSENNEMI_DUPLIQUEUR_2_RESTANT,

	STATUSENNEMI_PATRA_0_RESTANT = 70,
	STATUSENNEMI_PATRA_1_RESTANT,
	STATUSENNEMI_PATRA_2_RESTANT,
	STATUSENNEMI_PATRA_3_RESTANT,
	STATUSENNEMI_PATRA_4_RESTANT,
	STATUSENNEMI_PATRA_5_RESTANT,
	STATUSENNEMI_PATRA_6_RESTANT,
	STATUSENNEMI_PATRA_7_RESTANT,
	STATUSENNEMI_PATRA_8_RESTANT,

	STATUSENNEMI_BOSS_INIT = 150,
	STATUSENNEMI_BOSS_INIT_2,
	STATUSENNEMI_BOSS_INIT_3,
	STATUSENNEMI_BOSS_NORMAL,
	STATUSENNEMI_BOSS_MORT,
	STATUSENNEMI_BOSS_MORT_2,
	STATUSENNEMI_BOSS_MORT_3,
} StatusEnnemi;

#define DENSITE_ETOILES 100
#define RAYON_DEBUT_ETOILES 100
#define VITESSE_ETOILES 1.02f

#define CENTRE SDL_MAX_SINT32
#define NO_SCROLL SDL_MAX_SINT32
#define BLANC 0xFFFFFF
#define ROUGE 0xFF0000
#define VERT 0x00FF00
#define BLEU 0x0000FF
#define NOIR 0x000000
#define OPAQUE 255

#define LARGEUR_DEFAUT 5.0f
#define HAUTEUR_DEFAUT 10.0f
#define ESPACE_DEFAUT 3.0f

const i16 char_draw_info_starting_indexes[] = {
    1, 18, 47, 60, 81, 98, 111, 132, 145, 158, 171, 184, 193, 210, 223, 240, // a - p
    257, 278, 299, 320, 329, 342, 351, 368, 377, 386, 399, 420, 433, 454, 471, // q - 4
    484, 513, 534, 543, 564, 585, 590, 599, 604, 609, 630, 651, 676, 697, 706, // 5 - ??
    711, 716, 721, 734, 747
};
#define CHAR_DRAW_INFO_LEN 756
const i8 char_draw_info[CHAR_DRAW_INFO_LEN] = {
    127, // space/unknown

    0, 10, 0, 0, // a
    0, 0, 5, 0,
    5, 0, 5, 10,
    5, 5, 0, 5, 127,

    0, 10, 0, 0, // b
    0, 0, 5, 0,
    5, 0, 5, 3,
    5, 3, 0, 5,
    0, 5, 5, 7,
    5, 7, 5, 10,
    5, 10, 0, 10, 127,

    0, 10, 0, 0, // c
    0, 0, 5, 0,
    5, 10, 0, 10, 127,

    0, 10, 0, 0, // d
    0, 0, 2, 0,
    2, 10, 0, 10,
    2, 10, 5, 5,
    2, 0, 5, 5, 127,

    0, 10, 0, 0, // e
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 5, 0, 5, 127,

    0, 10, 0, 0, // f
    0, 0, 5, 0,
    5, 5, 0, 5, 127,

    0, 10, 0, 0, // g
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 10, 5, 5,
    5, 5, 3, 5, 127,

    0, 10, 0, 0, // h
    5, 0, 5, 10,
    5, 5, 0, 5, 127,

    0, 0, 5, 0, // i
    2, 0, 2, 10,
    5, 10, 0, 10, 127,

    5, 0, 5, 10, // j
    5, 10, 0, 10,
    0, 10, 0, 7, 127,

    0, 10, 0, 0, // k
    0, 5, 5, 0,
    0, 5, 5, 10, 127,

    0, 10, 0, 0, // l
    5, 10, 0, 10, 127,

    0, 10, 0, 0, // m
    5, 0, 5, 10,
    0, 0, 2, 5,
    5, 0, 2, 5, 127,

    0, 10, 0, 0, // n
    5, 0, 5, 10,
    0, 0, 5, 10, 127,

    0, 10, 0, 0, // o
    5, 0, 5, 10,
    0, 0, 5, 0,
    5, 10, 0, 10, 127,

    0, 10, 0, 0, // p
    0, 0, 5, 0,
    5, 0, 5, 5,
    5, 5, 0, 5, 127,

    0, 10, 0, 0, // q
    4, 0, 4, 10,
    0, 0, 4, 0,
    4, 10, 0, 10,
    5, 10, 3, 5, 127,

    0, 10, 0, 0, // r
    0, 0, 5, 0,
    5, 0, 5, 5,
    5, 5, 0, 5,
    2, 5, 5, 10, 127,

    0, 0, 5, 0, // s
    5, 10, 0, 10,
    5, 5, 0, 5,
    0, 0, 0, 5,
    5, 10, 5, 5, 127,

    2, 0, 2, 10, // t
    0, 0, 5, 0, 127,

    0, 10, 0, 0, // u
    5, 0, 5, 10,
    5, 10, 0, 10, 127,

    0, 0, 2, 10, // v
    5, 0, 2, 10, 127,

    0, 10, 0, 0, // w
    5, 0, 5, 10,
    5, 10, 0, 10,
    2, 10, 2, 4, 127,

    0, 0, 5, 10, // x
    5, 0, 0, 10, 127,

    5, 0, 0, 10, // y
    0, 0, 2, 5, 127,

    0, 0, 5, 0, // z
    5, 10, 0, 10,
    5, 0, 0, 10, 127,

    5, 0, 0, 10, // 0
    0, 10, 0, 0,
    5, 0, 5, 10,
    0, 0, 5, 0,
    5, 10, 0, 10, 127,

    0, 3, 2, 0, // 1
    2, 0, 2, 10,
    5, 10, 0, 10, 127,

    0, 3, 1, 0, // 2
    1, 0, 4, 0,
    5, 3, 4, 0,
    5, 3, 0, 10,
    5, 10, 0, 10, 127,

    5, 10, 5, 0, // 3
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 5, 0, 5, 127,

    0, 5, 0, 0, // 4
    5, 0, 5, 10,
    5, 5, 0, 5, 127,

    5, 0, 0, 0, // 5
    0, 5, 0, 0,
    5, 5, 0, 5,
    5, 5, 5, 8,
    5, 8, 4, 10,
    4, 10, 1, 10,
    1, 10, 0, 8, 127,

    0, 10, 0, 0, // 6
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 10, 5, 5,
    5, 5, 0, 5, 127,

    5, 0, 0, 0, // 7
    5, 0, 0, 10, 127,

    5, 5, 0, 5, // 8
    0, 10, 0, 0,
    5, 0, 5, 10,
    0, 0, 5, 0,
    5, 10, 0, 10, 127,

    5, 10, 5, 0, // 9
    0, 0, 5, 0,
    5, 10, 0, 10,
    0, 0, 0, 5,
    5, 5, 0, 5, 127,

    0, 10, 0, 10, 127, // .

    0, 3, 0, 3, // :
    0, 7, 0, 7, 127,

    2, 8, 0, 10, 127, // ,

    2, 2, 0, 0, 127, // '

    0, 10, 0, 0, // �
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 5, 0, 5,
    1, -2, 4, -4, 127,

    0, 10, 0, 0, // �
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 5, 0, 5,
    1, -4, 4, -2, 127,

    0, 10, 0, 0, // �
    0, 0, 5, 0,
    5, 10, 0, 10,
    5, 5, 0, 5,
    1, -2, 2, -4,
    4, -2, 2, -4, 127,

    0, 10, 0, 0, // �
    0, 0, 5, 0,
    5, 0, 5, 10,
    5, 5, 0, 5,
    1, -2, 4, 0, 127,

    2, 0, 2, 3, // "
    4, 0, 4, 3, 127,

    1, 5, 4, 5, 127, // -

    0, 10, 5, 0, 127, // /

    5, 10, 0, 0, 127, // \

    4, 0, 2, 3, // (
    2, 3, 2, 7,
    4, 10, 2, 7, 127,

    1, 0, 3, 3, // )
    3, 3, 3, 7,
    1, 10, 3, 7, 127,

    0, 5, 4, 5, // +
    2, 3, 2, 7, 127
};


typedef struct Explosion {
    Jeu* jeu;
    Vector3 position;
    i32 timer;
} Explosion;


#define NB_OPTIONS 4
typedef enum OptionsCurseur {
    CURSEUR_NOUVELLE_PARTIE,
    CURSEUR_CONTINUER,
    CURSEUR_ARCADE,
    CURSEUR_AUCUN
} OptionsCurseur;

typedef struct Curseur {
    Sprite self;

    i32 max_selection;
    OptionsCurseur selection;
    OptionsCurseur option_selectionee;
} Curseur;

#define CURSEUR_DAS G_FPS / 4
#define CURSEUR_X_INIT W_SEMI_LARGEUR - 150
#define CURSEUR_Y_INIT W_SEMI_HAUTEUR + 85
#define CURSEUR_ESPACE 50

#define MODELE_CURSEUR_LONGUEURE 5
const Vector3 curseur_modele[MODELE_CURSEUR_LONGUEURE] =
{
    {-15, -15, 0},
    {15, 0, 0 },
    {-15, 15, 0},
    {-12, 0, 0},
    {-15, -15, 0}
};

typedef struct Ennemi {
	Sprite self;
	TypeEnnemi type;
	StatusEnnemi statut;

	i32 HP;
	i32 largeur;

	float intervale_tir;
	float vitesse;
	float vitesse_z;

	Vector2 velocite;
	Vector2 cible;

	Vector3* modele_en_marche;
} Ennemi;

#define NB_TYPES_ENNEMIS 17
#define BOSS_MAX_HP 150
#define DISTANCE_DE_BORD_EVITER_INIT 200
#define VITESSE_MOYENNE_ENNEMI 0.4f
#define VITESSE_MOYENNE_Z_ENNEMI 2.5f
#define VITESSE_MOYENNE_TIR_ENNEMI 0.2f
#define ENNEMI_FRICTION 0.8f


const TypeEnnemi* liste_niveaux[20] = {
	0
};

const TypeEnnemi ennemis_valide_arcade[] = {
        TYPEENNEMI_OCTAHEDRON, TYPEENNEMI_DIAMANT, TYPEENNEMI_TOURNANT, TYPEENNEMI_ENERGIE, TYPEENNEMI_CROISSANT, TYPEENNEMI_DUPLIQUEUR, TYPEENNEMI_PATRA,
    TYPEENNEMI_OCTAHEDRON_DUR, TYPEENNEMI_DIAMANT_DUR, TYPEENNEMI_TOURNANT_DUR, TYPEENNEMI_ENERGIE_DUR, TYPEENNEMI_CROISSANT_DUR, TYPEENNEMI_DUPLIQUEUR_DUR, TYPEENNEMI_PATRA_DUR
};

typedef struct BombePulsar {
	Jeu* jeu;
	i32 HP;
	i32 timer;
	SDL_bool frapee;
} BombePulsar;

#define QUANTITE_RAYONS_BOMBE_PULSAR 50
#define BOMBE_PULSAR_MAX_HP 50
#define COULEUR_BOMBE (SDL_Color){ .r = 150, .g = 255, .b = 255, .a = 255 }

#define HYP_BOMBE_DATA_LEN 72
const float hyperbole_bleue_bombe_pulsar_data[HYP_BOMBE_DATA_LEN] = {
	-0.35f, -0.95f, -0.4f, -1.55f,
	-0.4f, -1.55f, -0.6f, -2.15f,
	-0.6f, -2.15f, -0.9f, -2.35f,
	0.2f, -1.0f, 0.25f, -1.55f,
	0.25f, -1.55f, 0.35f, -2.25f,
	0.35f, -2.25f, 0.6f, -2.45f,
	-0.15f, -1.15f, -0.15f, -1.8f,
	0.0f, -1.75f, 0.2f, -2.25f,
	-0.25f, -2.25f, -0.4f, -2.45f,
	-0.3f, 0.95f, -0.45f, 1.5f,
	-0.45f, 1.5f, -0.65f, 1.95f,
	-0.65f, 1.95f, -1.0f, 2.2f,
	0.25f, 0.95f, 0.3f, 1.5f,
	0.3f, 1.5f, 0.5f, 2.0f,
	0.5f, 2.0f, 1.0f, 2.3f,
	0.0f, 1.2f, 0.05f, 1.8f,
	-0.1f, 1.55f, -0.15f, 1.95f,
	-0.4f, 1.75f, -0.25f, 1.3f
};



#define LARGEUR_MAX_VAGUE_ELECTRIQUE 80
#define LARGEUR_MIN_VAGUE_ELECTRIQUE 50
#define PRECISION_VAGUE_ELECTRIQUE 50
#define TEMPS_AVANT_VAGUE_FAIT_DEGATS G_FPS / 6
#define DURATION_VAGUE_ELECTRIQUE 1 * G_FPS

typedef struct VagueElectrique {
    Sprite self;
    float rayon;
} VagueElectrique;

#define TIMER_DISPARITION_ITEM 2 * G_FPS
#define HP_BONUS 10
#define FACTEUR_VITESSE_ITEM 0.98f
#define POS_Z_COLLISION_JOUEUR 2.0f
#define NB_TYPES_ITEM 7

typedef enum TypeItem {
	TYPEITEM_NONE,
	TYPEITEM_X2_SHOT,
	TYPEITEM_X3_SHOT,
	TYPEITEM_HOMING,
	TYPEITEM_SPREAD,
	TYPEITEM_LASER,
	TYPEITEM_HP,
	TYPEITEM_VAGUE
} TypeItem;

typedef struct Item {
	Sprite self;
	TypeItem type;
} Item;

const float VITESSE_PROJECTILE = 0.95f;
static SDL_bool son_cree;

typedef struct Projectile {
	Sprite self;

	Vector3 cible;
	ProprietaireProjectile proprietaire;
	SDL_bool laser;

	float z_init;
	u8 ID;
} Projectile;

typedef enum ProprietaireProjectile {
	PROPRIETAIREPROJ_JOUEUR,
	PROPRIETAIREPROJ_ENNEMI
} ProprietaireProjectile;

#define NB_EFFETS 8
typedef enum EffetAudio {
    EFFET_PRESENTE,
    EFFET_NIVEAU,
    EFFET_TIR,
    EFFET_EXPLOSION_ENNEMI,
    EFFET_EXPLOSION_JOUEUR,
    EFFET_POWERUP,
    EFFET_VAGUE,
    EFFET_DOTV_ENTREE
} EffetAudio;

#define NB_MUSIQUE 7
typedef enum Musique {
    MUSIQUE_ATW,
    MUSIQUE_CRTP,
    MUSIQUE_DYSGENESIS,
    MUSIQUE_TBOT,
    MUSIQUE_DOTV,
    MUSIQUE_EUGENESIS,
    MUSIQUE_DCQBPM,
} Musique;

struct DataAudio {
    i32 ID;
    const char* fichier;
};
static struct DataAudio MusiqueData[NB_MUSIQUE] = {
    { MUSIQUE_ATW, "audio\\around the world.wav" },
    { MUSIQUE_CRTP, "audio\\cant remove the pain.wav" },
    { MUSIQUE_DYSGENESIS, "audio\\titlescreen.wav" },
    { MUSIQUE_TBOT, "audio\\the beginning of Time.wav" },
    { MUSIQUE_DOTV, "audio\\Dance of the Violins.wav" },
    { MUSIQUE_EUGENESIS, "audio\\eugenesis.wav" },
    { MUSIQUE_DCQBPM, "audio\\240 Bits Per Mile.wav" }
};
static struct DataAudio EffetData[NB_EFFETS] = {
    { EFFET_PRESENTE, "audio\\presents.wav" },
    { EFFET_NIVEAU, "audio\\sfx1.wav" },
    { EFFET_TIR, "audio\\laserShoot.wav" },
    { EFFET_EXPLOSION_ENNEMI, "audio\\explosion_enemy.wav" },
    { EFFET_EXPLOSION_JOUEUR, "audio\\explosion.wav" },
    { EFFET_POWERUP, "audio\\powerup.wav" },
    { EFFET_VAGUE, "audio\\synth.wav" },
    { EFFET_DOTV_ENTREE, "audio\\tone.wav" }
};

#define NB_CHAINES_SFX 20
typedef struct Son {
    Mix_Music* musique;
    Mix_Chunk* effets_sonnores[NB_CHAINES_SFX];

    i32 timer;
    i32 index_prochain_chunk;
    u8 volume;
    i32 volume_sdl;
} Son;

#define ALL_CHUNKS -1
static SDL_Rect boite_volume =
{
    W_LARGEUR - 360,
    10,
    350,
    100
};

const SDL_Rect BARRE_HP = { 125, 15, 10, 20 };
const SDL_Rect BARRE_VAGUE = { 125, 40, 100, 20 };

typedef struct Jeu {
	SDL_Window* fenetre;
	SDL_Renderer* render;
	SDL_Event* event;

	Joueur* joueur;
	Ennemi* ennemis;
	Projectile* projectiles;
	Explosion* explosions;
	Item* items;

	VagueElectrique* vague_electrique;
	Curseur* curseur;
	BombePulsar* bombe;
	Son* son;

	i32 gTimer;

	Vector2* etoiles;
	TypeEnnemi* liste_ennemis_arcade;
	i32 timer_changement_niveau;
	SDL_bool bouger_etoiles;
	SDL_bool en_cours;
	SDL_bool arcade_debloque;
	SDL_bool debug_lvl_select;
	u8 arcade_etapes;
	clock_t temps_image;
	Gamemode gamemode;
	i32 touches_pesees;
	i32 niveau;
	i32 niveau_continue;
	i32 ennemis_restant;
	i32 ennemis_tues;
	SDL_Color couleure_fond_ecran;
} Jeu;

typedef enum Gamemode {
	GAMEMODE_MENU_PRINCIPAL,
	GAMEMODE_AVENTURE,
	GAMEMODE_ARCADE,
	GAMEMODE_SCENE_INITIALIZATION,
	GAMEMODE_SCENE_DEBUT,
	GAMEMODE_SCENE_BONNE_FIN,
	GAMEMODE_SCENE_MAUVAISE_FIN,
	GAMEMODE_SCENE_GENERIQUE
} Gamemode;

typedef enum Touches {
	TOUCHE_W = 1,
	TOUCHE_A = 2,
	TOUCHE_S = 4,
	TOUCHE_D = 8,
	TOUCHE_J = 16,
	TOUCHE_K = 32,
	TOUCHE_M = 64,
	TOUCHE_R = 128,
	TOUCHE_C = 256,
	TOUCHE_E = 512,
	TOUCHE_PLUS = 1024,
	TOUCHE_MOINS = 2048
} Touche;

const i32 CODE_ARCADE[7] = { 0, TOUCHE_A, TOUCHE_R, TOUCHE_C, TOUCHE_A, TOUCHE_D, TOUCHE_E };
const i32 TOUCHES_VALIDES_ARCADE = TOUCHE_A | TOUCHE_R | TOUCHE_C | TOUCHE_A | TOUCHE_D | TOUCHE_E;