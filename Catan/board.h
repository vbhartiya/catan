#pragma once

#define BOARD "\n"\
"                                                 *  3:1   *						  \n"\
"                                                *          *					  \n"\
"                                              [N01NB][0102B-][N02NB]  				  \n"\
"                                             [0104B/]                [0205B\\]  	\n"\
"                                            [0104B/]                  [0205B\\] 	\n"\
"                                           [0104B/]       TTTTTT       [0205B\\]	\n"\
"                   ORE * * [N03NB][0304B-][N04NB]         00         [N05NB][0506B-][N06NB] * WOOL  \n"\
"                   2:1     [0308B/]               [0409B\\]        .....       [0510B/]               [0611B\\]    2:1	\n"\
"                     *    [0308B/]                 [0409B\\]  [R]             [0510B/]                 [0611B\\]    *	 \n"\
"                      *  [0308B/]       TTTTTT      [0409B\\]                [0510B/]       TTTTTT      [0611B\\]  *             \n"\
"         [N07NB][0708B-][N08NB]         00         [N09NB][0910B-][N10NB]         00         [N11NB][1112B-][N12NB]       \n"\
"        [0713B/]                [0814B\\]        .....      [0915B/]                [1016B\\]        .....      [1117B/]                [1218B\\]      \n"\
"       [0713B/]                  [0814B\\]  [R]            [0915B/]                  [1016B\\]  [R]            [1117B/]                  [1218B\\]     \n"\
"      [0713B/]       TTTTTT       [0814B\\]               [0915B/]       TTTTTT       [1016B\\]               [1117B/]       TTTTTT       [1218B\\]    \n"\
"     [N13NB]         00         [N14NB][1415B-][N15NB]         00         [N16NB][1617B-][N17NB]         00         [N18NB]	  \n"\
"      [1319B\\]        .....       [1420B/]               [1521B\\]        .....       [1622B/]               [1723B\\]        .....       [1824B/]    \n"\
"       [1319B\\]  [R]             [1420B/]                 [1521B\\]  [R]             [16221/]                 [1723B\\]  [R]             [1824B/]     \n"\
"        [1319B\\]                [1420B/]       TTTTTT      [1521B\\]                [1622B/]       TTTTTT      [1723B\\]                [1824B/]      \n"\
" GRAIN * [N19NB][1920B-][N20NB]         00         [N21NB][2122B-][N22NB]         00         [N23NB][2324B-][N24NB] * 3:1 \n"\
"  2:1   [1925B/]                [2026B\\]        .....      [2127B/]                [2228B\\]        .....      [2329B/]                [2430B\\]   *  \n"\
"   *   [1925B/]                  [2026B\\]  [R]            [2127B/]                  [2228B\\]  [R]            [2329B/]                  [2430B\\]  *  \n"\
"    * [1925B/]       TTTTTT       [2026B\\]               [2127B/]       TTTTTT       [2228B\\]               [2329B/]       TTTTTT       [2430B\\] *  \n"\
"     [N25NB]         00         [N26NB][2627B-][N27NB]         00         [N28NB][2829B-][N29NB]         00         [N30NB]	  \n"\
"      [2531B\\]        .....       [2632B/]               [2733B\\]        .....       [2834B/]               [2935B\\]        .....       [3036B/]    \n"\
"       [2531B\\]  [R]             [2632B/]                 [2733B\\]  [R]             [2834B/]                 [2935B\\]  [R]             [3036B/]     \n"\
"        [2531B\\]                [2632B/]       TTTTTT      [2733B\\]                [2834B/]       TTTTTT      [2935B\\]                [3036B/]      \n"\
"         [N31NB][3132B-][N32NB]         00         [N33NB][3334B-][N34NB]         00         [N35NB][3536B-][N36NB]          \n"\
"        [3137B/]                [3238B\\]        .....      [3339B/]                [3440B\\]        .....      [3541B/]                [3642B\\]      \n"\
"       [3137B/]                  [3238B\\]  [R]            [3339B/]                  [3440B\\]  [R]            [3541B/]                  [3642B\\]     \n"\
"      [3137B/]       TTTTTT       [3238B\\]               [3339B/]       TTTTTT       [3440B\\]               [3541B/]       TTTTTT       [3642B\\]    \n"\
"     [N37NB]         00         [N38NB][3839B-][N39NB]         00         [N40NB][4041B-][N41NB]         00         [N42NB]	  \n"\
"    * [3743B\\]        .....       [3844B/]               [3945B\\]        .....       [4046B/]               [4147B\\]        .....       [4248B/] *  \n"\
"   *   [3743B\\]  [R]             [3844B/]                 [3945B\\]  [R]             [4046B/]                 [4147B\\]  [R]             [4248B/]   * \n"\
"   *    [3743B\\]                [3844B/]       TTTTTT      [3945B\\]                [4046B/]       TTTTTT      [4147B\\]                [4248B/]    * \n"\
"   3:1 * [N43NB][4344B-][N44NB]         00         [N45NB][4546B-][N46NB]         00         [N47NB][4748B-][N48NB] * 3:1    \n"\
"                         [4449B\\]        .....      [4550B/]                [4651B\\]        .....      [4752B/]                       \n"\
"                          [4449B\\]  [R]            [4550B/]                  [4651B\\]  [R]            [4752B/]    \n"\
"                           [4449B\\]               [4550B/]       TTTTTT       [4651B\\]               [4752B/]     \n"\
"                           [N49NB][4950B-][N50NB]         00         [N51NB][5152B-][N52NB]   	 \n"\
"                            *            * [5053B\\]        .....       [5154B/] *            *		 \n"\
"                             *  LUMBER  *   [5053B\\]  [R]             [5154B/]   * * BRICK *		 \n"\
"                                  2:1        [5053B\\]                [5154B/]         2:1  			 \n"\
"                                              [N53NB][5354B-][N54NB]                     	 \n\n"

#define COSTS ""\
"\t%17s | 1 Brick, 1 Lumber\n"\
"\t%17s | 1 Brick, 1 Lumber, 1 Grain, 1 Wool\n"\
"\t%17s | 2 Grain, 3 Ore\n"\
"\t%17s | 1 Grain, 1 Wool, 1 Ore\n"\

struct Node;

std::string InitRandomBoard();
bool ReplaceSubstring(std::string& input, const char* original, const char* replacement, size_t length, unsigned int ocurrence = 0);
void ParseNodeNeighbours(Node* nodes, const std::string& board);
bool IsValidRoad(const std::string& board, int source, int destination);